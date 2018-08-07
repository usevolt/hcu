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


#ifndef INC_MODULES_IMPL2_H_
#define INC_MODULES_IMPL2_H_

#include <uv_utilities.h>
#include <uv_dual_solenoid_output.h>
#include "input.h"

/// @brief: Boom fold configuration settings. Should be stored in non-volatile memory
typedef struct {
	uv_dual_solenoid_output_conf_st out_conf;
} impl2_conf_st;

/// @brief: Resets the non-volatile settings to defaults
void impl2_conf_reset(impl2_conf_st *this);


typedef struct {
	// input module from the CAN-bus
	input_st input;

	uv_dual_solenoid_output_st out;

	impl2_conf_st *conf;

} impl2_st;


/// @brief: Initializes the module
void impl2_init(impl2_st *this, impl2_conf_st *conf_ptr);


/// @brief: Step function
void impl2_step(impl2_st *this, uint16_t step_ms);


static inline int16_t impl2_get_current(impl2_st *this) {
	return uv_dual_solenoid_output_get_current(&this->out);
}

/// @brief: Step function for the solenoid driver module. Should be called
/// with a smaller step cycle from a higher priority thread than the main module.
static inline void impl2_solenoid_step(impl2_st *this, uint16_t step_ms) {
	uv_dual_solenoid_output_step(&this->out, step_ms);
}


/// @brief: Manual way for setting the request. This can be used for implements
/// which dont have their own controllers, such as UW50 and UW100.
static inline void impl2_set_req(impl2_st *this, int8_t value) {
	this->input.request = value;
}



/// @brief: Disables the boom fold module
static inline void impl2_disable(impl2_st *this) {
	uv_dual_solenoid_output_disable(&this->out);
}


/// @brief: Enables the boom fold module
static inline void impl2_enable(impl2_st *this) {
	uv_dual_solenoid_output_enable(&this->out);
}



#endif /* INC_MODULES_IMPL2_H_ */
