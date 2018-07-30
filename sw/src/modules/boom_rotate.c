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

#include "boom_rotate.h"
#include "main.h"
#include "pin_mappings.h"


void boom_rotate_conf_reset(boom_rotate_conf_st *this) {
	this->out_conf.acc = DUAL_SOLENOID_ACC_MAX;
	this->out_conf.dec = DUAL_SOLENOID_DEC_MAX;
	this->out_conf.invert = false;
	this->out_conf.solenoid_conf[DUAL_OUTPUT_SOLENOID_A].max_ma = 4000;
	this->out_conf.solenoid_conf[DUAL_OUTPUT_SOLENOID_A].min_ma = 250;
	this->out_conf.solenoid_conf[DUAL_OUTPUT_SOLENOID_B].max_ma = 4000;
	this->out_conf.solenoid_conf[DUAL_OUTPUT_SOLENOID_B].min_ma = 250;
}


void boom_rotate_init(boom_rotate_st *this, boom_rotate_conf_st *conf_ptr) {
	input_init(&this->input);
	this->conf = conf_ptr;

	uv_dual_solenoid_output_init(&this->out, BOOM_ROTATE_PWMA,
			BOOM_ROTATE_PWMB, BOOM_ROTATE_SENSE, dev.dither_freq, dev.dither_ampl,
			VND5050_CURRENT_AMPL_UA, SOLENOID_MAX_CURRENT, SOLENOID_FAULT_CURRENT,
			HCU_EMCY_BOOM_ROTATE_OVERLOAD_A, HCU_EMCY_BOOM_ROTATE_OVERLOAD_B,
			HCU_EMCY_BOOM_ROTATE_FAULT_A, HCU_EMCY_BOOM_ROTATE_FAULT_B);
	uv_dual_solenoid_output_set_conf(&this->out, &this->conf->out_conf);
}


void boom_rotate_step(boom_rotate_st *this, uint16_t step_ms) {
	input_step(&this->input, step_ms);

	uv_dual_solenoid_output_set_conf(&this->out, &this->conf->out_conf);

	uv_dual_solenoid_output_set(&this->out, input_get_request(&this->input));

}

