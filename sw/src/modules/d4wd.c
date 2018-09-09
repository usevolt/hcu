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





#include "d4wd.h"
#include "main.h"
#include "pin_mappings.h"



void d4wd_init(d4wd_st *this) {
	this->req = OUTPUT_STATE_OFF;

	uv_output_init(&this->out, D4WD_SENSE, D4WD_OUT, VN5E01_CURRENT_AMPL_UA,
			15000, 20000, 50, HCU_EMCY_D4WD_OVERLOAD, HCU_EMCY_D4WD_FAULT);
}


void d4wd_step(d4wd_st *this, uint16_t step_ms) {

	uv_output_set_state(&this->out, this->req);
}

