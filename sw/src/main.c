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
#include <string.h>
#include <uv_eeprom.h>

dev_st dev = {};
static bool initialized = false;
#define this ((dev_st*) &dev)


uv_mutex_st mutex;

int16_t get_pressure(uv_adc_channels_e adc) {
	int32_t ret = (int64_t) uv_adc_read(PRESS_SENSE) * 3300000 / (ADC_MAX_VALUE * 75);

	int32_t rel = uv_reli(ret, 4000, 20000);

	ret = uv_lerpi(rel, 0, PRESS_SENSOR_MAX_BAR);

	return ret;
}


void init(dev_st* me) {
	// load non-volatile data
	if (uv_memory_load()) {

		this->dither_ampl = DITHER_AMPL_DEF;
		this->dither_freq = DITHER_FREQ_DEF;

		this->implement = HCU_IMPLEMENT_UW180S;

		boom_rotate_conf_reset(&this->boom_rotate_conf);
		boom_lift_conf_reset(&this->boom_lift_conf);
		boom_fold_conf_reset(&this->boom_fold_conf);
		boom_telescope_conf_reset(&this->boom_telescope_conf);
		left_foot_conf_reset(&this->left_foot_conf);
		right_foot_conf_reset(&this->right_foot_conf);
		rotator_conf_reset(&this->rotator_conf);
		impl1_conf_reset(&this->impl1_conf);
		impl2_conf_reset(&this->impl2_conf);

		// initialize non-volatile memory to default settings
		uv_memory_save();
	}

	this->total_current = 0;
	uv_sensor_init(&this->pressure, PRESS_SENSE, PRESS_MOVING_AVG_COUNT, &get_pressure);
	uv_sensor_set_fault(&this->pressure, PRESS_FAULT_MIN_VALUE_UA, PRESS_FAULT_MAX_VALUE_UA,
			PRESS_FAULT_HYSTERESIS_UA, HCU_EMCY_PRESSURE_SENSOR_FAULT);

	uv_eeprom_read(&this->assembly, sizeof(this->assembly), ASSEMBLY_EEPROM_ADDR);
	this->assembly_write = 0;

	this->fsb.door_sw1 = 0;
	this->fsb.door_sw2 = 0;
	this->fsb.seat_sw = 0;
	this->fsb.emcy = 0;
	this->fsb.ignkey_state = FSB_IGNKEY_STATE_OFF;

	this->ccu.drive_req = 0;

	if (this->implement >= HCU_IMPLEMENT_COUNT) {
		this->implement = HCU_IMPLEMENT_UW180S;
	}

	boom_rotate_init(&this->boom_rotate, &this->boom_rotate_conf);
	boom_lift_init(&this->boom_lift, &this->boom_lift_conf);
	boom_fold_init(&this->boom_fold, &this->boom_fold_conf);
	boom_telescope_init(&this->boom_telescope, &this->boom_telescope_conf);
	left_foot_init(&this->left_foot, &this->left_foot_conf);
	right_foot_init(&this->right_foot, &this->right_foot_conf);
	rotator_init(&this->rotator, &this->rotator_conf);
	impl1_init(&this->impl1, &this->impl1_conf);
	impl2_init(&this->impl2, &this->impl2_conf);
	d4wd_init(&this->d4wd);

	uv_terminal_enable();

	uv_terminal_init(terminal_commands, commands_size());

	uv_canopen_set_state(CANOPEN_OPERATIONAL);

	uv_mutex_init(&mutex);

	initialized = true;
}



void solenoid_step(void* me) {

	// wait until solenoid structures have been initialized
	while (!initialized) {
		uv_rtos_task_delay(1);
	}

	while (true) {
		uint32_t step_ms = 2;

		uv_mutex_lock(&mutex);

		boom_rotate_solenoid_step(&this->boom_rotate, step_ms);
		boom_lift_solenoid_step(&this->boom_lift, step_ms);
		boom_fold_solenoid_step(&this->boom_fold, step_ms);
		boom_telescope_solenoid_step(&this->boom_telescope, step_ms);
		left_foot_solenoid_step(&this->left_foot, step_ms);
		right_foot_solenoid_step(&this->right_foot, step_ms);
		rotator_solenoid_step(&this->rotator, step_ms);
		impl1_solenoid_step(&this->impl1, step_ms);
		impl2_solenoid_step(&this->impl2, step_ms);
		d4wd_solenoid_step(&this->d4wd, step_ms);

		uv_mutex_unlock(&mutex);

		uv_rtos_task_delay(step_ms);
	}
}


void step(void* me) {

	init(this);

	while (true) {
		unsigned int step_ms = 20;

		// update watchdog timer value to prevent a hard reset
		// uw_wdt_update();

		// terminal step function
		uv_terminal_step();

		if (this->assembly_write) {
			uv_eeprom_write(&this->assembly, sizeof(this->assembly), ASSEMBLY_EEPROM_ADDR);
			this->assembly_write = 0;
		}

		// hydraulic pressure
		uv_sensor_step(&this->pressure, step_ms);

		this->total_current = abs(boom_rotate_get_current(&this->boom_rotate)) +
				abs(boom_lift_get_current(&this->boom_lift)) +
				abs(boom_fold_get_current(&this->boom_fold)) +
				abs(boom_telescope_get_current(&this->boom_telescope)) +
				abs(left_foot_get_current(&this->left_foot)) +
				abs(right_foot_get_current(&this->right_foot)) +
				abs(rotator_get_current(&this->rotator)) +
				abs(impl1_get_current(&this->impl1)) +
				abs(impl2_get_current(&this->impl2)) +
				abs(d4wd_get_current(&this->d4wd));


		uv_mutex_lock(&mutex);

		boom_rotate_step(&this->boom_rotate, step_ms);
		boom_lift_step(&this->boom_lift, step_ms);
		boom_fold_step(&this->boom_fold, step_ms);
		boom_telescope_step(&this->boom_telescope, step_ms);
		left_foot_step(&this->left_foot, step_ms);
		right_foot_step(&this->right_foot, step_ms);
		rotator_step(&this->rotator, step_ms);
		impl1_step(&this->impl1, step_ms);
		impl2_step(&this->impl2, step_ms);
		d4wd_step(&this->d4wd, step_ms);

		uv_mutex_unlock(&mutex);


		// if keypad heartbeat messages are not received, input from that keypad is set to zero
		if (uv_canopen_heartbeat_producer_is_expired(LKEYPAD_NODE_ID)) {
		}
		else if (uv_canopen_heartbeat_producer_get_state(LKEYPAD_NODE_ID) != CANOPEN_OPERATIONAL) {
			uv_canopen_command(LKEYPAD_NODE_ID, CANOPEN_NMT_START_NODE);
		}
		else {

		}

		if (uv_canopen_heartbeat_producer_is_expired(RKEYPAD_NODE_ID)) {
		}
		else if (uv_canopen_heartbeat_producer_get_state(RKEYPAD_NODE_ID) != CANOPEN_OPERATIONAL) {
			uv_canopen_command(RKEYPAD_NODE_ID, CANOPEN_NMT_START_NODE);
		}
		else {

		}

		// outputs are disables if FSB is not found, ignition key is not in ON state,
		// or emergency switch is pressed
		if (uv_canopen_heartbeat_producer_is_expired(FSB_NODE_ID) ||
				uv_canopen_heartbeat_producer_is_expired(LKEYPAD_NODE_ID) ||
				uv_canopen_heartbeat_producer_is_expired(RKEYPAD_NODE_ID) ||
				(this->fsb.ignkey_state != FSB_IGNKEY_STATE_ON) ||
				this->fsb.emcy ||
				!this->fsb.seat_sw) {
			// disable all outputs
			boom_rotate_disable(&this->boom_rotate);
			boom_lift_disable(&this->boom_lift);
			boom_fold_disable(&this->boom_fold);
			boom_telescope_disable(&this->boom_telescope);
			left_foot_disable(&this->left_foot);
			right_foot_disable(&this->right_foot);
			rotator_disable(&this->rotator);
			impl1_disable(&this->impl1);
			impl2_disable(&this->impl2);
			d4wd_disable(&this->d4wd);
		}
		else {
			// enable outputs
			boom_rotate_enable(&this->boom_rotate);
			boom_lift_enable(&this->boom_lift);
			boom_fold_enable(&this->boom_fold);
			boom_telescope_enable(&this->boom_telescope);
			left_foot_enable(&this->left_foot);
			right_foot_enable(&this->right_foot);
			rotator_enable(&this->rotator);
			impl1_enable(&this->impl1);
			impl2_enable(&this->impl2);
			d4wd_enable(&this->d4wd);
		}

		uv_rtos_task_delay(step_ms);
	}
}



void hardfault_callback(void) {
	// we end up here if hardfault happened
	printf("Hardfault! Resetting the device...\n");

	boom_rotate_disable(&this->boom_rotate);
	boom_lift_disable(&this->boom_lift);
	boom_fold_disable(&this->boom_fold);
	boom_telescope_disable(&this->boom_telescope);
	left_foot_disable(&this->left_foot);
	right_foot_disable(&this->right_foot);
	rotator_disable(&this->rotator);
	impl1_disable(&this->impl1);
	impl2_disable(&this->impl2);
	d4wd_disable(&this->d4wd);
}



int main(void) {

	// init the watchdog timer
//	uw_wdt_init(5);

	uv_init(&dev);


	uv_rtos_task_create(&step, "step", UV_RTOS_MIN_STACK_SIZE * 3,
			&dev, UV_RTOS_IDLE_PRIORITY + 1, NULL);

	uv_rtos_task_create(&solenoid_step, "solenoid", UV_RTOS_MIN_STACK_SIZE * 2,
			&dev, UV_RTOS_IDLE_PRIORITY + 2, NULL);


	uv_rtos_start_scheduler();


    // Enter an infinite loop
	// never should end up here
    while(1) {
    }
    return 0;
}
