/*
===============================================================================
 Name        : main.c
 Author      : Olli Usenius
 Version     :
 Copyright   : $(copyright)
 Description :
===============================================================================
*/

#include "main.h"
#include "messages.h"
#include "pin_mappings.h"
#include "can_fsb.h"

#include <uv_utilities.h>
#include <uv_rtos.h>

dev_st dev = {};
#define this ((dev_st*) &dev)


bool adc_get_temp(uv_adc_channels_e adc_chn, int16_t *dest);
bool adc_get_level(uv_adc_channels_e adc_chn, int16_t *dest);
uint16_t adc_get_voltage_mv(const uv_adc_channels_e adc_chn);
void rpm_callb(uv_gpios_e);


#define GET_MOTOR_WATER()	(!uv_gpio_get(MOTOR_WATER_TEMP_I))
#define GET_MOTOR_OIL_PRESS() (!uv_gpio_get(MOTOR_OIL_PRESS_I))


#define VND5050_CURRENT_AMPL_UA		4173
#define VN5E01_CURRENT_AMPL_UA		13923

void init(dev_st* me) {
	uv_gpio_add_interrupt_callback(&rpm_callb);

	// load non-volatile data
	if (uv_memory_load()) {
		this->oilcooler_trigger_temp = OIL_TEMP_DEFAULT_TRIGGER_VALUE_C;

		// initialize non-volatile memory to default settings
		this->dither_ampl = 0;
		this->dither_freq = 50;
		this->pump_i = CONFIG_SOLENOID_MA_I;
		this->pump_p = CONFIG_SOLENOID_MA_P;
		this->engine_power_usage = ENGINE_POWER_USAGE_DEFAULT;
		this->pwr_rising_p = PWR_RISING_P_DEFAULT;
		uv_memory_save();
	}
	// initialize outputs
	uv_output_init(&this->glow, GLOW_SENSE_AIN,
			GLOW_PLUGS_O, VN5E01_CURRENT_AMPL_UA, 50000, 60000,
			OUTPUT_MOVING_AVG_COUNT,
			ESB_EMCY_GLOW_OVERLOAD, ESB_EMCY_GLOW_FAULT);
	uv_output_init(&this->starter, STARTER_SENSE_AIN,
			STARTER_O, VN5E01_CURRENT_AMPL_UA, 15000, 30000,
			OUTPUT_MOVING_AVG_COUNT,
			ESB_EMCY_STARTER_OVERLOAD, ESB_EMCY_STARTER_FAULT);
	uv_output_init(&this->ac, AC_SENSE_AIN,
			AC_O, VN5E01_CURRENT_AMPL_UA, 10000, 15000, OUTPUT_MOVING_AVG_COUNT,
			ESB_EMCY_AC_OVERLOAD, ESB_EMCY_AC_FAULT);
	uv_output_init(&this->engine_start1, ENGINE_START1_SENSE_AIN,
			ENGINE_START_1_O, VN5E01_CURRENT_AMPL_UA, 30000, 40000, OUTPUT_MOVING_AVG_COUNT,
			ESB_EMCY_ENGINE_STOP_OVERLOAD, ESB_EMCY_ENGINE_STOP_FAULT);
	uv_output_init(&this->engine_start2, ENGINE_START2_SENSE_AIN,
			ENGINE_START_2_O, VN5E01_CURRENT_AMPL_UA, 30000, 40000, OUTPUT_MOVING_AVG_COUNT,
			ESB_EMCY_ENGINE_STOP_OVERLOAD, ESB_EMCY_ENGINE_STOP_FAULT);
	uv_output_init(&this->alt_ig, ALT_IG_SENSE_AIN,
			ALT_IG_O, VND5050_CURRENT_AMPL_UA, 2000, 5000, OUTPUT_MOVING_AVG_COUNT,
			ESB_EMCY_ALT_IG_OVERLOAD, ESB_EMCY_ALT_IG_FAULT);
	uv_output_init(&this->oilcooler, OILCOOLER_AIN, OILCOOLER_O,
			VN5E01_CURRENT_AMPL_UA, 15000, 30000, OUTPUT_MOVING_AVG_COUNT,
			ESB_EMCY_OILCOOLER_OVERCURRENT, ESB_EMCY_OILCOOLER_FAULT);
	uv_solenoid_output_init(&this->pump, PUMP_PWM, this->dither_freq,
			DUTY_CYCLEPPT(this->dither_ampl), PUMP_SENSE_AIN,
			VND5050_CURRENT_AMPL_UA, 3500, 5000,
			ESB_EMCY_PUMP_OVERLOAD, ESB_EMCY_PUMP_FAULT);
	uv_pid_set_p(uv_solenoid_output_get_ma_pid(&this->pump), this->pump_p);
	uv_pid_set_i(uv_solenoid_output_get_ma_pid(&this->pump), this->pump_i);

	// initialize inputs
	UV_GPIO_INIT_INPUT(ALT_L_I, PULL_UP_ENABLED);
	UV_GPIO_INIT_INPUT(ALT_P_RPM_I, PULL_UP_ENABLED);
	uv_gpio_init_int(ALT_P_RPM_I, INT_RISING_EDGE);
	UV_GPIO_INIT_INPUT(MOTOR_WATER_TEMP_I, PULL_UP_ENABLED);
	UV_GPIO_INIT_INPUT(MOTOR_OIL_PRESS_I, PULL_UP_ENABLED);

	uv_hysteresis_init(&this->oil_temp_hyst, this->oilcooler_trigger_temp,
			OIL_TEMP_HYSTERESIS_C, false);


	// motor temp
	sensor_init(&this->motor_temp, MOTOR_TEMP_AIN, MOTOR_TEMP_AVG_COUNT,
			ESB_EMCY_MTEMP_SENSOR_FAULT, &adc_get_temp);
	sensor_set_warning(&this->motor_temp, MOTOR_TEMP_WARN_VALUE,
			MOTOR_TEMP_HYSTERESIS, false, ESB_EMCY_MTEMP_WARNING);
	sensor_set_error(&this->motor_temp, MOTOR_TEMP_ERR_VALUE,
			MOTOR_TEMP_HYSTERESIS, false, ESB_EMCY_MTEMP_ERROR);

	// oil temp
	sensor_init(&this->oil_temp, OIL_TEMP_AIN, OIL_TEMP_AVG_COUNT,
			ESB_EMCY_OTEMP_SENSOR_FAULT, &adc_get_temp);
	sensor_set_warning(&this->oil_temp, OIL_TEMP_WARN_VALUE,
			OIL_TEMP_HYSTERESIS, false, ESB_EMCY_OTEMP_WARNING);
	sensor_set_error(&this->oil_temp, OIL_TEMP_ERR_VALUE,
			OIL_TEMP_HYSTERESIS, false, ESB_EMCY_OTEMP_ERROR);

	// fuel level
	sensor_init(&this->fuel_level, FUEL_LEVEL_AIN, FUEL_LEVEL_AVG_COUNT,
			ESB_EMCY_FLEVEL_FAULT, &adc_get_level);
	sensor_set_warning(&this->fuel_level, FUEL_LEVEL_WARN_VALUE,
			FUEL_LEVEL_HYSTERESIS, true, ESB_EMCY_FLEVEL_WARNING);
	sensor_set_error(&this->fuel_level, FUEL_LEVEL_ERR_VALUE,
			FUEL_LEVEL_HYSTERESIS, true, ESB_EMCY_FLEVEL_ERROR);

	// oil level
	sensor_init(&this->oil_level, OIL_LEVEL_AIN, OIL_LEVEL_AVG_COUNT,
			ESB_EMCY_OLEVEL_SENSOR_FAULT, &adc_get_level);
	sensor_set_warning(&this->oil_level, OIL_LEVEL_WARN_VALUE,
			OIL_LEVEL_HYSTERESIS, true, ESB_EMCY_OLEVEL_WARNING);
	sensor_set_error(&this->oil_level, OIL_LEVEL_ERR_VALUE,
			OIL_LEVEL_HYSTERESIS, true, ESB_EMCY_OLEVEL_ERROR);

	// vdd
	uv_moving_aver_init(&this->vdd_avg, VDD_AVG_COUNT);
	uv_hysteresis_init(&this->vdd_warning, VDD_WARN_VALUE_MV,
			VDD_WARN_HYSTERESIS_MV, true);
	this->vdd = 0;
	this->vdd_warn_req = true;

	this->motor_water_temp = 0;
	this->motor_oil_press = 0;
	this->alt_p_rpm = 0;
	// start RPM timer
	uv_timer_init(RPM_TIMER);
	uv_timer_start(RPM_TIMER);

	uv_delay_init(&this->motor_delay, MOTOR_DELAY_MS);

	this->pwr.last_usage = 0;
	this->pwr.usage = 0;
	uv_pid_init(&this->pwr.pid, this->pwr_rising_p, 0, 0);
	this->pwr.pump_angle = PWR_USAGE_MAX;



	//init terminal and pass application terminal commands array as a parameter
	uv_terminal_init(terminal_commands, commands_size());

	this->fsb.ignkey_state = FSB_IGNKEY_STATE_OFF;
	this->fsb.emcy = 0;
	this->ecu.hydr_pressure = 0;

	this->ac_override = false;

	uv_canopen_set_state(CANOPEN_OPERATIONAL);

}




/// @brief: PT100 resistor teaching values in milliohms
#define PT100_RES_0C_MOHM		100000
#define PT100_RES_100C_MOHM		139000

/// @brief: Indicates the ADC reading when PT100 sensor is
/// in series with 1k5 resistor (voltage divider) and that
/// voltage is amplified by 11 (op amp with 10k + 1k negative feedback)
#define PT100_ADC_0C			2816
#define PT100_ADC_100C			3821
/// @brief: Returns the ADC's read value as celsius degrees
bool adc_get_temp(uv_adc_channels_e adc_chn, int16_t *dest) {
	int32_t adc = uv_adc_read(adc_chn);
	bool ret = true;
	if (!dest) {
		ret = false;
	}
	else {
		int32_t t = uv_reli(adc, PT100_ADC_0C, PT100_ADC_100C);
		int16_t result_c = uv_lerpi(t, 0, 100);
		if ((result_c > -50) && (result_c < 200)) {
			*dest = result_c;
		}
		else {
			ret = false;
		}
	}
	return ret;
}




#define LEVEL_0_MV				0
#define LEVEL_100_MV			500
/// @brief: Reads the adc channel and converts it to liquid level percentage
bool adc_get_level(uv_adc_channels_e adc_chn, int16_t *dest) {
	bool ret = true;
	int64_t mv = adc_get_voltage_mv(adc_chn);
	if ((mv >= (LEVEL_100_MV * 2)) || (!dest)) {
		ret = false;
	}
	else {
		int32_t t = uv_reli(mv, LEVEL_0_MV, LEVEL_100_MV);
		*dest = uv_lerpi(t, 0, 100);
	}
	return ret;
}




uint16_t adc_get_voltage_mv(const uv_adc_channels_e adc_chn) {
	int32_t adc = uv_adc_read(adc_chn);
	return adc * 3300 / ADC_MAX_VALUE;
}

void rpm_callb(uv_gpios_e gpio) {
	uint32_t us = uv_timer_get_us(RPM_TIMER);
	uv_timer_clear(RPM_TIMER);
	if (us != 0) {
		uint32_t freq = 1000000 / us;
		this->alt_p_rpm = freq * 5.5f;
	}
}



void step(void* me) {

	init(this);

	while (true) {
		unsigned int step_ms = 2;
		// update watchdog timer value to prevent a hard reset
		// uw_wdt_update();

		uv_output_step(&this->glow, step_ms);
		uv_output_step(&this->starter, step_ms);
		uv_output_step(&this->ac, step_ms);
		uv_output_step(&this->engine_start1, step_ms);
		uv_output_step(&this->engine_start2,step_ms);
		uv_output_step(&this->alt_ig, step_ms);
		uv_output_step(&this->oilcooler, step_ms);
		uv_solenoid_output_step(&this->pump, step_ms);


		// terminal step function
		uv_terminal_step();

		this->total_current = uv_output_get_current(&this->glow) +
				uv_output_get_current(&this->starter) +
				uv_output_get_current(&this->ac) +
				uv_output_get_current(&this->engine_start1) +
				uv_output_get_current(&this->engine_start2) +
				uv_output_get_current(&this->alt_ig) +
				uv_output_get_current(&this->oilcooler) +
				uv_solenoid_output_get_current(&this->pump);

		// motor temperature
		sensor_step(&this->motor_temp, step_ms);
		sensor_step(&this->oil_temp, step_ms);
		sensor_step(&this->fuel_level, step_ms);
		sensor_step(&this->oil_level, step_ms);

		// kubota sensors
		this->motor_water_temp = GET_MOTOR_WATER();
		this->motor_oil_press = GET_MOTOR_OIL_PRESS();
		this->alt_l = !uv_gpio_get(ALT_L_I);

		// vdd voltage
		// note: Multiplier 11 comes from 10k/1k voltage divider resistors
		this->vdd = uv_moving_aver_step(&this->vdd_avg,
				adc_get_voltage_mv(VDD_SENSE_AIN) * 11);
		// round vdd up
		this->vdd /= 100;
		this->vdd *= 100;
		// warning when VDD is too low
		if (uv_hysteresis_step(&this->vdd_warning, this->vdd)) {
			if (this->vdd_warn_req &&
					(this->fsb.ignkey_state != FSB_IGNKEY_STATE_PREHEAT) &&
					(this->fsb.ignkey_state != FSB_IGNKEY_STATE_START)) {
				uv_canopen_emcy_send(CANOPEN_EMCY_DEVICE_SPECIFIC, ESB_EMCY_VDD_LOW_WARNING);
			}
			this->vdd_warn_req = false;
		}
		else {
			this->vdd_warn_req = true;
		}


		// rpm
		uint32_t val = uv_timer_get_us(RPM_TIMER);
		// more than second has passed since last pulse
		if (val > 1000000) {
			this->alt_p_rpm = 0;
			uv_timer_clear(RPM_TIMER);
		}

		// **** power usage ****

		if (this->ecu.hydr_pressure == 0) {
			// prevent dividing with zero
			this->ecu.hydr_pressure = 1;
		}
		this->pwr.usage = (int32_t) this->alt_p_rpm * this->alt_p_rpm / this->ecu.hydr_pressure;
		// add user calibration parameter into calculations
		this->pwr.usage = this->pwr.usage * this->engine_power_usage / ENGINE_POWER_USAGE_DEFAULT;
		if (this->pwr.usage > PWR_USAGE_MAX) {
			this->pwr.usage = PWR_USAGE_MAX;
		}
		if (this->pwr.usage < this->pwr.last_usage) {
			this->pwr.pump_angle = this->pwr.usage;
		}
		else {
			// slow P controller
			uv_pid_set_p(&this->pwr.pid, this->pwr_rising_p);
			uv_pid_set_target(&this->pwr.pid, this->pwr.usage);
			uv_pid_step(&this->pwr.pid, step_ms, this->pwr.pump_angle);
			this->pwr.pump_angle += uv_pid_get_output(&this->pwr.pid);
		}
		if (this->pwr.pump_angle > PWR_USAGE_MAX) {
			this->pwr.pump_angle = PWR_USAGE_MAX;
		}
		int32_t rel = uv_reli(this->pwr.pump_angle, 0, PWR_USAGE_MAX);
		int32_t result = uv_lerpi(rel, PUMP_CURRENT_MIN_MA, PUMP_CURRENT_MAX_MA);
		// set the pump solenoid output based on the power usage calculations
//		uv_solenoid_output_set(&this->pump, result);
		this->pwr.last_usage = this->pwr.usage;




		// **** ignition key states ****

		if (this->fsb.ignkey_state == FSB_IGNKEY_STATE_ON) {
			if (uv_output_get_current(&this->engine_start1) < 200) {
				uv_output_set_state(&this->engine_start1, OUTPUT_STATE_OFF);
			}
			// too big solenoid current might indicate a mismatch in solenoids
			else if (uv_output_get_current(&this->engine_start1) > 2000) {
				uv_output_set_state(&this->engine_start1, OUTPUT_STATE_OFF);
			}
			else {

			}
			if (uv_output_get_current(&this->engine_start2) < 200) {
				uv_output_set_state(&this->engine_start2, OUTPUT_STATE_OFF);
			}
			// too big solenoid current might indicate a mismatch in solenoids
			else if (uv_output_get_current(&this->engine_start2) > 2000) {
				uv_output_set_state(&this->engine_start2, OUTPUT_STATE_OFF);
			}
			else {

			}
		}
		else if ((this->fsb.ignkey_state == FSB_IGNKEY_STATE_START) ||
				(this->fsb.ignkey_state == FSB_IGNKEY_STATE_PREHEAT)) {
			uv_output_set_state(&this->engine_start1, OUTPUT_STATE_ON);
			uv_output_set_state(&this->engine_start2, OUTPUT_STATE_ON);
		}
		else {
			uv_output_set_state(&this->engine_start1, OUTPUT_STATE_OFF);
			uv_output_set_state(&this->engine_start2, OUTPUT_STATE_OFF);
		}

		// motor sensor shut down
		if (this->fsb.ignkey_state == FSB_IGNKEY_STATE_ON) {
			if (this->motor_water_temp ||
					this->motor_oil_press) {
				if (uv_delay(&this->motor_delay, step_ms)) {
					uv_output_set_state(&this->engine_start1, OUTPUT_STATE_OFF);
					uv_output_set_state(&this->engine_start2, OUTPUT_STATE_OFF);
					// send EMCY message from motor protection
					uv_canopen_emcy_send(CANOPEN_EMCY_DEVICE_SPECIFIC,
							ESB_EMCY_ENGINE_PROTECTION_SHUTDOWN);
				}
			}
			else {
				uv_delay_init(&this->motor_delay, MOTOR_DELAY_MS);
			}
		}


		// glow is active only when ignition key is in PREHEAT position
		uv_output_set_state(&this->glow,
				(this->fsb.ignkey_state == FSB_IGNKEY_STATE_PREHEAT) ?
						OUTPUT_STATE_ON : OUTPUT_STATE_OFF);

		// starter is active only when ignition key is in START position
		uv_output_set_state(&this->starter,
				(this->fsb.ignkey_state == FSB_IGNKEY_STATE_START) ?
				OUTPUT_STATE_ON : OUTPUT_STATE_OFF);

		// ac is controlled by CSB when ignition key is in ON position
		uv_output_state_e state;
		if (this->ac_override) {
			// state machine override from terminal
			state = OUTPUT_STATE_ON;
		}
		else if (this->fsb.ignkey_state != FSB_IGNKEY_STATE_ON) {
			// ignition key state
			state = OUTPUT_STATE_OFF;
		}
		else {
			// csb request
			state = (this->csb.ac_req) ? OUTPUT_STATE_ON : OUTPUT_STATE_OFF;
		}
		uv_output_set_state(&this->ac, state);

		// alternator ignition is on if engine is running and starter is not running
		uv_output_set_state(&this->alt_ig,
				(this->fsb.ignkey_state == FSB_IGNKEY_STATE_ON) ?
				OUTPUT_STATE_ON : OUTPUT_STATE_OFF);

		// oil cooler control
		uv_hysteresis_set_trigger_value(&this->oil_temp_hyst, this->oilcooler_trigger_temp);
		uv_hysteresis_step(&this->oil_temp_hyst, sensor_get_value(&this->oil_temp));
		uv_output_set_state(&this->oilcooler, (uv_hysteresis_get_output(&this->oil_temp_hyst)) ?
				OUTPUT_STATE_ON : OUTPUT_STATE_OFF);

		// if FSB heartbeat message is not received in a given time,
		// it indicates that FSB is not in the system. As FSB takes care of the EMCY switch,
		// the best practice would be to assume that the EMCY switch is turned on.
		if (uv_canopen_heartbeat_producer_is_expired(FSB_NODE_ID)) {
			this->fsb.ignkey_state = FSB_IGNKEY_STATE_OFF;
			this->fsb.emcy = 1;
		}

		// emcy
		if (this->fsb.emcy) {
			uv_output_set_state(&this->glow, OUTPUT_STATE_OFF);
			uv_output_set_state(&this->starter, OUTPUT_STATE_OFF);
			uv_output_set_state(&this->ac, OUTPUT_STATE_OFF);
			uv_output_set_state(&this->engine_start1, OUTPUT_STATE_OFF);
			uv_output_set_state(&this->engine_start2, OUTPUT_STATE_OFF);
			uv_output_set_state(&this->alt_ig, OUTPUT_STATE_OFF);
			uv_output_set_state(&this->oilcooler, OUTPUT_STATE_OFF);
			uv_solenoid_output_set_state(&this->pump, OUTPUT_STATE_OFF);
		}

		uv_rtos_task_delay(step_ms);
	}
}






int main(void) {

	// init the watchdog timer
//	uw_wdt_init(5);

	uv_init(&dev);

	uv_rtos_task_create(step, "step", UV_RTOS_MIN_STACK_SIZE * 5,
			&dev, UV_RTOS_IDLE_PRIORITY + 1, NULL);


	uv_rtos_start_scheduler();


    // Enter an infinite loop
	// never should end up here
    while(1) {
    }
    return 0;
}
