/*
===============================================================================
 Name        : main.c
 Author      : Olli Usenius
 Version     :
 Copyright   : $(copyright)
 Description :
===============================================================================
*/


#include "main.h"
#include "messages.h"
#include "pin_mappings.h"
#include "can_fsb.h"

#include <uv_utilities.h>
#include <uv_rtos.h>
#include <string.h>

dev_st dev = {};
static bool initialized = false;
#define this ((dev_st*) &dev)




void init(dev_st* me) {
	// load non-volatile data
	if (uv_memory_load()) {

		this->dither_ampl = DITHER_AMPL_DEF;
		this->dither_freq = DITHER_FREQ_DEF;

		boom_rotate_conf_reset(&this->boom_rotate_conf);

		// initialize non-volatile memory to default settings
		uv_memory_save();
	}
	// initialize outputs

	this->total_current = 0;

	boom_rotate_init(&this->boom_rotate, &this->boom_rotate_conf);
	boom_lift_init(&this->boom_lift, &this->boom_lift_conf);
	boom_fold_init(&this->boom_fold, &this->boom_fold_conf);

	uv_terminal_init(terminal_commands, commands_size());

	uv_canopen_set_state(CANOPEN_OPERATIONAL);


	initialized = true;
}



void solenoid_step(void* me) {

	// wait until solenoid structures have been initialized
	while (!initialized) {
		uv_rtos_task_delay(1);
	}

	while (true) {
		uint32_t step_ms = 2;

		boom_rotate_solenoid_step(&this->boom_rotate, step_ms);
		boom_lift_solenoid_step(&this->boom_lift, step_ms);
		boom_fold_solenoid_step(&this->boom_fold, step_ms);

		uv_rtos_task_delay(step_ms);
	}
}


void step(void* me) {

	init(this);

	while (true) {
		unsigned int step_ms = 20;
		// update watchdog timer value to prevent a hard reset
		// uw_wdt_update();

		// terminal step function
		uv_terminal_step();


		this->total_current = abs(boom_rotate_get_current(&this->boom_rotate)) +
				abs(boom_lift_get_current(&this->boom_lift)) +
				abs(boom_fold_get_current(&this->boom_fold));


		boom_rotate_step(&this->boom_rotate, step_ms);
		boom_lift_step(&this->boom_lift, step_ms);
		boom_fold_step(&this->boom_fold, step_ms);


		// if keypad heartbeat messages are not received, input from that keypad is set to zero
		if (uv_canopen_heartbeat_producer_is_expired(LKEYPAD_NODE_ID)) {
		}
		if (uv_canopen_heartbeat_producer_is_expired(RKEYPAD_NODE_ID)) {
		}

		// outputs are disables if FSB is not found, ignition key is not in ON state,
		// or emergency switch is pressed
		if (uv_canopen_heartbeat_producer_is_expired(FSB_NODE_ID) ||
				(this->fsb.ignkey_state != FSB_IGNKEY_STATE_ON) ||
				this->fsb.emcy) {
			// disable all outputs
			boom_rotate_disable(&this->boom_rotate);
			boom_lift_disable(&this->boom_lift);
			boom_fold_disable(&this->boom_fold);
		}
		else {
			// enable outputs
			boom_rotate_enable(&this->boom_rotate);
			boom_lift_disable(&this->boom_lift);
			boom_fold_disable(&this->boom_fold);
		}

		uv_rtos_task_delay(step_ms);
	}
}






int main(void) {

	// init the watchdog timer
//	uw_wdt_init(5);

	uv_init(&dev);


	uv_rtos_task_create(&step, "step", UV_RTOS_MIN_STACK_SIZE * 5,
			&dev, UV_RTOS_IDLE_PRIORITY + 1, NULL);

	uv_rtos_task_create(&solenoid_step, "solenoid", UV_RTOS_MIN_STACK_SIZE * 2,
			&dev, UV_RTOS_IDLE_PRIORITY + 2, NULL);


	uv_rtos_start_scheduler();


    // Enter an infinite loop
	// never should end up here
    while(1) {
    }
    return 0;
}
