/* ==========================================================
 * project_main.c - 
 * Project : Disk91 SDK
 * ----------------------------------------------------------
 * Created on: 6 sept. 2018
 *     Author: Paul Pinault aka Disk91
 * ----------------------------------------------------------
 * Copyright (C) 2018 Disk91
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU LESSER General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Lesser Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 * ----------------------------------------------------------
 * 
 * Add a such file in the main Src directory for executing
 * you own workload.
 *
 * ==========================================================
 */
#include <it_sdk/config.h>
#include <it_sdk/itsdk.h>
#include <it_sdk/logger/logger.h>
#include <it_sdk/sched/scheduler.h>
#include <it_sdk/console/console.h>
#include <it_sdk/sigfox/sigfox.h>

struct state {
	uint8_t 	led;
	uint32_t  	loops;
} s_state;

void task() {
	uint8_t t[4] = { '/','|','\\','-'};
	log_info("\r%c ",t[s_state.loops & 3]);
	s_state.led = (s_state.led==__GPIO_VAL_SET)?__GPIO_VAL_RESET:__GPIO_VAL_SET;
	gpio_change(__BANK_B, GPIO_PIN_5,s_state.led);
	s_state.loops++;
}


void project_setup() {
	log_info("Booting 2 \r\n");
	_itsdk_console_printf("Booting\r\n");

	//itsdk_config_resetToFactory();

	s_state.led = __GPIO_VAL_SET;
	s_state.loops = 0;
	gpio_change(__BANK_B, GPIO_PIN_5,s_state.led);
	itsdk_delayMs(2000);

	//itdt_sched_registerSched(1000,ITSDK_SCHED_CONF_IMMEDIATE, &task);

	// Misc init
	itsdk_sigfox_setup();
	uint8_t * strVersion;
	itsdk_sigfox_getSigfoxLibVersion(&strVersion);
	log_info("Sigfox Lib Version : %s\r\n",strVersion);

	itsdk_sigfox_device_is_t deviceId;
	itsdk_sigfox_getDeviceId(&deviceId);
	log_info("DeviceID is : 0x%08X\r\n",deviceId);

	// Send a Sigfox Frame
	uint8_t f[12] = { 'a','b','c','d',4,5,6,7,8,9,10,11 };
	uint8_t r[8] = {0};
	itdsk_sigfox_txrx_t ret = itsdk_sigfox_sendFrame(f,12,2,SIGFOX_SPEED_DEFAULT,SIGFOX_POWER_DEFAULT,PAYLOAD_ENCRYPT_NONE ,false,r);

	log_info("Tx completed <3 \r\n");

}

void project_loop() {

}

