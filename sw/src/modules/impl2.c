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





#include "impl2.h"
#include "main.h"
#include "pin_mappings.h"
#include <uv_rtos.h>


void impl2_conf_reset(impl2_conf_st *this) {
	this->out_conf.acc = 100;
	this->out_conf.dec = 100;
	this->out_conf.invert = false;
	this->out_conf.assembly_invert = false;
	this->out_conf.solenoid_conf[DUAL_OUTPUT_SOLENOID_A].max_ma = 2000;
	this->out_conf.solenoid_conf[DUAL_OUTPUT_SOLENOID_A].min_ma = 600;
	this->out_conf.solenoid_conf[DUAL_OUTPUT_SOLENOID_B].max_ma = 2000;
	this->out_conf.solenoid_conf[DUAL_OUTPUT_SOLENOID_B].min_ma = 600;
}


void impl2_init(impl2_st *this, impl2_conf_st *conf_ptr) {
	input_init(&this->input);
	this->conf = conf_ptr;

	uv_dual_solenoid_output_init(&this->out1, &conf_ptr->out_conf, IMPL2_1_PWMA,
			IMPL2_1_PWMB, IMPL2_1_SENSE, dev.dither_freq, dev.dither_ampl,
			VND5050_CURRENT_AMPL_UA, SOLENOID_MAX_CURRENT, SOLENOID_FAULT_CURRENT,
			HCU_EMCY_IMPL2_1_OVERLOAD_A, HCU_EMCY_IMPL2_1_OVERLOAD_B,
			HCU_EMCY_IMPL2_1_FAULT_A, HCU_EMCY_IMPL2_1_FAULT_B);

	uv_dual_solenoid_output_init(&this->out2, &conf_ptr->out_conf, IMPL2_2_PWMA,
			IMPL2_2_PWMB, IMPL2_2_SENSE, dev.dither_freq, dev.dither_ampl,
			VND5050_CURRENT_AMPL_UA, SOLENOID_MAX_CURRENT, SOLENOID_FAULT_CURRENT,
			HCU_EMCY_IMPL2_2_OVERLOAD_A, HCU_EMCY_IMPL2_2_OVERLOAD_B,
			HCU_EMCY_IMPL2_2_FAULT_A, HCU_EMCY_IMPL2_2_FAULT_B);
}


void impl2_step(impl2_st *this, uint16_t step_ms) {
	input_step(&this->input, step_ms);

	uv_disable_int();
	if (dev.implement == HCU_IMPLEMENT_UW50) {
		// remap request to right joystick z
		canopen_pdo_mapping_parameter_st *map =
				uv_canopen_rxpdo_get_mapping(CANOPEN_TXPDO1_ID + RKEYPAD_NODE_ID);
		if (map != NULL &&
				map->mappings[4].main_index != HCU_IMPL2_REQ_INDEX) {
			map->mappings[4].main_index = HCU_IMPL2_REQ_INDEX;
			map->mappings[4].sub_index = HCU_IMPL2_REQ_SUBINDEX;
		}
	}
	else if (dev.implement != HCU_IMPLEMENT_UW100) {
		// make sure request is not mapped to right joystick z. It will stay mapped in RXPDO.
		canopen_pdo_mapping_parameter_st *map =
				uv_canopen_rxpdo_get_mapping(CANOPEN_TXPDO1_ID + RKEYPAD_NODE_ID);
		if (map != NULL &&
				map->mappings[4].main_index != 0) {
			map->mappings[4].main_index = 0;
			map->mappings[4].sub_index = 0;
		}
	}
	else {

	}
	uv_enable_int();


	uv_dual_solenoid_output_set(&this->out1, input_get_request(&this->input, &this->conf->out_conf));
	uv_dual_solenoid_output_set(&this->out2, input_get_request(&this->input, &this->conf->out_conf));



}

