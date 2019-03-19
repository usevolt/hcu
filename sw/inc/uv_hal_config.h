/*
 * uw_hal_config.h
 *
 *  Created on: Mar 22, 2016
 *      Author: usevolt
 */

#ifndef UV_HAL_CONFIG_H_
#define UV_HAL_CONFIG_H_


#include "can_esb.h"
#include "can_fsb.h"
#include "can_csb.h"
#include "can_hcu.h"
#include "can_keypad.h"
#include "can_ccu.h"

/**** USER CONFIGURATIONS ****/


#define CONFIG_INTERFACE_REVISION					0


#define CONFIG_TARGET_LPC11C14						0
#define CONFIG_TARGET_LPC1785						0
#define CONFIG_TARGET_LPC1549						1


#define CONFIG_HARDFAULT_CALLBACK					hardfault_callback


#define CONFIG_NON_VOLATILE_MEMORY					1
#define CONFIG_MAIN_H								"main.h"
#define CONFIG_APP_ST								struct _dev_st dev
#define CONFIG_NON_VOLATILE_START					dev.data_start
#define CONFIG_NON_VOLATILE_END						dev.data_end



#define CONFIG_RTOS									1
#define CONFIG_RTOS_HEAP_SIZE						6000
#define CONFIG_UV_BOOTLOADER						1


#define CONFIG_WDT									1
#define CONFIG_WDT_CYCLE_S							1

#define CONFIG_PWM									1
#define CONFIG_PWM0									1
#define CONFIG_PWM0_FREQ							1200
#define CONFIG_PWM0_0								1
#define CONFIG_PWM0_0_IO							P0_10
#define CONFIG_PWM0_1								1
#define CONFIG_PWM0_1_IO							P0_8
#define CONFIG_PWM0_2								1
#define CONFIG_PWM0_2_IO							P1_1
#define CONFIG_PWM0_3								1
#define CONFIG_PWM0_4								1
#define CONFIG_PWM0_5								1
#define CONFIG_PWM0_6								1

#define CONFIG_PWM1									1
#define CONFIG_PWM1_FREQ							CONFIG_PWM0_FREQ
#define CONFIG_PWM1_0								1
#define CONFIG_PWM1_0_IO							P0_5
#define CONFIG_PWM1_1								1
#define CONFIG_PWM1_1_IO							P0_28
#define CONFIG_PWM1_2								1
#define CONFIG_PWM1_2_IO							P0_27
#define CONFIG_PWM1_3								1
#define CONFIG_PWM1_4								1
#define CONFIG_PWM1_5								1
#define CONFIG_PWM1_6								0

#define CONFIG_PWM2									1
#define CONFIG_PWM2_FREQ							CONFIG_PWM0_FREQ
#define CONFIG_PWM2_0								1
#define CONFIG_PWM2_0_IO							P1_6
#define CONFIG_PWM2_1								1
#define CONFIG_PWM2_1_IO							P1_7
#define CONFIG_PWM2_2								1
#define CONFIG_PWM2_2_IO							P1_4
#define CONFIG_PWM2_3								1
#define CONFIG_PWM2_4								1

#define CONFIG_PWM3									1
#define CONFIG_PWM3_FREQ							CONFIG_PWM0_FREQ
#define CONFIG_PWM3_0								0
#define CONFIG_PWM3_0_IO							P0_4
#define CONFIG_PWM3_1								0
#define CONFIG_PWM3_1_IO							P0_4
#define CONFIG_PWM3_2								0
#define CONFIG_PWM3_2_IO							P0_4
#define CONFIG_PWM3_3								1
#define CONFIG_PWM3_4								1





#define CONFIG_TERMINAL								1
#define CONFIG_TERMINAL_BUFFER_SIZE					200
#define CONFIG_TERMINAL_ARG_COUNT					4
#define CONFIG_TERMINAL_INSTRUCTIONS				1
#define CONFIG_TERMINAL_UART						0
#define CONFIG_TERMINAL_CAN							1





#define CONFIG_ADC0									1
#define CONFIG_ADC1									1
#define CONFIG_ADC_MODE								ADC_MODE_SYNC
#define CONFIG_ADC_CONVERSION_FREQ					20000

#define CONFIG_ADC_CHANNEL0_0						0
#define CONFIG_ADC_CHANNEL0_1						1
#define CONFIG_ADC_CHANNEL0_2						0
#define CONFIG_ADC_CHANNEL0_3						0
#define CONFIG_ADC_CHANNEL0_4						1
#define CONFIG_ADC_CHANNEL0_5						0
#define CONFIG_ADC_CHANNEL0_6						0
#define CONFIG_ADC_CHANNEL0_7						0
#define CONFIG_ADC_CHANNEL0_8						1
#define CONFIG_ADC_CHANNEL0_9						1
#define CONFIG_ADC_CHANNEL0_10						0
#define CONFIG_ADC_CHANNEL0_11						1
#define CONFIG_ADC_CHANNEL1_0						0
#define CONFIG_ADC_CHANNEL1_1						1
#define CONFIG_ADC_CHANNEL1_2						0
#define CONFIG_ADC_CHANNEL1_3						1
#define CONFIG_ADC_CHANNEL1_4						1
#define CONFIG_ADC_CHANNEL1_5						0
#define CONFIG_ADC_CHANNEL1_6						1
#define CONFIG_ADC_CHANNEL1_7						0
#define CONFIG_ADC_CHANNEL1_8						1
#define CONFIG_ADC_CHANNEL1_9						1
#define CONFIG_ADC_CHANNEL1_10						0
#define CONFIG_ADC_CHANNEL1_11						1




#define CONFIG_EEPROM								1
#define CONFIG_EEPROM_RING_BUFFER					0

#define CONFIG_RTC									0




#define CONFIG_CAN									1
#define CONFIG_CAN0									1
#define CONFIG_CAN1									0

#define CONFIG_CAN0_BAUDRATE						250000
#define CONFIG_CAN0_TX_BUFFER_SIZE					8
#define CONFIG_CAN0_RX_BUFFER_SIZE					32
#define CONFIG_CAN0_TX_PIN							P0_25
#define CONFIG_CAN0_RX_PIN							P1_10

#define CONFIG_CAN_LOG								0
#define CONFIG_CAN_ERROR_LOG						1



#define CONFIG_CANOPEN								1
#define CONFIG_CANOPEN_LOG							0
#define CONFIG_CANOPEN_NMT_SLAVE					1
#define CONFIG_CANOPEN_AUTO_PREOPERATIONAL			1
#define CONFIG_CANOPEN_RXPDO_COUNT					8
#define CONFIG_CANOPEN_TXPDO_COUNT					2
#define CONFIG_CANOPEN_PDO_MAPPING_COUNT			8
#define CONFIG_CANOPEN_SDO_SYNC						1
#define CONFIG_CANOPEN_SDO_SEGMENTED				1
#define CONFIG_CANOPEN_SDO_BLOCK_TRANSFER			0
#define CONFIG_CANOPEN_SDO_TIMEOUT_MS				10
#define CONFIG_CANOPEN_OBJ_DICT_APP_PARAMS			obj_dict
#define CONFIG_CANOPEN_OBJ_DICT_APP_PARAMS_COUNT	obj_dict_len
#define CONFIG_CANOPEN_PRODUCER_HEARTBEAT_TIME_MS	1000
#define CONFIG_CANOPEN_HEARTBEAT_CONSUMER			1
#define CONFIG_CANOPEN_HEARTBEAT_PRODUCER			1
#define CONFIG_CANOPEN_HEARTBEAT_PRODUCER_COUNT		3
#define CONFIG_CANOPEN_HEARTBEAT_PRODUCER_NODEID1	FSB_NODE_ID
#define CONFIG_CANOPEN_HEARTBEAT_PRODUCER_TIME1		2200
#define CONFIG_CANOPEN_HEARTBEAT_PRODUCER_NODEID2	LKEYPAD_NODE_ID
#define CONFIG_CANOPEN_HEARTBEAT_PRODUCER_TIME2		1200
#define CONFIG_CANOPEN_HEARTBEAT_PRODUCER_NODEID3	RKEYPAD_NODE_ID
#define CONFIG_CANOPEN_HEARTBEAT_PRODUCER_TIME3		1200
#define CONFIG_CANOPEN_CHANNEL						CAN0
#define CONFIG_CANOPEN_DEFAULT_NODE_ID				HCU_NODE_ID
#define CONFIG_CANOPEN_EMCY_RX_BUFFER_SIZE			3

#define CONFIG_CANOPEN_RXPDO1_ID					(CANOPEN_RXPDO1_ID + HCU_NODE_ID)
#define CONFIG_CANOPEN_RXPDO1_TRANSMISSION_TYPE		CANOPEN_PDO_TRANSMISSION_ASYNC
#define CONFIG_CANOPEN_RXPDO1_MAPPING1_MAIN_INDEX	HCU_IMPL1_REQ_INDEX
#define CONFIG_CANOPEN_RXPDO1_MAPPING1_SUB_INDEX	HCU_IMPL1_REQ_SUBINDEX
#define CONFIG_CANOPEN_RXPDO1_MAPPING1_LEN			CANOPEN_TYPE_LEN(HCU_IMPL1_REQ_TYPE)
#define CONFIG_CANOPEN_RXPDO1_MAPPING2_MAIN_INDEX	HCU_IMPL2_REQ_INDEX
#define CONFIG_CANOPEN_RXPDO1_MAPPING2_SUB_INDEX	HCU_IMPL2_REQ_SUBINDEX
#define CONFIG_CANOPEN_RXPDO1_MAPPING2_LEN			CANOPEN_TYPE_LEN(HCU_IMPL2_REQ_TYPE)
#define CONFIG_CANOPEN_RXPDO1_MAPPING3_MAIN_INDEX	0
#define CONFIG_CANOPEN_RXPDO1_MAPPING3_SUB_INDEX	0
#define CONFIG_CANOPEN_RXPDO1_MAPPING3_LEN			CANOPEN_TYPE_LEN(0)
#define CONFIG_CANOPEN_RXPDO1_MAPPING4_MAIN_INDEX	0
#define CONFIG_CANOPEN_RXPDO1_MAPPING4_SUB_INDEX	0
#define CONFIG_CANOPEN_RXPDO1_MAPPING4_LEN			CANOPEN_TYPE_LEN(0)
#define CONFIG_CANOPEN_RXPDO1_MAPPING5_MAIN_INDEX	0
#define CONFIG_CANOPEN_RXPDO1_MAPPING5_SUB_INDEX	0
#define CONFIG_CANOPEN_RXPDO1_MAPPING5_LEN			CANOPEN_TYPE_LEN(0)
#define CONFIG_CANOPEN_RXPDO1_MAPPING6_MAIN_INDEX	0
#define CONFIG_CANOPEN_RXPDO1_MAPPING6_SUB_INDEX	0
#define CONFIG_CANOPEN_RXPDO1_MAPPING6_LEN			CANOPEN_TYPE_LEN(0)
#define CONFIG_CANOPEN_RXPDO1_MAPPING7_MAIN_INDEX	0
#define CONFIG_CANOPEN_RXPDO1_MAPPING7_SUB_INDEX	0
#define CONFIG_CANOPEN_RXPDO1_MAPPING7_LEN			CANOPEN_TYPE_LEN(0)
#define CONFIG_CANOPEN_RXPDO1_MAPPING8_MAIN_INDEX	0
#define CONFIG_CANOPEN_RXPDO1_MAPPING8_SUB_INDEX	0
#define CONFIG_CANOPEN_RXPDO1_MAPPING8_LEN			CANOPEN_TYPE_LEN(0)

#define CONFIG_CANOPEN_RXPDO2_ID					(CANOPEN_RXPDO2_ID + HCU_NODE_ID)
#define CONFIG_CANOPEN_RXPDO2_TRANSMISSION_TYPE		CANOPEN_PDO_TRANSMISSION_ASYNC
#define CONFIG_CANOPEN_RXPDO2_MAPPING1_MAIN_INDEX	HCU_D4WD_STATE_REQ_INDEX
#define CONFIG_CANOPEN_RXPDO2_MAPPING1_SUB_INDEX	HCU_D4WD_STATE_REQ_SUBINDEX
#define CONFIG_CANOPEN_RXPDO2_MAPPING1_LEN			CANOPEN_TYPE_LEN(HCU_D4WD_STATE_REQ_TYPE)
#define CONFIG_CANOPEN_RXPDO2_MAPPING2_MAIN_INDEX	0
#define CONFIG_CANOPEN_RXPDO2_MAPPING2_SUB_INDEX	0
#define CONFIG_CANOPEN_RXPDO2_MAPPING2_LEN			CANOPEN_TYPE_LEN(0)
#define CONFIG_CANOPEN_RXPDO2_MAPPING3_MAIN_INDEX	0
#define CONFIG_CANOPEN_RXPDO2_MAPPING3_SUB_INDEX	0
#define CONFIG_CANOPEN_RXPDO2_MAPPING3_LEN			CANOPEN_TYPE_LEN(0)
#define CONFIG_CANOPEN_RXPDO2_MAPPING4_MAIN_INDEX	0
#define CONFIG_CANOPEN_RXPDO2_MAPPING4_SUB_INDEX	0
#define CONFIG_CANOPEN_RXPDO2_MAPPING4_LEN			CANOPEN_TYPE_LEN(0)
#define CONFIG_CANOPEN_RXPDO2_MAPPING5_MAIN_INDEX	0
#define CONFIG_CANOPEN_RXPDO2_MAPPING5_SUB_INDEX	0
#define CONFIG_CANOPEN_RXPDO2_MAPPING5_LEN			CANOPEN_TYPE_LEN(0)
#define CONFIG_CANOPEN_RXPDO2_MAPPING6_MAIN_INDEX	0
#define CONFIG_CANOPEN_RXPDO2_MAPPING6_SUB_INDEX	0
#define CONFIG_CANOPEN_RXPDO2_MAPPING6_LEN			CANOPEN_TYPE_LEN(0)
#define CONFIG_CANOPEN_RXPDO2_MAPPING7_MAIN_INDEX	0
#define CONFIG_CANOPEN_RXPDO2_MAPPING7_SUB_INDEX	0
#define CONFIG_CANOPEN_RXPDO2_MAPPING7_LEN			CANOPEN_TYPE_LEN(0)
#define CONFIG_CANOPEN_RXPDO2_MAPPING8_MAIN_INDEX	0
#define CONFIG_CANOPEN_RXPDO2_MAPPING8_SUB_INDEX	0
#define CONFIG_CANOPEN_RXPDO2_MAPPING8_LEN			CANOPEN_TYPE_LEN(0)

#define CONFIG_CANOPEN_RXPDO3_ID					(CANOPEN_TXPDO1_ID + FSB_NODE_ID)
#define CONFIG_CANOPEN_RXPDO3_TRANSMISSION_TYPE		CANOPEN_PDO_TRANSMISSION_ASYNC
#define CONFIG_CANOPEN_RXPDO3_MAPPING1_MAIN_INDEX	0
#define CONFIG_CANOPEN_RXPDO3_MAPPING1_SUB_INDEX	0
#define CONFIG_CANOPEN_RXPDO3_MAPPING1_LEN			CANOPEN_TYPE_LEN(FSB_TOTAL_CURRENT_TYPE)
#define CONFIG_CANOPEN_RXPDO3_MAPPING2_MAIN_INDEX	HCU_FSB_INDEX_OFFSET + FSB_IGNKEY_INDEX
#define CONFIG_CANOPEN_RXPDO3_MAPPING2_SUB_INDEX	FSB_IGNKEY_SUBINDEX
#define CONFIG_CANOPEN_RXPDO3_MAPPING2_LEN			CANOPEN_TYPE_LEN(FSB_IGNKEY_TYPE)
#define CONFIG_CANOPEN_RXPDO3_MAPPING3_MAIN_INDEX	HCU_FSB_INDEX_OFFSET + FSB_EMCY_INDEX
#define CONFIG_CANOPEN_RXPDO3_MAPPING3_SUB_INDEX	FSB_EMCY_SUBINDEX
#define CONFIG_CANOPEN_RXPDO3_MAPPING3_LEN			CANOPEN_TYPE_LEN(FSB_EMCY_TYPE)
#define CONFIG_CANOPEN_RXPDO3_MAPPING4_MAIN_INDEX	HCU_FSB_INDEX_OFFSET + FSB_DOORSW1_INDEX
#define CONFIG_CANOPEN_RXPDO3_MAPPING4_SUB_INDEX	FSB_DOORSW1_SUBINDEX
#define CONFIG_CANOPEN_RXPDO3_MAPPING4_LEN			CANOPEN_TYPE_LEN(FSB_DOORSW1_TYPE)
#define CONFIG_CANOPEN_RXPDO3_MAPPING5_MAIN_INDEX	HCU_FSB_INDEX_OFFSET + FSB_DOORSW2_INDEX
#define CONFIG_CANOPEN_RXPDO3_MAPPING5_SUB_INDEX	FSB_DOORSW2_SUBINDEX
#define CONFIG_CANOPEN_RXPDO3_MAPPING5_LEN			CANOPEN_TYPE_LEN(FSB_DOORSW2_TYPE)
#define CONFIG_CANOPEN_RXPDO3_MAPPING6_MAIN_INDEX	HCU_FSB_INDEX_OFFSET + FSB_SEATSW_INDEX
#define CONFIG_CANOPEN_RXPDO3_MAPPING6_SUB_INDEX	FSB_SEATSW_SUBINDEX
#define CONFIG_CANOPEN_RXPDO3_MAPPING6_LEN			CANOPEN_TYPE_LEN(FSB_SEATSW_TYPE)
#define CONFIG_CANOPEN_RXPDO3_MAPPING7_MAIN_INDEX	0
#define CONFIG_CANOPEN_RXPDO3_MAPPING7_SUB_INDEX	0
#define CONFIG_CANOPEN_RXPDO3_MAPPING7_LEN			0
#define CONFIG_CANOPEN_RXPDO3_MAPPING8_MAIN_INDEX	0
#define CONFIG_CANOPEN_RXPDO3_MAPPING8_SUB_INDEX	0
#define CONFIG_CANOPEN_RXPDO3_MAPPING8_LEN			0

#define CONFIG_CANOPEN_RXPDO4_ID					(CANOPEN_TXPDO1_ID + LKEYPAD_NODE_ID)
#define CONFIG_CANOPEN_RXPDO4_TRANSMISSION_TYPE		CANOPEN_PDO_TRANSMISSION_ASYNC
#define CONFIG_CANOPEN_RXPDO4_MAPPING1_MAIN_INDEX	HCU_BOOM_ROTATE_REQ_INDEX
#define CONFIG_CANOPEN_RXPDO4_MAPPING1_SUB_INDEX	HCU_BOOM_ROTATE_REQ_SUBINDEX
#define CONFIG_CANOPEN_RXPDO4_MAPPING1_LEN			CANOPEN_TYPE_LEN(KEYP_JOYX_TYPE)
#define CONFIG_CANOPEN_RXPDO4_MAPPING2_MAIN_INDEX	0
#define CONFIG_CANOPEN_RXPDO4_MAPPING2_SUB_INDEX	0
#define CONFIG_CANOPEN_RXPDO4_MAPPING2_LEN			CANOPEN_TYPE_LEN(KEYP_JOYX_TYPE)
#define CONFIG_CANOPEN_RXPDO4_MAPPING3_MAIN_INDEX	HCU_BOOM_FOLD_REQ_INDEX
#define CONFIG_CANOPEN_RXPDO4_MAPPING3_SUB_INDEX	HCU_BOOM_FOLD_REQ_SUBINDEX
#define CONFIG_CANOPEN_RXPDO4_MAPPING3_LEN			CANOPEN_TYPE_LEN(KEYP_JOYY_TYPE)
#define CONFIG_CANOPEN_RXPDO4_MAPPING4_MAIN_INDEX	0
#define CONFIG_CANOPEN_RXPDO4_MAPPING4_SUB_INDEX	0
#define CONFIG_CANOPEN_RXPDO4_MAPPING4_LEN			CANOPEN_TYPE_LEN(KEYP_JOYY_TYPE)
#define CONFIG_CANOPEN_RXPDO4_MAPPING5_MAIN_INDEX	0
#define CONFIG_CANOPEN_RXPDO4_MAPPING5_SUB_INDEX	0
#define CONFIG_CANOPEN_RXPDO4_MAPPING5_LEN			CANOPEN_TYPE_LEN(KEYP_JOYZ_TYPE)
#define CONFIG_CANOPEN_RXPDO4_MAPPING6_MAIN_INDEX	0
#define CONFIG_CANOPEN_RXPDO4_MAPPING6_SUB_INDEX	0
#define CONFIG_CANOPEN_RXPDO4_MAPPING6_LEN			CANOPEN_TYPE_LEN(KEYP_JOYZ_TYPE)
#define CONFIG_CANOPEN_RXPDO4_MAPPING7_MAIN_INDEX	0
#define CONFIG_CANOPEN_RXPDO4_MAPPING7_SUB_INDEX	0
#define CONFIG_CANOPEN_RXPDO4_MAPPING7_LEN			CANOPEN_TYPE_LEN(KEYP_JOYV_TYPE)
#define CONFIG_CANOPEN_RXPDO4_MAPPING8_MAIN_INDEX	0
#define CONFIG_CANOPEN_RXPDO4_MAPPING8_SUB_INDEX	0
#define CONFIG_CANOPEN_RXPDO4_MAPPING8_LEN			CANOPEN_TYPE_LEN(KEYP_JOYV_TYPE)

#define CONFIG_CANOPEN_RXPDO5_ID					(CANOPEN_TXPDO2_ID + LKEYPAD_NODE_ID)
#define CONFIG_CANOPEN_RXPDO5_TRANSMISSION_TYPE		CANOPEN_PDO_TRANSMISSION_ASYNC
#define CONFIG_CANOPEN_RXPDO5_MAPPING1_MAIN_INDEX	HCU_LEFT_FOOT_REQ_INDEX
#define CONFIG_CANOPEN_RXPDO5_MAPPING1_SUB_INDEX	HCU_LEFT_FOOT_REQ_SUBINDEX
#define CONFIG_CANOPEN_RXPDO5_MAPPING1_LEN			CANOPEN_TYPE_LEN(KEYP_BUTTON1_TYPE)
#define CONFIG_CANOPEN_RXPDO5_MAPPING2_MAIN_INDEX	0
#define CONFIG_CANOPEN_RXPDO5_MAPPING2_SUB_INDEX	0
#define CONFIG_CANOPEN_RXPDO5_MAPPING2_LEN			CANOPEN_TYPE_LEN(KEYP_BUTTON2_TYPE)
#define CONFIG_CANOPEN_RXPDO5_MAPPING3_MAIN_INDEX	0
#define CONFIG_CANOPEN_RXPDO5_MAPPING3_SUB_INDEX	0
#define CONFIG_CANOPEN_RXPDO5_MAPPING3_LEN			CANOPEN_TYPE_LEN(KEYP_BUTTON3_TYPE)
#define CONFIG_CANOPEN_RXPDO5_MAPPING4_MAIN_INDEX	0
#define CONFIG_CANOPEN_RXPDO5_MAPPING4_SUB_INDEX	0
#define CONFIG_CANOPEN_RXPDO5_MAPPING4_LEN			CANOPEN_TYPE_LEN(KEYP_BUTTON4_TYPE)
#define CONFIG_CANOPEN_RXPDO5_MAPPING5_MAIN_INDEX	0
#define CONFIG_CANOPEN_RXPDO5_MAPPING5_SUB_INDEX	0
#define CONFIG_CANOPEN_RXPDO5_MAPPING5_LEN			CANOPEN_TYPE_LEN(KEYP_BUTTON5_INDEX)
#define CONFIG_CANOPEN_RXPDO5_MAPPING6_MAIN_INDEX	0
#define CONFIG_CANOPEN_RXPDO5_MAPPING6_SUB_INDEX	0
#define CONFIG_CANOPEN_RXPDO5_MAPPING6_LEN			CANOPEN_TYPE_LEN(KEYP_BUTTON6_TYPE)
#define CONFIG_CANOPEN_RXPDO5_MAPPING7_MAIN_INDEX	0
#define CONFIG_CANOPEN_RXPDO5_MAPPING7_SUB_INDEX	0
#define CONFIG_CANOPEN_RXPDO5_MAPPING7_LEN			CANOPEN_TYPE_LEN(KEYP_BUTTON7_TYPE)
#define CONFIG_CANOPEN_RXPDO5_MAPPING8_MAIN_INDEX	0
#define CONFIG_CANOPEN_RXPDO5_MAPPING8_SUB_INDEX	0
#define CONFIG_CANOPEN_RXPDO5_MAPPING8_LEN			CANOPEN_TYPE_LEN(0)

#define CONFIG_CANOPEN_RXPDO6_ID					(CANOPEN_TXPDO1_ID + RKEYPAD_NODE_ID)
#define CONFIG_CANOPEN_RXPDO6_TRANSMISSION_TYPE		CANOPEN_PDO_TRANSMISSION_ASYNC
#define CONFIG_CANOPEN_RXPDO6_MAPPING1_MAIN_INDEX	0
#define CONFIG_CANOPEN_RXPDO6_MAPPING1_SUB_INDEX	0
#define CONFIG_CANOPEN_RXPDO6_MAPPING1_LEN			CANOPEN_TYPE_LEN(KEYP_JOYX_TYPE)
#define CONFIG_CANOPEN_RXPDO6_MAPPING2_MAIN_INDEX	0
#define CONFIG_CANOPEN_RXPDO6_MAPPING2_SUB_INDEX	0
#define CONFIG_CANOPEN_RXPDO6_MAPPING2_LEN			CANOPEN_TYPE_LEN(KEYP_JOYX_TYPE)
#define CONFIG_CANOPEN_RXPDO6_MAPPING3_MAIN_INDEX	HCU_BOOM_LIFT_REQ_INDEX
#define CONFIG_CANOPEN_RXPDO6_MAPPING3_SUB_INDEX	HCU_BOOM_LIFT_REQ_SUBINDEX
#define CONFIG_CANOPEN_RXPDO6_MAPPING3_LEN			CANOPEN_TYPE_LEN(KEYP_JOYY_TYPE)
#define CONFIG_CANOPEN_RXPDO6_MAPPING4_MAIN_INDEX	0
#define CONFIG_CANOPEN_RXPDO6_MAPPING4_SUB_INDEX	0
#define CONFIG_CANOPEN_RXPDO6_MAPPING4_LEN			CANOPEN_TYPE_LEN(KEYP_JOYY_TYPE)
#define CONFIG_CANOPEN_RXPDO6_MAPPING5_MAIN_INDEX	0
#define CONFIG_CANOPEN_RXPDO6_MAPPING5_SUB_INDEX	0
#define CONFIG_CANOPEN_RXPDO6_MAPPING5_LEN			CANOPEN_TYPE_LEN(KEYP_JOYZ_TYPE)
#define CONFIG_CANOPEN_RXPDO6_MAPPING6_MAIN_INDEX	0
#define CONFIG_CANOPEN_RXPDO6_MAPPING6_SUB_INDEX	0
#define CONFIG_CANOPEN_RXPDO6_MAPPING6_LEN			CANOPEN_TYPE_LEN(KEYP_JOYZ_TYPE)
#define CONFIG_CANOPEN_RXPDO6_MAPPING7_MAIN_INDEX	0
#define CONFIG_CANOPEN_RXPDO6_MAPPING7_SUB_INDEX	0
#define CONFIG_CANOPEN_RXPDO6_MAPPING7_LEN			CANOPEN_TYPE_LEN(KEYP_JOYV_TYPE)
#define CONFIG_CANOPEN_RXPDO6_MAPPING8_MAIN_INDEX	0
#define CONFIG_CANOPEN_RXPDO6_MAPPING8_SUB_INDEX	0
#define CONFIG_CANOPEN_RXPDO6_MAPPING8_LEN			CANOPEN_TYPE_LEN(KEYP_JOYV_TYPE)

#define CONFIG_CANOPEN_RXPDO7_ID					(CANOPEN_TXPDO2_ID + RKEYPAD_NODE_ID)
#define CONFIG_CANOPEN_RXPDO7_TRANSMISSION_TYPE		CANOPEN_PDO_TRANSMISSION_ASYNC
#define CONFIG_CANOPEN_RXPDO7_MAPPING1_MAIN_INDEX	HCU_RIGHT_FOOT_REQ_INDEX
#define CONFIG_CANOPEN_RXPDO7_MAPPING1_SUB_INDEX	HCU_RIGHT_FOOT_REQ_SUBINDEX
#define CONFIG_CANOPEN_RXPDO7_MAPPING1_LEN			CANOPEN_TYPE_LEN(KEYP_BUTTON1_TYPE)
#define CONFIG_CANOPEN_RXPDO7_MAPPING2_MAIN_INDEX	0
#define CONFIG_CANOPEN_RXPDO7_MAPPING2_SUB_INDEX	0
#define CONFIG_CANOPEN_RXPDO7_MAPPING2_LEN			CANOPEN_TYPE_LEN(KEYP_BUTTON2_TYPE)
#define CONFIG_CANOPEN_RXPDO7_MAPPING3_MAIN_INDEX	0
#define CONFIG_CANOPEN_RXPDO7_MAPPING3_SUB_INDEX	0
#define CONFIG_CANOPEN_RXPDO7_MAPPING3_LEN			CANOPEN_TYPE_LEN(KEYP_BUTTON3_TYPE)
#define CONFIG_CANOPEN_RXPDO7_MAPPING4_MAIN_INDEX	0
#define CONFIG_CANOPEN_RXPDO7_MAPPING4_SUB_INDEX	0
#define CONFIG_CANOPEN_RXPDO7_MAPPING4_LEN			CANOPEN_TYPE_LEN(KEYP_BUTTON4_TYPE)
#define CONFIG_CANOPEN_RXPDO7_MAPPING5_MAIN_INDEX	0
#define CONFIG_CANOPEN_RXPDO7_MAPPING5_SUB_INDEX	0
#define CONFIG_CANOPEN_RXPDO7_MAPPING5_LEN			CANOPEN_TYPE_LEN(KEYP_BUTTON5_TYPE)
#define CONFIG_CANOPEN_RXPDO7_MAPPING6_MAIN_INDEX	0
#define CONFIG_CANOPEN_RXPDO7_MAPPING6_SUB_INDEX	0
#define CONFIG_CANOPEN_RXPDO7_MAPPING6_LEN			CANOPEN_TYPE_LEN(KEYP_BUTTON6_TYPE)
#define CONFIG_CANOPEN_RXPDO7_MAPPING7_MAIN_INDEX	HCU_BOOM_TELESCOPE_REQ_INDEX
#define CONFIG_CANOPEN_RXPDO7_MAPPING7_SUB_INDEX	HCU_BOOM_TELESCOPE_REQ_SUBINDEX
#define CONFIG_CANOPEN_RXPDO7_MAPPING7_LEN			CANOPEN_TYPE_LEN(KEYP_BUTTON7_TYPE)
#define CONFIG_CANOPEN_RXPDO7_MAPPING8_MAIN_INDEX	0
#define CONFIG_CANOPEN_RXPDO7_MAPPING8_SUB_INDEX	0
#define CONFIG_CANOPEN_RXPDO7_MAPPING8_LEN			CANOPEN_TYPE_LEN(0)

#define CONFIG_CANOPEN_RXPDO8_ID					(CANOPEN_TXPDO1_ID + CCU_NODE_ID)
#define CONFIG_CANOPEN_RXPDO8_TRANSMISSION_TYPE		CANOPEN_PDO_TRANSMISSION_ASYNC
#define CONFIG_CANOPEN_RXPDO8_MAPPING1_MAIN_INDEX	0
#define CONFIG_CANOPEN_RXPDO8_MAPPING1_SUB_INDEX	0
#define CONFIG_CANOPEN_RXPDO8_MAPPING1_LEN			CANOPEN_TYPE_LEN(CCU_TOTAL_CURRENT_TYPE)
#define CONFIG_CANOPEN_RXPDO8_MAPPING2_MAIN_INDEX	0
#define CONFIG_CANOPEN_RXPDO8_MAPPING2_SUB_INDEX	0
#define CONFIG_CANOPEN_RXPDO8_MAPPING2_LEN			CANOPEN_TYPE_LEN(CCU_GEAR_TYPE)
#define CONFIG_CANOPEN_RXPDO8_MAPPING3_MAIN_INDEX	0
#define CONFIG_CANOPEN_RXPDO8_MAPPING3_SUB_INDEX	0
#define CONFIG_CANOPEN_RXPDO8_MAPPING3_LEN			CANOPEN_TYPE_LEN(CCU_STEER_REQ_TYPE)
#define CONFIG_CANOPEN_RXPDO8_MAPPING4_MAIN_INDEX	HCU_CCU_INDEX_OFFSET + CCU_DRIVE_REQ_INDEX
#define CONFIG_CANOPEN_RXPDO8_MAPPING4_SUB_INDEX	CCU_DRIVE_REQ_SUBINDEX
#define CONFIG_CANOPEN_RXPDO8_MAPPING4_LEN			CANOPEN_TYPE_LEN(CCU_DRIVE_REQ_TYPE)
#define CONFIG_CANOPEN_RXPDO8_MAPPING5_MAIN_INDEX	0
#define CONFIG_CANOPEN_RXPDO8_MAPPING5_SUB_INDEX	0
#define CONFIG_CANOPEN_RXPDO8_MAPPING5_LEN			0
#define CONFIG_CANOPEN_RXPDO8_MAPPING6_MAIN_INDEX	0
#define CONFIG_CANOPEN_RXPDO8_MAPPING6_SUB_INDEX	0
#define CONFIG_CANOPEN_RXPDO8_MAPPING6_LEN			0
#define CONFIG_CANOPEN_RXPDO8_MAPPING7_MAIN_INDEX	0
#define CONFIG_CANOPEN_RXPDO8_MAPPING7_SUB_INDEX	0
#define CONFIG_CANOPEN_RXPDO8_MAPPING7_LEN			0
#define CONFIG_CANOPEN_RXPDO8_MAPPING8_MAIN_INDEX	0
#define CONFIG_CANOPEN_RXPDO8_MAPPING8_SUB_INDEX	0
#define CONFIG_CANOPEN_RXPDO8_MAPPING8_LEN			0


#define CONFIG_CANOPEN_TXPDO1_ID					(CANOPEN_TXPDO1_ID + HCU_NODE_ID)
#define CONFIG_CANOPEN_TXPDO1_TRANSMISSION_TYPE		CANOPEN_PDO_TRANSMISSION_ASYNC
#define CONFIG_CANOPEN_TXPDO1_EVENT_TIMER			40
#define CONFIG_CANOPEN_TXPDO1_INHIBIT_TIME			20
#define CONFIG_CANOPEN_TXPDO1_MAPPING1_MAIN_INDEX	HCU_TOTAL_CURRENT_INDEX
#define CONFIG_CANOPEN_TXPDO1_MAPPING1_SUB_INDEX	HCU_TOTAL_CURRENT_SUBINDEX
#define CONFIG_CANOPEN_TXPDO1_MAPPING1_LEN			CANOPEN_TYPE_LEN(HCU_TOTAL_CURRENT_TYPE)
#define CONFIG_CANOPEN_TXPDO1_MAPPING2_MAIN_INDEX	HCU_IMPLEMENT_INDEX
#define CONFIG_CANOPEN_TXPDO1_MAPPING2_SUB_INDEX	HCU_IMPLEMENT_SUBINDEX
#define CONFIG_CANOPEN_TXPDO1_MAPPING2_LEN			CANOPEN_TYPE_LEN(HCU_IMPLEMENT_TYPE)
#define CONFIG_CANOPEN_TXPDO1_MAPPING3_MAIN_INDEX	HCU_PRESSURE_INDEX
#define CONFIG_CANOPEN_TXPDO1_MAPPING3_SUB_INDEX	HCU_PRESSURE_SUBINDEX
#define CONFIG_CANOPEN_TXPDO1_MAPPING3_LEN			CANOPEN_TYPE_LEN(HCU_PRESSURE_TYPE)
#define CONFIG_CANOPEN_TXPDO1_MAPPING4_MAIN_INDEX	HCU_BOOM_LIFT_REQ_INDEX
#define CONFIG_CANOPEN_TXPDO1_MAPPING4_SUB_INDEX	HCU_BOOM_LIFT_REQ_SUBINDEX
#define CONFIG_CANOPEN_TXPDO1_MAPPING4_LEN			CANOPEN_TYPE_LEN(HCU_BOOM_LIFT_REQ_TYPE)
#define CONFIG_CANOPEN_TXPDO1_MAPPING5_MAIN_INDEX	HCU_BOOM_FOLD_REQ_INDEX
#define CONFIG_CANOPEN_TXPDO1_MAPPING5_SUB_INDEX	HCU_BOOM_FOLD_REQ_SUBINDEX
#define CONFIG_CANOPEN_TXPDO1_MAPPING5_LEN			CANOPEN_TYPE_LEN(HCU_BOOM_FOLD_REQ_TYPE)
#define CONFIG_CANOPEN_TXPDO1_MAPPING6_MAIN_INDEX	HCU_BOOM_ROTATE_REQ_INDEX
#define CONFIG_CANOPEN_TXPDO1_MAPPING6_SUB_INDEX	HCU_BOOM_ROTATE_REQ_SUBINDEX
#define CONFIG_CANOPEN_TXPDO1_MAPPING6_LEN			CANOPEN_TYPE_LEN(HCU_BOOM_ROTATE_REQ_TYPE)
#define CONFIG_CANOPEN_TXPDO1_MAPPING7_MAIN_INDEX	0
#define CONFIG_CANOPEN_TXPDO1_MAPPING7_SUB_INDEX	0
#define CONFIG_CANOPEN_TXPDO1_MAPPING7_LEN			CANOPEN_TYPE_LEN(0)
#define CONFIG_CANOPEN_TXPDO1_MAPPING8_MAIN_INDEX	0
#define CONFIG_CANOPEN_TXPDO1_MAPPING8_SUB_INDEX	0
#define CONFIG_CANOPEN_TXPDO1_MAPPING8_LEN			CANOPEN_TYPE_LEN(0)


#define CONFIG_CANOPEN_TXPDO2_ID					(CANOPEN_TXPDO2_ID + HCU_NODE_ID)
#define CONFIG_CANOPEN_TXPDO2_TRANSMISSION_TYPE		CANOPEN_PDO_TRANSMISSION_ASYNC
#define CONFIG_CANOPEN_TXPDO2_EVENT_TIMER			200
#define CONFIG_CANOPEN_TXPDO2_INHIBIT_TIME			20
#define CONFIG_CANOPEN_TXPDO2_MAPPING1_MAIN_INDEX	HCU_BOOM_TELESCOPE_REQ_INDEX
#define CONFIG_CANOPEN_TXPDO2_MAPPING1_SUB_INDEX	HCU_BOOM_TELESCOPE_REQ_SUBINDEX
#define CONFIG_CANOPEN_TXPDO2_MAPPING1_LEN			CANOPEN_TYPE_LEN(HCU_BOOM_TELESCOPE_REQ_TYPE)
#define CONFIG_CANOPEN_TXPDO2_MAPPING2_MAIN_INDEX	HCU_LEFT_FOOT_REQ_INDEX
#define CONFIG_CANOPEN_TXPDO2_MAPPING2_SUB_INDEX	HCU_LEFT_FOOT_REQ_SUBINDEX
#define CONFIG_CANOPEN_TXPDO2_MAPPING2_LEN			CANOPEN_TYPE_LEN(HCU_LEFT_FOOT_REQ_TYPE)
#define CONFIG_CANOPEN_TXPDO2_MAPPING3_MAIN_INDEX	HCU_RIGHT_FOOT_REQ_INDEX
#define CONFIG_CANOPEN_TXPDO2_MAPPING3_SUB_INDEX	HCU_RIGHT_FOOT_REQ_SUBINDEX
#define CONFIG_CANOPEN_TXPDO2_MAPPING3_LEN			CANOPEN_TYPE_LEN(HCU_RIGHT_FOOT_REQ_TYPE)
#define CONFIG_CANOPEN_TXPDO2_MAPPING4_MAIN_INDEX	HCU_ROTATOR_REQ_INDEX
#define CONFIG_CANOPEN_TXPDO2_MAPPING4_SUB_INDEX	HCU_ROTATOR_REQ_SUBINDEX
#define CONFIG_CANOPEN_TXPDO2_MAPPING4_LEN			CANOPEN_TYPE_LEN(HCU_ROTATOR_REQ_TYPE)
#define CONFIG_CANOPEN_TXPDO2_MAPPING5_MAIN_INDEX	HCU_IMPL1_REQ_INDEX
#define CONFIG_CANOPEN_TXPDO2_MAPPING5_SUB_INDEX	HCU_IMPL1_REQ_SUBINDEX
#define CONFIG_CANOPEN_TXPDO2_MAPPING5_LEN			CANOPEN_TYPE_LEN(HCU_IMPL1_REQ_TYPE)
#define CONFIG_CANOPEN_TXPDO2_MAPPING6_MAIN_INDEX	HCU_IMPL2_REQ_INDEX
#define CONFIG_CANOPEN_TXPDO2_MAPPING6_SUB_INDEX	HCU_IMPL2_REQ_SUBINDEX
#define CONFIG_CANOPEN_TXPDO2_MAPPING6_LEN			CANOPEN_TYPE_LEN(HCU_IMPL2_REQ_TYPE)
#define CONFIG_CANOPEN_TXPDO2_MAPPING7_MAIN_INDEX	HCU_LEFT_FOOT_STATE_INDEX
#define CONFIG_CANOPEN_TXPDO2_MAPPING7_SUB_INDEX	HCU_LEFT_FOOT_STATE_SUBINDEX
#define CONFIG_CANOPEN_TXPDO2_MAPPING7_LEN			CANOPEN_TYPE_LEN(HCU_LEFT_FOOT_STATE_TYPE)
#define CONFIG_CANOPEN_TXPDO2_MAPPING8_MAIN_INDEX	HCU_RIGHT_FOOT_STATE_INDEX
#define CONFIG_CANOPEN_TXPDO2_MAPPING8_SUB_INDEX	HCU_RIGHT_FOOT_STATE_SUBINDEX
#define CONFIG_CANOPEN_TXPDO2_MAPPING8_LEN			CANOPEN_TYPE_LEN(HCU_RIGHT_FOOT_STATE_TYPE)



#define CONFIG_OUTPUT								1

#define CONFIG_SOLENOID_OUTPUT						1
#define CONFIG_SOLENOID_MA_P						1000
#define CONFIG_SOLENOID_MA_I						4
#define CONFIG_SOLENOID_MAX_CURRENT_DEF				1800
#define CONFIG_SOLENOID_MIN_CURRENT_DEF				600
#define CONFIG_SOLENOID_MODE_PWM					0
#define CONFIG_SOLENOID_MODE_ONOFF					0
#define CONFIG_PID									1
#define CONFIG_DUAL_SOLENOID_OUTPUT					1
#define CONFIG_DUAL_SOLENOID_ACC_DEF				100
#define CONFIG_DUAL_SOLENOID_DEC_DEF				100

/**** END OF USER CONFIGURATIONS ****/




#endif /* UV_HAL_CONFIG_H_ */
