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



#define BOOM_ROTATE_PWMA		PWM0_0
#define BOOM_ROTATE_PWMB		PWM0_5
#define BOOM_ROTATE_SENSE		ADC1_3

#define BOOM_LIFT_PWMA			PWM0_1
#define BOOM_LIFT_PWMB			PWM0_2
#define BOOM_LIFT_SENSE			ADC1_1

#define BOOM_FOLD_PWMA			PWM1_0
#define BOOM_FOLD_PWMB			PWM2_3
#define BOOM_FOLD_SENSE			ADC0_1

#define IMPL1_PWMA				PWM1_3
#define IMPL1_PWMB				PWM1_4
#define IMPL1_SENSE				ADC0_4

#define BOOM_TELESCOPE_PWMA		PWM0_3
#define BOOM_TELESCOPE_PWMB		PWM0_4
#define BOOM_TELESCOPE_SENSE	ADC0_8

#define LEFT_FOOT_PWMA			PWM1_1
#define LEFT_FOOT_PWMB			PWM2_4
#define LEFT_FOOT_SENSE			ADC0_9

#define RIGHT_FOOT_PWMA			PWM3_3
#define RIGHT_FOOT_PWMB			PWM1_2
#define RIGHT_FOOT_SENSE		ADC0_11

#define ROTATOR_PWMA			PWM0_6
#define ROTATOR_PWMB			PWM3_4
#define ROTATOR_SENSE			ADC1_8

#define IMPL2_1_PWMA			PWM2_0
#define IMPL2_1_PWMB			PWM2_1
#define IMPL2_1_SENSE			ADC1_9

#define IMPL2_2_PWMA			PWM2_2
#define IMPL2_2_PWMB			PWM1_5
#define IMPL2_2_SENSE			ADC1_11




#define D4WD_SENSE				ADC1_6
#define D4WD_OUT				P1_3


#define PRESS_SENSE				ADC1_4

#endif /* UW_MB_SRC_PIN_MAPPINGS_H_ */
