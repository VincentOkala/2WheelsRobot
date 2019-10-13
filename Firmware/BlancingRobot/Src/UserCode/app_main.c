/*
 * app_main.c
 *
 *  Created on: Oct 9, 2019
 *      Author: 16138
 */

#ifndef USERCODE_APP_MAIN_C_
#define USERCODE_APP_MAIN_C_

#include <UserCode/Mode_PIDT/Mode_PIDT.h>
#include <UserCode/Mode_IMU/Mode_IMU.h>
#include <UserCode/Mode_Basic/Mode_Basic.h>

#include "app_main.h"
#include "Com/Com.h"
#include "UserCode/Mav/protocol/mavlink.h"
#include "UserCode/Params/Params.h"

typedef void (*func_t)(void);

static robot_mode_t  gmode = MODE_BASIC;
static func_t 		 gmode_init;
static func_t 		 gmode_deinit;
static on_mav_recv_t gon_mode_mav_recv;

static void on_mavlink_recv(mavlink_message_t *msg){
	if(msg->msgid == MAVLINK_MSG_ID_CMD_CHANGE_MODE){
		mavlink_cmd_change_mode_t cmd_change_mode;
		mavlink_msg_cmd_change_mode_decode(msg, &cmd_change_mode);
		gmode_deinit();
		if(cmd_change_mode.CMD_CHANGE_MODE == MODE_BASIC){
			gmode = MODE_BASIC;
			gmode_init = mode_basic_init;
			gmode_deinit = mode_basic_deinit;
			gon_mode_mav_recv = on_mode_basic_mavlink_recv;
		}
		else if(cmd_change_mode.CMD_CHANGE_MODE == MODE_IMU_CALIBRATION){
			gmode = MODE_IMU_CALIBRATION;
			gmode_init = mode_imu_init;
			gmode_deinit = mode_imu_deinit;
			gon_mode_mav_recv = on_mode_imu_mavlink_recv;
			gmode = MODE_IMU_CALIBRATION;
		}
		else if(cmd_change_mode.CMD_CHANGE_MODE == MODE_PID_TUNNING){
			gmode = MODE_PID_TUNNING;
			gmode_init = mode_pidt_init;
			gmode_deinit = mode_pidt_deinit;
			gon_mode_mav_recv = on_mode_pidt_mavlink_recv;
		}
		gmode_init();
		respond_ok();
	}
	else{
		gon_mode_mav_recv(msg);
	}
}

void app_main(){
	// Delay for other module to start
	HAL_Delay(1000);

	// Run default mode
	gmode_init = mode_basic_init;
	gmode_deinit = mode_basic_deinit;
	gon_mode_mav_recv = on_mode_basic_mavlink_recv;
	gmode_init();

	params_load();

	// Initialize communication
	com_init();
	com_set_on_mav_recv(on_mavlink_recv);
}

#endif /* USERCODE_APP_MAIN_C_ */
