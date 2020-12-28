/* 
 * This file is part of the uv_hal distribution (www.usevolt.fi).
 * Copyright (c) 2017 Usevolt Oy.
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef INC_MODULES_IMPL1_H_
#define INC_MODULES_IMPL1_H_

#include <uv_utilities.h>
#include <uv_dual_solenoid_output.h>
#include "input.h"

/// @brief: Boom fold configuration settings. Should be stored in non-volatile memory
typedef struct {
	uv_dual_solenoid_output_conf_st out_conf;
} impl1_conf_st;

/// @brief: Resets the non-volatile settings to defaults
void impl1_conf_reset(impl1_conf_st *this);


typedef struct {
	// input module from the CAN-bus
	input_st input;

	uv_dual_solenoid_output_st out;

	impl1_conf_st *conf;

} impl1_st;


/// @brief: Initializes the module
void impl1_init(impl1_st *this, impl1_conf_st *conf_ptr);


/// @brief: Step function
void impl1_step(impl1_st *this, uint16_t step_ms);


static inline int16_t impl1_get_current(impl1_st *this) {
	return uv_dual_solenoid_output_get_current(&this->out);
}


/// @brief: Manual way for setting the request. This can be used for implements
/// which dont have their own controllers, such as UW50 and UW100.
static inline void impl1_set_req(impl1_st *this, int8_t value) {
	this->input.request = value;
}


/// @brief: Step function for the solenoid driver module. Should be called
/// with a smaller step cycle from a higher priority thread than the main module.
static inline void impl1_solenoid_step(impl1_st *this, uint16_t step_ms) {
	uv_dual_solenoid_output_step(&this->out, step_ms);
}



static inline uint8_t impl1_get_active(impl1_st *this) {
	return !!uv_dual_solenoid_output_get_target(&this->out);
}


/// @brief: Disables the boom fold module
static inline void impl1_disable(impl1_st *this) {
	uv_dual_solenoid_output_disable(&this->out);
	this->input.request = 0;
}


/// @brief: Enables the boom fold module
static inline void impl1_enable(impl1_st *this) {
	uv_dual_solenoid_output_enable(&this->out);
}



#endif /* INC_MODULES_IMPL1_H_ */
