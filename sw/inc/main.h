/*
 * main.h
 *
 *  Created on: Apr 26, 2015
 *      Author: usevolt
 */

#ifndef MAIN_H_
#define MAIN_H_


#include <uv_memory.h>
#include <uv_filters.h>
#include <uv_output.h>
#include <uv_solenoid_output.h>
#include "sensor.h"
#include "can_fsb.h"

/// brief: Delay for motor_oil_press and motor_water_temp
/// warning signals
#define MOTOR_DELAY_MS			10000


/// @brief: Motor temperature max limit in celsius.
/// Warning is generated after this has been exceeded
#define MOTOR_TEMP_WARN_VALUE		90
/// @brief: Motor temperature max limit in celsius.
/// Error is generated after this has been exceeded
#define MOTOR_TEMP_ERR_VALUE		95
#define MOTOR_TEMP_HYSTERESIS		2
#define MOTOR_TEMP_AVG_COUNT		100


/// @brief: Hydraulic oil temperature max limit in celsius.
/// Warning is generated after this has been exceeded
#define OIL_TEMP_WARN_VALUE			80
/// @brief: Motor temperature max limit in celsius.
/// Error is generated after this has been exceeded
#define OIL_TEMP_ERR_VALUE			90
#define OIL_TEMP_HYSTERESIS			4
#define OIL_TEMP_AVG_COUNT			100

/// @brief: Fuel level min limit in percents.
/// Warning is generated after this has been exceeded
#define FUEL_LEVEL_WARN_VALUE		30
/// @brief: fuel level min limit in percents.
/// Error is generated after this has been exceeded
#define FUEL_LEVEL_ERR_VALUE		5
#define FUEL_LEVEL_HYSTERESIS		10
#define FUEL_LEVEL_AVG_COUNT		100

/// @brief: Oil level min limit in percents.
/// Warning is generated after this has been exceeded
#define OIL_LEVEL_WARN_VALUE		50
/// @brief: oil level min limit in percents.
/// Error is generated after this has been exceeded
#define OIL_LEVEL_ERR_VALUE			50
#define OIL_LEVEL_HYSTERESIS		10
#define OIL_LEVEL_AVG_COUNT			100

#define VDD_AVG_COUNT				10
#define VDD_WARN_VALUE_MV			11000
#define VDD_WARN_HYSTERESIS_MV		500

#define OUTPUT_MOVING_AVG_COUNT		100

#define OIL_TEMP_HYSTERESIS_C				10
#define OIL_TEMP_DEFAULT_TRIGGER_VALUE_C	70

#define ENGINE_POWER_USAGE_DEFAULT	50
#define PUMP_CURRENT_MIN_MA			200
#define PUMP_CURRENT_MAX_MA			600
#define PWR_RISING_P_DEFAULT		10
#define PWR_USAGE_MAX				1000



/// @brief: main data structure.
/// This struct can be save to non-volatile flash memory with
/// a terminal command 'save'.
typedef struct _dev_st {

	uv_output_st glow;
	uv_output_st starter;
	uv_output_st ac;
	uv_output_st engine_start1;
	uv_output_st engine_start2;
	uv_output_st alt_ig;
	uv_output_st oilcooler;
	uv_solenoid_output_st pump;


	uint16_t total_current;

	sensor_st motor_temp;
	sensor_st oil_temp;
	sensor_st fuel_level;
	sensor_st oil_level;

	uv_hysteresis_st oil_temp_hyst;

	uint16_t alt_p_rpm;
	uint8_t alt_l;
	uint8_t motor_water_temp;
	uint8_t motor_oil_press;
	uv_delay_st motor_delay;

	uv_moving_aver_st vdd_avg;
	uv_hysteresis_st vdd_warning;
	uint16_t vdd;
	bool vdd_warn_req;

	struct {
		// stores the current power usage calculated from rpm and pressure
		int16_t usage;
		// last calculated value
		int16_t last_usage;
		// rising value pid controller
		uv_pid_st pid;
		// result value of the controller. 0...1000
		int16_t pump_angle;
	} pwr;


	struct {
		fsb_ignkey_states_e ignkey_state;
		uint8_t emcy;
	} fsb;
	struct {
		uint16_t hydr_pressure;
	} ecu;
	struct {
		uint8_t ac_req;
	} csb;

	uint8_t ac_override;


	// non-volatile data start
	uv_data_start_t data_start;

	int8_t oilcooler_trigger_temp;

	uint8_t engine_power_usage;
	// Kp factor for increasing the pump angle
	uint16_t pwr_rising_p;

	// PID Kp and Ki factors for the pump solenoid output
	uint16_t pump_i;
	uint16_t pump_p;

	/// @brief: Proportional solenoid dither frequency
	uint8_t dither_freq;
	/// @brief: Proportional solenoid dither amplitude
	uint16_t dither_ampl;

	uv_data_end_t data_end;

} dev_st;


void adc_callback(void);

void step(void* me);

void init(dev_st* me);





#endif /* MAIN_H_ */
