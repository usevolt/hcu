/*
 * sensor.h
 *
 *  Created on: Sep 7, 2017
 *      Author: usevolt
 */

#ifndef SENSOR_H_
#define SENSOR_H_

#include "can_esb.h"
#include <uv_filters.h>
#include <uv_adc.h>



enum {
	SENSOR_STATE_OK,
	SENSOR_STATE_WARNING,
	SENSOR_STATE_ERROR,
	SENSOR_STATE_FAULT
};
typedef uint8_t sensor_state_e;


/// @file: Implements a module for reading analog sensor data
typedef struct {
	uv_moving_aver_st avg;
	int16_t value;
	bool hyst_warning_enabled;
	bool hyst_error_enabled;
	sensor_state_e state;
	uv_hysteresis_st hyst_warning;
	esb_emcy_e emcy_warning;
	uv_hysteresis_st hyst_error;
	esb_emcy_e emcy_error;
	esb_emcy_e emcy_fault;
	uv_adc_channels_e adc;
	bool (*get_data)(uv_adc_channels_e chn, int16_t *dest);
} sensor_st;



void sensor_init(sensor_st *this, uv_adc_channels_e adc_chn, uint16_t avg_count,
		esb_emcy_e emcy_fault, bool (*get_data_ptr)(uv_adc_channels_e chn, int16_t *dest));

void sensor_set_warning(sensor_st *this, int16_t trigger_value, int16_t hysteresis,
		bool invert, esb_emcy_e emcy_warning);

void sensor_set_error(sensor_st *this, int16_t trigger_value, int16_t hysteresis,
		bool invert, esb_emcy_e emcy_error);

void sensor_step(sensor_st *this, uint16_t step_ms);

static inline int16_t sensor_get_value(const sensor_st *this) {
	return this->value;
}

static inline sensor_state_e sensor_get_state(const sensor_st *this) {
	return this->state;
}



#endif /* SENSOR_H_ */
