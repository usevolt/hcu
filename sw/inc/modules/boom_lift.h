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


#ifndef INC_MODULES_BOOM_LIFT_H_
#define INC_MODULES_BOOM_LIFT_H_

#include <uv_utilities.h>
#include <uv_dual_solenoid_output.h>
#include "input.h"

/// @brief: Boom lift configuration settings. Should be stored in non-volatile memory
typedef struct {
	uv_dual_solenoid_output_conf_st out_conf;
} boom_lift_conf_st;

/// @brief: Resets the non-volatile settings to defaults
void boom_lift_conf_reset(boom_lift_conf_st *this);


typedef struct {
	// input module from the CAN-bus
	input_st input;

	uv_dual_solenoid_output_st out;

	boom_lift_conf_st *conf;

} boom_lift_st;


/// @brief: Initializes the module
void boom_lift_init(boom_lift_st *this, boom_lift_conf_st *conf_ptr);


/// @brief: Step function
void boom_lift_step(boom_lift_st *this, uint16_t step_ms);



static inline int16_t boom_lift_get_current(boom_lift_st *this) {
	return uv_dual_solenoid_output_get_current(&this->out);
}

/// @brief: Step function for the solenoid driver module. Should be called
/// with a smaller step cycle from a higher priority thread than the main module.
static inline void boom_lift_solenoid_step(boom_lift_st *this, uint16_t step_ms) {
	uv_dual_solenoid_output_step(&this->out, step_ms);
}




/// @brief: Disables the boom lift module
static inline void boom_lift_disable(boom_lift_st *this) {
	uv_dual_solenoid_output_disable(&this->out);
}


/// @brief: Enables the boom lift module
static inline void boom_lift_enable(boom_lift_st *this) {
	uv_dual_solenoid_output_enable(&this->out);
}


#endif /* INC_MODULES_BOOM_LIFT_H_ */
