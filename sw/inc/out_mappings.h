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


#ifndef INC_OUT_MAPPINGS_H_
#define INC_OUT_MAPPINGS_H_


#include "main.h"

/// @file: Defines the solenoid valve mappings for Usewood FM, CM and LM

#define VALVE_BR	dev.pout[0]
#define VALVE_BL	dev.pout[1]
#define VALVE_BF	dev.pout[2]
#define VALVE_IMPL2	dev.pout[3]
#define VALVE_BT	dev.pout[4]
#define VALVE_LF	dev.pout[5]
#define VALVE_RF	dev.pout[6]
#define VALVE_ROT	dev.pout[7]
#define VALVE_IMPL1	dev.pout[8]


#endif /* INC_OUT_MAPPINGS_H_ */
