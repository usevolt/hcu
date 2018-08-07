/*
 * uw_messages.c
 *
 *  Created on: Feb 19, 2015
 *      Author: usenius
 */


#include "main.h"
#include "messages.h"
#include "can_esb.h"
#include "can_fsb.h"
#include "can_csb.h"
#include "can_hcu.h"
#include "can_keypad.h"
#include "pin_mappings.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <uv_timer.h>
#include <uv_utilities.h>

extern dev_st dev;
#define this (&dev)




canopen_object_st obj_dict[] = {
		{
				.main_index = HCU_TOTAL_CURRENT_INDEX,
				.sub_index = HCU_TOTAL_CURRENT_SUBINDEX,
				.type = HCU_TOTAL_CURRENT_TYPE,
				.permissions = HCU_TOTAL_CURRENT_PERMISSIONS,
				.data_ptr = &this->total_current
		},
		{
				.main_index = HCU_IMPLEMENT_INDEX,
				.sub_index = HCU_IMPLEMENT_SUBINDEX,
				.type = HCU_IMPLEMENT_TYPE,
				.permissions = HCU_IMPLEMENT_PERMISSIONS,
				.data_ptr = &this->implement
		},
		{
				.main_index = HCU_BOOM_ROTATE_REQ_INDEX,
				.sub_index = HCU_BOOM_ROTATE_REQ_SUBINDEX,
				.type = HCU_BOOM_ROTATE_REQ_TYPE,
				.permissions = HCU_BOOM_ROTATE_REQ_PERMISSIONS,
				.data_ptr = &this->boom_rotate.input.request
		},
		{
				.main_index = HCU_BOOM_ROTATE_PARAM_INDEX,
				.array_max_size = HCU_BOOM_ROTATE_PARAM_ARRAY_MAX_SIZE,
				.type = HCU_BOOM_ROTATE_PARAM_TYPE,
				.permissions = HCU_BOOM_ROTATE_PARAM_PERMISSIONS,
				.data_ptr = &this->boom_rotate_conf
		},
		{
				.main_index = HCU_BOOM_ROTATE_CURRENT_INDEX,
				.sub_index = HCU_BOOM_ROTATE_CURRENT_SUBINDEX,
				.type = HCU_BOOM_ROTATE_CURRENT_TYPE,
				.permissions = HCU_BOOM_ROTATE_CURRENT_PERMISSIONS,
				.data_ptr = &this->boom_rotate.out.current_ma
		},
		{
				.main_index = HCU_BOOM_LIFT_REQ_INDEX,
				.sub_index = HCU_BOOM_LIFT_REQ_SUBINDEX,
				.type = HCU_BOOM_LIFT_REQ_TYPE,
				.permissions = HCU_BOOM_LIFT_REQ_PERMISSIONS,
				.data_ptr = &this->boom_lift.input.request
		},
		{
				.main_index = HCU_BOOM_LIFT_PARAM_INDEX,
				.array_max_size = HCU_BOOM_LIFT_PARAM_ARRAY_MAX_SIZE,
				.type = HCU_BOOM_LIFT_PARAM_TYPE,
				.permissions = HCU_BOOM_LIFT_PARAM_PERMISSIONS,
				.data_ptr = &this->boom_lift_conf
		},
		{
				.main_index = HCU_BOOM_LIFT_CURRENT_INDEX,
				.sub_index = HCU_BOOM_LIFT_CURRENT_SUBINDEX,
				.type = HCU_BOOM_LIFT_CURRENT_TYPE,
				.permissions = HCU_BOOM_LIFT_CURRENT_PERMISSIONS,
				.data_ptr = &this->boom_lift.out.current_ma
		},
		{
				.main_index = HCU_BOOM_FOLD_REQ_INDEX,
				.sub_index = HCU_BOOM_FOLD_REQ_SUBINDEX,
				.type = HCU_BOOM_FOLD_REQ_TYPE,
				.permissions = HCU_BOOM_FOLD_REQ_PERMISSIONS,
				.data_ptr = &this->boom_fold.input.request
		},
		{
				.main_index = HCU_BOOM_FOLD_PARAM_INDEX,
				.array_max_size = HCU_BOOM_FOLD_PARAM_ARRAY_MAX_SIZE,
				.type = HCU_BOOM_FOLD_PARAM_TYPE,
				.permissions = HCU_BOOM_FOLD_PARAM_PERMISSIONS,
				.data_ptr = &this->boom_fold_conf
		},
		{
				.main_index = HCU_BOOM_FOLD_CURRENT_INDEX,
				.sub_index = HCU_BOOM_FOLD_CURRENT_SUBINDEX,
				.type = HCU_BOOM_FOLD_CURRENT_TYPE,
				.permissions = HCU_BOOM_FOLD_CURRENT_PERMISSIONS,
				.data_ptr = &this->boom_fold.out.current_ma
		},
		{
				.main_index = HCU_BOOM_TELESCOPE_REQ_INDEX,
				.sub_index = HCU_BOOM_TELESCOPE_REQ_SUBINDEX,
				.type = HCU_BOOM_TELESCOPE_REQ_TYPE,
				.permissions = HCU_BOOM_TELESCOPE_REQ_PERMISSIONS,
				.data_ptr = &this->boom_telescope.input.request
		},
		{
				.main_index = HCU_BOOM_TELESCOPE_PARAM_INDEX,
				.array_max_size = HCU_BOOM_TELESCOPE_PARAM_ARRAY_MAX_SIZE,
				.type = HCU_BOOM_TELESCOPE_PARAM_TYPE,
				.permissions = HCU_BOOM_TELESCOPE_PARAM_PERMISSIONS,
				.data_ptr = &this->boom_telescope_conf
		},
		{
				.main_index = HCU_BOOM_TELESCOPE_CURRENT_INDEX,
				.sub_index = HCU_BOOM_TELESCOPE_CURRENT_SUBINDEX,
				.type = HCU_BOOM_TELESCOPE_CURRENT_TYPE,
				.permissions = HCU_BOOM_TELESCOPE_CURRENT_PERMISSIONS,
				.data_ptr = &this->boom_telescope.out.current_ma
		},
		{
				.main_index = HCU_LEFT_FOOT_REQ_INDEX,
				.sub_index = HCU_LEFT_FOOT_REQ_SUBINDEX,
				.type = HCU_LEFT_FOOT_REQ_TYPE,
				.permissions = HCU_LEFT_FOOT_REQ_PERMISSIONS,
				.data_ptr = &this->left_foot.input.request
		},
		{
				.main_index = HCU_LEFT_FOOT_PARAM_INDEX,
				.array_max_size = HCU_LEFT_FOOT_PARAM_ARRAY_MAX_SIZE,
				.type = HCU_LEFT_FOOT_PARAM_TYPE,
				.permissions = HCU_LEFT_FOOT_PARAM_PERMISSIONS,
				.data_ptr = &this->left_foot_conf
		},
		{
				.main_index = HCU_LEFT_FOOT_CURRENT_INDEX,
				.sub_index = HCU_LEFT_FOOT_CURRENT_SUBINDEX,
				.type = HCU_LEFT_FOOT_CURRENT_TYPE,
				.permissions = HCU_LEFT_FOOT_CURRENT_PERMISSIONS,
				.data_ptr = &this->left_foot.out.current_ma
		},
		{
				.main_index = HCU_RIGHT_FOOT_REQ_INDEX,
				.sub_index = HCU_RIGHT_FOOT_REQ_SUBINDEX,
				.type = HCU_RIGHT_FOOT_REQ_TYPE,
				.permissions = HCU_RIGHT_FOOT_REQ_PERMISSIONS,
				.data_ptr = &this->right_foot.input.request
		},
		{
				.main_index = HCU_RIGHT_FOOT_PARAM_INDEX,
				.array_max_size = HCU_RIGHT_FOOT_PARAM_ARRAY_MAX_SIZE,
				.type = HCU_RIGHT_FOOT_PARAM_TYPE,
				.permissions = HCU_RIGHT_FOOT_PARAM_PERMISSIONS,
				.data_ptr = &this->right_foot_conf
		},
		{
				.main_index = HCU_RIGHT_FOOT_CURRENT_INDEX,
				.sub_index = HCU_RIGHT_FOOT_CURRENT_SUBINDEX,
				.type = HCU_RIGHT_FOOT_CURRENT_TYPE,
				.permissions = HCU_RIGHT_FOOT_CURRENT_PERMISSIONS,
				.data_ptr = &this->right_foot.out.current_ma
		},
		{
				.main_index = HCU_ROTATOR_REQ_INDEX,
				.sub_index = HCU_ROTATOR_REQ_SUBINDEX,
				.type = HCU_ROTATOR_REQ_TYPE,
				.permissions = HCU_ROTATOR_REQ_PERMISSIONS,
				.data_ptr = &this->rotator.input.request
		},
		{
				.main_index = HCU_ROTATOR_PARAM_INDEX,
				.array_max_size = HCU_ROTATOR_PARAM_ARRAY_MAX_SIZE,
				.type = HCU_ROTATOR_PARAM_TYPE,
				.permissions = HCU_ROTATOR_PARAM_PERMISSIONS,
				.data_ptr = &this->rotator_conf
		},
		{
				.main_index = HCU_ROTATOR_CURRENT_INDEX,
				.sub_index = HCU_ROTATOR_CURRENT_SUBINDEX,
				.type = HCU_ROTATOR_CURRENT_TYPE,
				.permissions = HCU_ROTATOR_CURRENT_PERMISSIONS,
				.data_ptr = &this->rotator.out.current_ma
		},
		{
				.main_index = HCU_IMPL1_REQ_INDEX,
				.sub_index = HCU_IMPL1_REQ_SUBINDEX,
				.type = HCU_IMPL1_REQ_TYPE,
				.permissions = HCU_IMPL1_REQ_PERMISSIONS,
				.data_ptr = &this->impl1.input.request
		},
		{
				.main_index = HCU_IMPL1_PARAM_INDEX,
				.array_max_size = HCU_IMPL1_PARAM_ARRAY_MAX_SIZE,
				.type = HCU_IMPL1_PARAM_TYPE,
				.permissions = HCU_IMPL1_PARAM_PERMISSIONS,
				.data_ptr = &this->impl1_conf
		},
		{
				.main_index = HCU_IMPL1_CURRENT_INDEX,
				.sub_index = HCU_IMPL1_CURRENT_SUBINDEX,
				.type = HCU_IMPL1_CURRENT_TYPE,
				.permissions = HCU_IMPL1_CURRENT_PERMISSIONS,
				.data_ptr = &this->impl1.out.current_ma
		},
		{
				.main_index = HCU_IMPL2_REQ_INDEX,
				.sub_index = HCU_IMPL2_REQ_SUBINDEX,
				.type = HCU_IMPL2_REQ_TYPE,
				.permissions = HCU_IMPL2_REQ_PERMISSIONS,
				.data_ptr = &this->impl2.input.request
		},
		{
				.main_index = HCU_IMPL2_PARAM_INDEX,
				.array_max_size = HCU_IMPL2_PARAM_ARRAY_MAX_SIZE,
				.type = HCU_IMPL2_PARAM_TYPE,
				.permissions = HCU_IMPL2_PARAM_PERMISSIONS,
				.data_ptr = &this->impl2_conf
		},
		{
				.main_index = HCU_IMPL2_CURRENT_INDEX,
				.sub_index = HCU_IMPL2_CURRENT_SUBINDEX,
				.type = HCU_IMPL2_CURRENT_TYPE,
				.permissions = HCU_IMPL2_CURRENT_PERMISSIONS,
				.data_ptr = &this->impl2.out.current_ma
		},

		{
				.main_index = HCU_PRESSURE_INDEX,
				.sub_index = HCU_PRESSURE_SUBINDEX,
				.type = HCU_PRESSURE_TYPE,
				.permissions = HCU_PRESSURE_PERMISSIONS,
				.data_ptr = &this->pressure.value
		},


		{
				.main_index = HCU_FSB_INDEX_OFFSET + FSB_IGNKEY_INDEX,
				.sub_index = FSB_IGNKEY_SUBINDEX,
				.type = FSB_IGNKEY_TYPE,
				.permissions = FSB_IGNKEY_PERMISSIONS,
				.data_ptr = &this->fsb.ignkey_state
		},
		{
				.main_index = HCU_FSB_INDEX_OFFSET + FSB_EMCY_INDEX,
				.sub_index = FSB_EMCY_SUBINDEX,
				.type = FSB_EMCY_TYPE,
				.permissions = FSB_EMCY_PERMISSIONS,
				.data_ptr = &this->fsb.emcy
		},
		{
				.main_index = HCU_FSB_INDEX_OFFSET + FSB_DOORSW1_INDEX,
				.sub_index = FSB_DOORSW1_SUBINDEX,
				.type = FSB_DOORSW1_TYPE,
				.permissions = FSB_DOORSW1_PERMISSIONS,
				.data_ptr = &this->fsb.door_sw1
		},
		{
				.main_index = HCU_FSB_INDEX_OFFSET + FSB_DOORSW2_INDEX,
				.sub_index = FSB_DOORSW2_SUBINDEX,
				.type = FSB_DOORSW2_TYPE,
				.permissions = FSB_DOORSW2_PERMISSIONS,
				.data_ptr = &this->fsb.door_sw2
		},
		{
				.main_index = HCU_FSB_INDEX_OFFSET + FSB_SEATSW_INDEX,
				.sub_index = FSB_SEATSW_SUBINDEX,
				.type = FSB_SEATSW_TYPE,
				.permissions = FSB_SEATSW_PERMISSIONS,
				.data_ptr = &this->fsb.seat_sw
		},
};

int obj_dict_len() {
	return sizeof(obj_dict) / sizeof(canopen_object_st);
}

void stat_callb(void* me, unsigned int cmd, unsigned int args, argument_st *argv);
void set_callb(void* me, unsigned int cmd, unsigned int args, argument_st *argv);


const uv_command_st terminal_commands[] = {
		{
				.id = CMD_STAT,
				.str = "stat",
				.instructions = "Displays the system status information.\n"
						"Usage: stat",
				.callback = &stat_callb
		},
		{
				.id = CMD_SET,
				.str = "set",
				.instructions = "Sets the configurations for output modules.\n"
						"Usage: set <\"bl\"/\"bf\"/\"br\"/\"bt\"/\"lf\"/\"rf\"> "
						"<\"maxa\"/\"maxb\"/\"mina\"/\"minb\"/\"acc\"/\"dec\"/\"invert\">"
						"<value>",
				.callback = &set_callb
		}
};




unsigned int commands_size(void) {
	return sizeof(terminal_commands) / sizeof(uv_command_st);
}




static void stat_output(uv_dual_solenoid_output_st *output, const char *name) {
	printf("%s solenoid states: %u %u, current: %i mA\n",
			name, uv_dual_solenoid_output_get_state(output, DUAL_OUTPUT_SOLENOID_A),
			uv_dual_solenoid_output_get_state(output, DUAL_OUTPUT_SOLENOID_B),
			uv_dual_solenoid_output_get_current(output));
}


void stat_callb(void* me, unsigned int cmd, unsigned int args, argument_st *argv) {
	printf("SYSTEM STATUS:\n");
	printf("Total current: %u mA\n", (unsigned int) this->total_current);
	stat_output(&this->boom_rotate.out, "Boom Rotate");
	stat_output(&this->boom_lift.out, "Boom Lift");
	stat_output(&this->boom_fold.out, "Boom Fold");
	stat_output(&this->boom_telescope.out, "Boom Telescope");
	stat_output(&this->left_foot.out, "Left Foot");
	stat_output(&this->right_foot.out, "Right Foot");
	stat_output(&this->rotator.out, "Rotator");

	printf("Keypads found: left: %u right: %u\n",
			!uv_canopen_heartbeat_producer_is_expired(LKEYPAD_NODE_ID),
			!uv_canopen_heartbeat_producer_is_expired(RKEYPAD_NODE_ID));

	printf("emcy: %u, ignkey state: %u\n", this->fsb.emcy, this->fsb.ignkey_state);
}

void set_callb(void* me, unsigned int cmd, unsigned int args, argument_st *argv) {
	if ((args < 1) || (argv[0].type != ARG_STRING)) {
		printf("Give module name as an argument.\n");
	}
	else {
		uv_dual_solenoid_output_conf_st *conf = NULL;
		const char *str = argv[0].str;
		if (strcmp(str, "bl") == 0) {
			conf = &this->boom_lift_conf.out_conf;
		}
		else if (strcmp(str, "bf") == 0) {
			conf = &this->boom_fold_conf.out_conf;
		}
		else if (strcmp(str, "br") == 0) {
			conf = &this->boom_rotate_conf.out_conf;
		}
		else if (strcmp(str, "bt") == 0) {
			conf = &this->boom_telescope_conf.out_conf;
		}
		else if (strcmp(str, "lf") == 0) {
			conf = &this->left_foot_conf.out_conf;
		}
		else if (strcmp(str, "rf") == 0) {
			conf = &this->right_foot_conf.out_conf;
		}
		else if (strcmp(str, "rot") == 0) {
			conf = &this->rotator_conf.out_conf;
		}

		else {
			printf("Unknown module '%s'\n", str);
		}
		if (conf) {
			if (args > 2) {
				if ((argv[1].type == ARG_STRING) &&
					(argv[2].type == ARG_INTEGER)) {
					const char *s = argv[1].str;
					int16_t value = argv[2].number;
					if (strcmp(s, "maxa") == 0) {
						conf->solenoid_conf[DUAL_OUTPUT_SOLENOID_A].max_ma = value;
					}
					else if (strcmp(s, "mina") == 0) {
						conf->solenoid_conf[DUAL_OUTPUT_SOLENOID_A].min_ma = value;
					}
					else if (strcmp(s, "maxb") == 0) {
						conf->solenoid_conf[DUAL_OUTPUT_SOLENOID_B].max_ma = value;
					}
					else if (strcmp(s, "minb") == 0) {
						conf->solenoid_conf[DUAL_OUTPUT_SOLENOID_B].min_ma = value;
					}
					else if (strcmp(s, "acc") == 0) {
						conf->acc = value;
					}
					else if (strcmp(s, "dec") == 0) {
						conf->dec = value;
					}
					else if (strcmp(s, "invert") == 0) {
						conf->invert = value;
					}
					else {
						printf("Unknown parameter '%s'\n", s);
					}
				}
				else {
					printf("Wrong type of arguments. Arguments has to be:\n"
							"   String, string and integer.\n");
				}
			}
			printf("%s parameters:\n"
					"   Max Speed A: %u\n"
					"   Min Speed A: %u\n"
					"   Max Speed B: %u\n"
					"   Min Speed B: %u\n"
					"   Acceleration: %u\n"
					"   Deceleration: %u\n"
					"   Invert: %u\n",
					str,
					conf->solenoid_conf[DUAL_OUTPUT_SOLENOID_A].max_ma,
					conf->solenoid_conf[DUAL_OUTPUT_SOLENOID_A].min_ma,
					conf->solenoid_conf[DUAL_OUTPUT_SOLENOID_B].max_ma,
					conf->solenoid_conf[DUAL_OUTPUT_SOLENOID_B].min_ma,
					conf->acc,
					conf->dec,
					conf->invert);
		}
	}
}



