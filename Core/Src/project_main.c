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

#define LED_PORT	__BANK_B
#define LED_PIN		__LP_GPIO_5

#define COMFREQS	(10*60*1000)
#define TASKDELAYMS	(1000)

struct state {
	uint8_t 		led;
	uint32_t  		loops;
	uint32_t		lastComMS;
	itsdk_bool_e	setup;
} s_state;

void task() {

	// Just to get something provinf the activity
	uint8_t t[4] = { '/','|','\\','-'};
	log_info("\r%c ",t[s_state.loops & 3]);
	s_state.led = (s_state.led==__GPIO_VAL_SET)?__GPIO_VAL_RESET:__GPIO_VAL_SET;
	gpio_change(LED_PORT, LED_PIN,s_state.led);
	s_state.loops++;

	// wait for the board configuration
	itsdk_sigfox_device_is_t deviceId;
	itsdk_sigfox_getDeviceId(&deviceId);
	uint32_t d = (uint32_t)deviceId;
	if ( d != 0 ) {
		if ( s_state.setup == BOOL_FALSE) {
			log_info("Init Sigfox Stack ");
			if ( itsdk_sigfox_setup() == SIGFOX_INIT_SUCESS ) {
				log_info("success\r\n");
				s_state.setup = BOOL_TRUE;
			} else {
				log_info("failed\r\n");
			}
		}
		if ( s_state.setup == BOOL_TRUE && s_state.lastComMS > COMFREQS) {
			// Send a Sigfox Frame
			uint8_t f[12] = { 'a','b','c','d',4,5,6,7,8,9,10,11 };
			uint8_t r[8] = {0};
			itdsk_sigfox_txrx_t ret;
			ret = itsdk_sigfox_sendFrame(
					f,						// Message to transmit
					12,						// Size of this message
					2,						// repeat - 2 is sigfox required
					SIGFOX_SPEED_DEFAULT,	// default speed according to RC - 100BPS for EU
					SIGFOX_POWER_DEFAULT,	// default power according to RC - 14dBm for EU
					PAYLOAD_ENCRYPT_NONE,	// clear text transmission
					false,					// no downlink / ack request
					r						// buffer for downlink response ( could be NULL when downlink req is false
			);
			if ( ret == SIGFOX_TRANSMIT_SUCESS ) {
				log_info("Tx completed <3\r\n");
			} else {
				log_warn("Tx failed \r\n");
			}
			s_state.lastComMS = 0;
		} else {
			s_state.lastComMS += TASKDELAYMS;
		}
	}
}


void project_setup() {

	itsdk_delayMs(2000);
	log_info("Startup\r\n");				// print a message on the USART1
	_itsdk_console_printf("Booting\r\n");
	itsdk_delayMs(2000);

	//itsdk_config_resetToFactory();

	s_state.led = __GPIO_VAL_RESET;
	s_state.loops = 0;
	s_state.lastComMS = COMFREQS;
	s_state.setup = BOOL_FALSE;
	gpio_change(LED_PORT, LED_PIN,s_state.led);

	itdt_sched_registerSched(TASKDELAYMS,ITSDK_SCHED_CONF_IMMEDIATE, &task);

	// lowPower_disable();
}

void project_loop() {

}

