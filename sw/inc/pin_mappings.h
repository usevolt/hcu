/*
 * pin_mappings.h
 *
 *  Created on: Jan 27, 2015
 *      Author: usenius
 *
 *  Defines keypad pin mappings for different pcb revisions used
 */

#ifndef UW_MB_SRC_PIN_MAPPINGS_H_
#define UW_MB_SRC_PIN_MAPPINGS_H_

#include <uv_gpio.h>
#include <uv_timer.h>
#include <uv_adc.h>
#include <uv_pwm.h>


// Analog inputs
#define VDD_SENSE_AIN				ADC0_11
#define GLOW_SENSE_AIN				ADC0_10
#define STARTER_SENSE_AIN			ADC0_9
#define AC_SENSE_AIN				ADC0_8
#define ENGINE_START1_SENSE_AIN		ADC0_7
#define ENGINE_START2_SENSE_AIN		ADC0_5
#define PUMP_SENSE_AIN				ADC0_1
#define ALT_IG_SENSE_AIN			ADC0_2
#define MOTOR_TEMP_AIN				ADC1_11
#define OIL_TEMP_AIN				ADC1_10
#define FUEL_LEVEL_AIN				ADC1_8
#define OIL_LEVEL_AIN				ADC1_9
#define OILCOOLER_AIN				ADC1_0

// Digital inputs
#define ALT_L_I						P0_11
#define ALT_P_RPM_I					P0_13
#define MOTOR_WATER_TEMP_I			P1_3
#define MOTOR_OIL_PRESS_I			P1_2

// Digital outputs
#define PUMP_PWM					PWM0_0
#define ALT_IG_O					P0_5
#define AC_O						P0_27
#define ENGINE_START_1_O			P0_26
#define ENGINE_START_2_O			P0_2
#define GLOW_PLUGS_O				P0_29
#define STARTER_O					P0_28
#define OILCOOLER_O					P0_9


// RPM timer
#define RPM_TIMER					TIMER1

#endif /* UW_MB_SRC_PIN_MAPPINGS_H_ */
