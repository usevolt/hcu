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


#include "boom_lift.h"
#include "main.h"
#include "pin_mappings.h"


void boom_lift_conf_reset(boom_lift_conf_st *this) {
	this->out_conf.acc = 40;
	this->out_conf.dec = 40;
	this->out_conf.invert = true;
	this->out_conf.assembly_invert = false;
	this->out_conf.solenoid_conf[DUAL_OUTPUT_SOLENOID_A].max_ma = 600;
	this->out_conf.solenoid_conf[DUAL_OUTPUT_SOLENOID_A].min_ma = 150;
	this->out_conf.solenoid_conf[DUAL_OUTPUT_SOLENOID_B].max_ma = 600;
	this->out_conf.solenoid_conf[DUAL_OUTPUT_SOLENOID_B].min_ma = 90;
}



void boom_lift_init(boom_lift_st *this, boom_lift_conf_st *conf_ptr) {
	input_init(&this->input);

	this->conf = conf_ptr;

	uv_dual_solenoid_output_init(&this->out, &conf_ptr->out_conf, BOOM_LIFT_PWMA,
			BOOM_LIFT_PWMB, BOOM_LIFT_SENSE, dev.dither_freq, dev.dither_ampl,
			VND5050_CURRENT_AMPL_UA, SOLENOID_MAX_CURRENT, SOLENOID_FAULT_CURRENT,
			HCU_EMCY_BOOM_LIFT_OVERLOAD_A, HCU_EMCY_BOOM_LIFT_OVERLOAD_B,
			HCU_EMCY_BOOM_LIFT_FAULT_A, HCU_EMCY_BOOM_LIFT_FAULT_B);

}


void boom_lift_step(boom_lift_st *this, uint16_t step_ms) {


	input_step(&this->input, step_ms);

	uv_dual_solenoid_output_set(&this->out, input_get_request(&this->input, &this->conf->out_conf));

}
