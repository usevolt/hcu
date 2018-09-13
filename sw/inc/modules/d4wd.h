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


#ifndef INC_MODULES_D4WD_H_
#define INC_MODULES_D4WD_H_

#include <uv_utilities.h>
#include <uv_output.h>
#include "input.h"


typedef struct {
	uv_output_state_e req;

	uv_output_st out;

} d4wd_st;


/// @brief: Initializes the module
void d4wd_init(d4wd_st *this);


/// @brief: Step function
void d4wd_step(d4wd_st *this, uint16_t step_ms);


static inline int16_t d4wd_get_current(d4wd_st *this) {
	return uv_output_get_current(&this->out);
}

/// @brief: Step function for the solenoid driver module. Should be called
/// with a smaller step cycle from a higher priority thread than the main module.
static inline void d4wd_solenoid_step(d4wd_st *this, uint16_t step_ms) {
	uv_output_step(&this->out, step_ms);
}




/// @brief: Disables the boom fold module
static inline void d4wd_disable(d4wd_st *this) {
	uv_output_disable(&this->out);
	this->req = OUTPUT_STATE_OFF;
}


/// @brief: Enables the boom fold module
static inline void d4wd_enable(d4wd_st *this) {
	uv_output_enable(&this->out);
}



#endif /* INC_MODULES_D4WD_H_ */
