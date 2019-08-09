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

#include "boom_telescope.h"
#include "main.h"
#include "pin_mappings.h"
#include <uv_rtos.h>


void boom_telescope_conf_reset(boom_telescope_conf_st *this) {
	this->out_conf.acc = DUAL_SOLENOID_ACC_MAX;
	this->out_conf.dec = DUAL_SOLENOID_DEC_MAX;
	this->out_conf.invert = true;
	this->out_conf.assembly_invert = false;
	this->out_conf.solenoid_conf[DUAL_OUTPUT_SOLENOID_A].max_ma = 500;
	this->out_conf.solenoid_conf[DUAL_OUTPUT_SOLENOID_A].min_ma = 150;
	this->out_conf.solenoid_conf[DUAL_OUTPUT_SOLENOID_B].max_ma = 500;
	this->out_conf.solenoid_conf[DUAL_OUTPUT_SOLENOID_B].min_ma = 150;
}


void boom_telescope_init(boom_telescope_st *this, boom_telescope_conf_st *conf_ptr) {
	input_init(&this->input);
	this->conf = conf_ptr;

	uv_dual_solenoid_output_init(&this->out, &conf_ptr->out_conf, BOOM_TELESCOPE_PWMA,
			BOOM_TELESCOPE_PWMB, BOOM_TELESCOPE_SENSE, dev.dither_freq, dev.dither_ampl,
			VND5050_CURRENT_AMPL_UA, SOLENOID_MAX_CURRENT, SOLENOID_FAULT_CURRENT,
			HCU_EMCY_BOOM_TELESCOPE_OVERLOAD_A, HCU_EMCY_BOOM_TELESCOPE_OVERLOAD_B,
			HCU_EMCY_BOOM_TELESCOPE_FAULT_A, HCU_EMCY_BOOM_TELESCOPE_FAULT_B);
}


void boom_telescope_step(boom_telescope_st *this, uint16_t step_ms) {

	uv_disable_int();
	if (dev.implement == HCU_IMPLEMENT_UW180S ||
			dev.implement == HCU_IMPLEMENT_UW50) {
		// remap request to right joystick button7
		canopen_pdo_mapping_parameter_st *map =
				uv_canopen_rxpdo_get_mapping(CANOPEN_TXPDO2_ID + RKEYPAD_NODE_ID);
		if (map != NULL &&
				map->mappings[6].main_index != HCU_BOOM_TELESCOPE_REQ_INDEX) {
			map->mappings[6].main_index = HCU_BOOM_TELESCOPE_REQ_INDEX;
			map->mappings[6].sub_index = HCU_BOOM_TELESCOPE_REQ_SUBINDEX;
		}
		// make sure request is not on left joystick thumb
		if (dev.implement != HCU_IMPLEMENT_UW50) {
			map = uv_canopen_rxpdo_get_mapping(CANOPEN_TXPDO1_ID + LKEYPAD_NODE_ID);
			if (map != NULL &&
					map->mappings[4].main_index != 0) {
				map->mappings[4].main_index = 0;
				map->mappings[4].sub_index = 0;
			}
		}
	}
	else {
		// make sure request is not mapped to right joystick button7
		canopen_pdo_mapping_parameter_st *map =
				uv_canopen_rxpdo_get_mapping(CANOPEN_TXPDO2_ID + RKEYPAD_NODE_ID);
		if (map != NULL &&
				map->mappings[6].main_index != 0) {
			map->mappings[6].main_index = 0;
			map->mappings[6].sub_index = 0;
		}
		// map request to left joystick thumb
		map = uv_canopen_rxpdo_get_mapping(CANOPEN_TXPDO1_ID + LKEYPAD_NODE_ID);
		if (map != NULL &&
				map->mappings[4].main_index != HCU_BOOM_TELESCOPE_REQ_INDEX) {
			map->mappings[4].main_index = HCU_BOOM_TELESCOPE_REQ_INDEX;
			map->mappings[4].sub_index = HCU_BOOM_TELESCOPE_REQ_SUBINDEX;
		}
	}
	uv_enable_int();


	if (dev.assembly.boomtel_installed) {

		input_step(&this->input, step_ms);

		int16_t req = input_get_request(&this->input, &this->conf->out_conf);

		uv_dual_solenoid_output_set(&this->out, req);
	}

}

