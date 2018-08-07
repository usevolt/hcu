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





#include "right_foot.h"
#include "main.h"
#include "pin_mappings.h"


void right_foot_conf_reset(right_foot_conf_st *this) {
	this->out_conf.acc = 40;
	this->out_conf.dec = 40;
	this->out_conf.invert = false;
	this->out_conf.solenoid_conf[DUAL_OUTPUT_SOLENOID_A].max_ma = 1000;
	this->out_conf.solenoid_conf[DUAL_OUTPUT_SOLENOID_A].min_ma = 50;
	this->out_conf.solenoid_conf[DUAL_OUTPUT_SOLENOID_B].max_ma = 1000;
	this->out_conf.solenoid_conf[DUAL_OUTPUT_SOLENOID_B].min_ma = 80;
}


void right_foot_init(right_foot_st *this, right_foot_conf_st *conf_ptr) {
	input_init(&this->input);

	this->conf = conf_ptr;

	uv_dual_solenoid_output_init(&this->out, &conf_ptr->out_conf, RIGHT_FOOT_PWMA,
			RIGHT_FOOT_PWMB, RIGHT_FOOT_SENSE, dev.dither_freq, dev.dither_ampl,
			VND5050_CURRENT_AMPL_UA, SOLENOID_MAX_CURRENT, SOLENOID_FAULT_CURRENT,
			HCU_EMCY_RIGHT_FOOT_OVERLOAD_A, HCU_EMCY_RIGHT_FOOT_OVERLOAD_B,
			HCU_EMCY_RIGHT_FOOT_FAULT_A, HCU_EMCY_RIGHT_FOOT_FAULT_B);
}


void right_foot_step(right_foot_st *this, uint16_t step_ms) {
	input_step(&this->input, step_ms);

	uv_dual_solenoid_output_set(&this->out, input_get_request(&this->input));

}

