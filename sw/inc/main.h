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
#include <uv_dual_solenoid_output.h>
#include <uv_sensor.h>
#include "can_fsb.h"
#include "boom_rotate.h"
#include "boom_lift.h"
#include "boom_fold.h"
#include "boom_telescope.h"
#include "left_foot.h"
#include "right_foot.h"
#include "rotator.h"
#include "impl1.h"
#include "impl2.h"


#define VND5050_CURRENT_AMPL_UA		1619
#define VN5E01_CURRENT_AMPL_UA		13923

#define DITHER_AMPL_DEF				0
#define DITHER_FREQ_DEF				50

#define SOLENOID_MAX_CURRENT		4000
#define SOLENOID_FAULT_CURRENT		5000

#define PRESS_SENSOR_MAX_BAR		400
#define PRESS_MOVING_AVG_COUNT		100
#define PRESS_FAULT_HYSTERESIS_UA	3000
#define PRESS_FAULT_MIN_VALUE_UA	4000
#define PRESS_FAULT_MAX_VALUE_UA	20000

/// @brief: main data structure.
/// This struct can be save to non-volatile flash memory with
/// a terminal commmand 'save'.
typedef struct _dev_st {


	uint16_t total_current;

	// hydraulic pressure measured in bars
	uv_sensor_st pressure;

	boom_rotate_st boom_rotate;
	boom_lift_st boom_lift;
	boom_fold_st boom_fold;
	boom_telescope_st boom_telescope;
	left_foot_st left_foot;
	right_foot_st right_foot;
	rotator_st rotator;
	impl1_st impl1;
	impl2_st impl2;

	struct {
		fsb_ignkey_states_e ignkey_state;
		uint8_t emcy;
		uint8_t door_sw1;
		uint8_t door_sw2;
		uint8_t seat_sw;
	} fsb;

	// non-volatile data start
	uv_data_start_t data_start;

	uint16_t dither_freq;
	int16_t dither_ampl;

	hcu_impls_e implement;

	boom_rotate_conf_st boom_rotate_conf;
	boom_lift_conf_st boom_lift_conf;
	boom_fold_conf_st boom_fold_conf;
	boom_telescope_conf_st boom_telescope_conf;
	left_foot_conf_st left_foot_conf;
	right_foot_conf_st right_foot_conf;
	rotator_conf_st	rotator_conf;
	impl1_conf_st impl1_conf;
	impl2_conf_st impl2_conf;

	uv_data_end_t data_end;

} dev_st;


extern dev_st dev;


void step(void* me);

void init(dev_st* me);





#endif /* MAIN_H_ */
