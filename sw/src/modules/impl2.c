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


#define TOGGLE_DELAY_MS		1500


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
	this->toggle_state = false;
	this->canreq = 0;
	uv_delay_init(&this->toggle_delay, TOGGLE_DELAY_MS);

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
		// clear hydout request mapping
		map = uv_canopen_rxpdo_get_mapping(CANOPEN_TXPDO2_ID + RKEYPAD_NODE_ID);
		if (map != NULL) {
			map->mappings[1].main_index = 0;
			map->mappings[1].sub_index = 0;
		}
	}
	else if (dev.implement == HCU_IMPLEMENT_HYDOUTPUT ||
			dev.implement == HCU_IMPLEMENT_UW100) {
		// make sure that UW100 is mapped to right joystick z,
		// since it might be used with hydout
		canopen_pdo_mapping_parameter_st *map =
				uv_canopen_rxpdo_get_mapping(CANOPEN_TXPDO1_ID + RKEYPAD_NODE_ID);
		if (map != NULL &&
				map->mappings[4].main_index != HCU_IMPL1_REQ_INDEX) {
			map->mappings[4].main_index = HCU_IMPL1_REQ_INDEX;
			map->mappings[4].sub_index = HCU_IMPL1_REQ_SUBINDEX;
		}
		// remap hydout request to feed button
		map = uv_canopen_rxpdo_get_mapping(CANOPEN_TXPDO2_ID + RKEYPAD_NODE_ID);
		if (map != NULL &&
				map->mappings[1].main_index != HCU_IMPL2_REQ_INDEX) {
			map->mappings[1].length = CANOPEN_SIZEOF(HCU_IMPL2_REQ_TYPE);
			map->mappings[1].main_index = HCU_IMPL2_REQ_INDEX;
			map->mappings[1].sub_index = HCU_IMPL2_REQ_SUBINDEX;
		}
	}
	else {
		// make sure request is not mapped to right joystick z. It will stay mapped in RXPDO.
		canopen_pdo_mapping_parameter_st *map =
				uv_canopen_rxpdo_get_mapping(CANOPEN_TXPDO1_ID + RKEYPAD_NODE_ID);
		if (map != NULL &&
				map->mappings[4].main_index != 0) {
			map->mappings[4].main_index = 0;
			map->mappings[4].sub_index = 0;
		}
		// clear hydout request mapping
		map = uv_canopen_rxpdo_get_mapping(CANOPEN_TXPDO2_ID + RKEYPAD_NODE_ID);
		if (map != NULL) {
			map->mappings[1].main_index = 0;
			map->mappings[1].sub_index = 0;
		}
	}
	uv_enable_int();

	int32_t req = input_get_request(&this->input, &this->conf->out_conf);

	if (dev.implement == HCU_IMPLEMENT_HYDOUTPUT) {
		if (req) {
			if ((this->toggle_state != 0 &&
					!uv_delay_has_ended(&this->toggle_delay)) ||
				uv_delay(&this->toggle_delay, step_ms)) {
				if (this->toggle_state) {
					this->toggle_state = 0;
				}
				else {
					this->toggle_state = req;
				}
			}
		}
		else {
			uv_delay_init(&this->toggle_delay, TOGGLE_DELAY_MS);
		}
		if (dev.fsb.ignkey_state != FSB_IGNKEY_STATE_ON ||
				dev.fsb.emcy) {
			this->toggle_state = 0;
		}
		req = this->toggle_state;
	}

	// if manual request is zero, take the request from the CAN-bus
	if (req == 0) {
		req = (int32_t) this->canreq * 1000 / INT8_MAX;
	}

	uv_dual_solenoid_output_set(&this->out1, req);
	uv_dual_solenoid_output_set(&this->out2, req);



}



void impl2_disable(impl2_st *this) {
	if (dev.implement != HCU_IMPLEMENT_HYDOUTPUT) {
		uv_dual_solenoid_output_disable(&this->out1);
		uv_dual_solenoid_output_disable(&this->out2);
		this->input.request = 0;
	}
}

