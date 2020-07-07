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
#include <uv_eeprom.h>

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
				.main_index = HCU_LEFT_FOOT_STATE_INDEX,
				.sub_index = HCU_LEFT_FOOT_STATE_SUBINDEX,
				.type = HCU_LEFT_FOOT_STATE_TYPE,
				.permissions = HCU_LEFT_FOOT_STATE_PERMISSIONS,
				.data_ptr = &this->left_foot.state
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
				.main_index = HCU_RIGHT_FOOT_STATE_INDEX,
				.sub_index = HCU_RIGHT_FOOT_STATE_SUBINDEX,
				.type = HCU_RIGHT_FOOT_STATE_TYPE,
				.permissions = HCU_RIGHT_FOOT_STATE_PERMISSIONS,
				.data_ptr = &this->right_foot.state
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
				.main_index = HCU_IMPL2_CURRENT1_INDEX,
				.sub_index = HCU_IMPL2_CURRENT1_SUBINDEX,
				.type = HCU_IMPL2_CURRENT1_TYPE,
				.permissions = HCU_IMPL2_CURRENT1_PERMISSIONS,
				.data_ptr = &this->impl2.out1.current_ma
		},
		{
				.main_index = HCU_IMPL2_CURRENT2_INDEX,
				.sub_index = HCU_IMPL2_CURRENT2_SUBINDEX,
				.type = HCU_IMPL2_CURRENT2_TYPE,
				.permissions = HCU_IMPL2_CURRENT2_PERMISSIONS,
				.data_ptr = &this->impl2.out2.current_ma
		},
		{
				.main_index = HCU_IMPL2_CANREQ_INDEX,
				.sub_index = HCU_IMPL2_CANREQ_SUBINDEX,
				.type = HCU_IMPL2_CANREQ_TYPE,
				.permissions = HCU_IMPL2_CANREQ_PERMISSIONS,
				.data_ptr = &this->impl2.canreq
		},
		{
				.main_index = HCU_D4WD_STATE_REQ_INDEX,
				.sub_index = HCU_D4WD_STATE_REQ_SUBINDEX,
				.type = HCU_D4WD_STATE_REQ_TYPE,
				.permissions = HCU_D4WD_STATE_REQ_PERMISSIONS,
				.data_ptr = &this->d4wd.req
		},
		{
				.main_index = HCU_D4WD_STATE_INDEX,
				.sub_index = HCU_D4WD_STATE_SUBINDEX,
				.type = HCU_D4WD_STATE_TYPE,
				.permissions = HCU_D4WD_STATE_PERMISSIONS,
				.data_ptr = &this->d4wd.out.state
		},
		{
				.main_index = HCU_D4WD_CURRENT_INDEX,
				.sub_index = HCU_D4WD_CURRENT_SUBINDEX,
				.type = HCU_D4WD_CURRENT_TYPE,
				.permissions = HCU_D4WD_CURRENT_PERMISSIONS,
				.data_ptr = &this->d4wd.out.current
		},

		{
				.main_index = HCU_PRESSURE_INDEX,
				.sub_index = HCU_PRESSURE_SUBINDEX,
				.type = HCU_PRESSURE_TYPE,
				.permissions = HCU_PRESSURE_PERMISSIONS,
				.data_ptr = &this->pressure.value
		},

		{
				.main_index = HCU_ASSEMBLY_INDEX,
				.array_max_size = HCU_ASSEMBLY_ARRAY_SIZE,
				.type = HCU_ASSEMBLY_TYPE,
				.permissions = HCU_ASSEMBLY_PERMISSIONS,
				.data_ptr = &this->assembly
		},
		{
				.main_index = HCU_ASSEMBLY_WRITE_INDEX,
				.sub_index = HCU_ASSEMBLY_WRITE_SUBINDEX,
				.type = HCU_ASSEMBLY_WRITE_TYPE,
				.permissions = HCU_ASSEMBLY_WRITE_PERMISSIONS,
				.data_ptr = &dev.assembly_write
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
		{
				.main_index = HCU_CCU_INDEX_OFFSET + CCU_DRIVE_REQ_INDEX,
				.sub_index = CCU_DRIVE_REQ_SUBINDEX,
				.type = CCU_DRIVE_REQ_TYPE,
				.permissions = CCU_DRIVE_REQ_PERMISSIONS,
				.data_ptr = &this->ccu.drive_req
		}
};

int obj_dict_len() {
	return sizeof(obj_dict) / sizeof(canopen_object_st);
}

void stat_callb(void* me, unsigned int cmd, unsigned int args, argument_st *argv);
void set_callb(void* me, unsigned int cmd, unsigned int args, argument_st *argv);
void ass_callb(void* me, unsigned int cmd, unsigned int args, argument_st *argv);


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
						"Usage: set <\"bl\"/\"bf\"/\"br\"/\"bt\"/\"lf\"/\"rf\"/\"impl1\"/\"impl2\"/\"rot\"> "
						"<\"maxa\"/\"maxb\"/\"mina\"/\"minb\"/\"acc\"/\"dec\"/\"invert\">"
						"<value>",
				.callback = &set_callb
		},
		{
				.id = CMD_ASS,
				.str = "ass",
				.instructions = "Sets the assembly bits.\n"
						"Usage: ass <\"boomtelescope\"> <value>",
				.callback = &ass_callb
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
	stat_output(&this->impl1.out, "Implement 1");
	printf("Impl2 can req: %i\n", this->impl2.canreq);
	stat_output(&this->impl2.out1, "Implement 2:1");
	stat_output(&this->impl2.out1, "Implement 2:2");
	printf("D4WD state: %u, current: %u mA\n",
			uv_output_get_state(&this->d4wd.out),
			d4wd_get_current(&this->d4wd));
	printf("Left foot state: %u, right foot state: %u\n",
			this->left_foot.state,
			this->right_foot.state);
	stat_output(&this->rotator.out, "Rotator");
	printf("Pressure: %i bar, adc: 0x%x\n",
			uv_sensor_get_value(&this->pressure),
			uv_adc_read(PRESS_SENSE));
	char *str;
	switch (this->implement) {
	case HCU_IMPLEMENT_UW100:
		str = "UW100";
		break;
	case HCU_IMPLEMENT_UW50:
		str = "UW50";
		break;
	case HCU_IMPLEMENT_UW180S:
		str = "UW180S";
		break;
	case HCU_IMPLEMENT_HYDOUTPUT:
		str = "Hydroutput";
		break;
	default:
		str = "none";
		break;
	}
	printf("Implement: %s\n", str);

	printf("Keypads found: left: %u right: %u\n",
			!uv_canopen_heartbeat_producer_is_expired(LKEYPAD_NODE_ID),
			!uv_canopen_heartbeat_producer_is_expired(RKEYPAD_NODE_ID));
	printf("FSB found: %u\n",
			!uv_canopen_heartbeat_producer_is_expired(FSB_NODE_ID));

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
		else if (strcmp(str, "impl1") == 0) {
			conf = &this->impl1_conf.out_conf;
		}
		else if (strcmp(str, "impl2") == 0) {
			conf = &this->impl2_conf.out_conf;
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
						conf->invert = (bool) value;
					}
					else if (strcmp(s, "assinv") == 0) {
						conf->assembly_invert = (bool) value;
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
					"   Invert: %u\n"
					"   Assembly invert: %u\n",
					str,
					conf->solenoid_conf[DUAL_OUTPUT_SOLENOID_A].max_ma,
					conf->solenoid_conf[DUAL_OUTPUT_SOLENOID_A].min_ma,
					conf->solenoid_conf[DUAL_OUTPUT_SOLENOID_B].max_ma,
					conf->solenoid_conf[DUAL_OUTPUT_SOLENOID_B].min_ma,
					conf->acc,
					conf->dec,
					conf->invert,
					conf->assembly_invert);
		}
	}
}

void ass_callb(void* me, unsigned int cmd, unsigned int args, argument_st *argv) {
	if (args >= 2 &&
			argv[0].type == ARG_STRING &&
			argv[1].type == ARG_INTEGER) {
		char *str = argv[0].str;
		int value = argv[1].number;
		bool match = true;
		if (strcmp(str, "boomtelescope") == 0) {
			this->assembly.boomtel_installed = !!value;
		}
		else if (strcmp(str, "backsteer") == 0) {
			this->assembly.backsteer_intalled = !!value;
		}
		else {
			match = false;
		}
		if (match) {
			uv_eeprom_write(&this->assembly, sizeof(this->assembly), ASSEMBLY_EEPROM_ADDR);
		}
	}
	else if (args) {
		printf("First argument should be a string defining the parameter to set\n"
				"and second parameter the value which will be set.\n");
	}
	else {

	}

	printf("Assembly variable:\n"
			"   Boom Telescope: %u\n"
			"   Back steer: %u\n",
			this->assembly.boomtel_installed,
			this->assembly.backsteer_intalled);

}

