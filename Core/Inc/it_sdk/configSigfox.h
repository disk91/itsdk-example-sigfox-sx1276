/* ==========================================================
 * configSigfox.h - SDK Configuration file for Sigfox communication
 * Project : Disk91 SDK
 * ----------------------------------------------------------
 * Created on: 4 nov. 2018
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
 * S2LP:
 *    In cube MX declare the CSn and SDN pin as output.
 *      CSn is pullup set to High initially
 *      SDN is set to low initially (no shutdown)
 *    Declare SPI. default configuration normally match.
 *
 * ==========================================================
 */

#ifndef IT_SDK_CONFIG_SIGFOX_H_
#define IT_SDK_CONFIG_SIGFOX_H_

#include <it_sdk/config_defines.h>
#if ITSDK_SIGFOX_LIB == __SIGFOX_S2LP || ITSDK_SIGFOX_LIB == __SIGFOX_SX1276
	#include "spi.h"
    #include <it_sdk/sigfox/sigfox.h>
#endif

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// | SDK SETTING                   | USER SELECTED VALUE                  | SETTING DESCRIPTION                   |
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +------------SIGFOX-------------|--------------------------------------|---------------------------------------|
#if ITSDK_WITH_SIGFOX_LIB == 1
#define ITSDK_SIGFOX_ENCRYPTION		(   __PAYLOAD_ENCRYPT_AESCTR \
									  | __PAYLOAD_ENCRYPT_SPECK  \
									 /* | __PAYLOAD_ENCRYPT_SIGFOX */ \
									)										// Encryption code activated

#define ITSDK_SIGFOX_MEM_SIZE		256										// Static memory allocated to sigfox
#define ITSDK_SIGFOX_NVM_SOURCE		__SFX_NVM_LOCALEPROM					// where the non volatile information are stored
#define ITSDK_SIGFOX_NVM_BASEADDR	0x600									// Base address in the NVM for sigfox lib
#define ITSDK_SIGFOX_NVM_IDBASEADDR	0x200									// Base address in the NVM for EncUtils lib
#define ITSDK_SIGFOX_LOWPOWER		0										// When 1 the device can be switch to low power by the sigfox lib
#define ITSDK_SIGFOX_ID				0x00D206AF								// The device ID when NVM_SOURCE is HEADERS
#define ITSDK_SIGFOX_PAC			{ 0x58, 0x1B, 0xD4, 0x43, \
									  0x6C, 0xB0, 0x7D, 0xBD }				// The device PAC when NVM_SOURCE is HEADERS
#define ITDSK_SIGFOX_RCZ			SIGFOX_RCZ1								// The default RCZ when NVM_SOURCE is HEADERS
#define ITSDK_SIGFOX_KEY_TYPE		SIGFOX_KEY_PRIVATE						// Type of key to be used SIGFOX_KEY_PRIVATE / SIGFOX_KEY_PUBLIC
#define ITSDK_SIGFOX_TXPOWER		SIGFOX_DEFAULT_POWER					// Default Tx power in dB - can be replaced by a value in dB
#define ITSDK_SIGFOX_SPEED			SIGFOX_DEFAULT_SPEED					// Default Speed in bps - can be replaced by a value in BPS
#define ITSDK_SIGFOX_RSSICAL		0										// Default Rssi Calibration
#define ITSDK_SIGFOX_KEY			{ 0x42, 0x39, 0x45, 0x14, \
									  0xF9, 0x90, 0x16, 0xC3, \
									  0xA7, 0x33, 0x4A, 0x12, \
									  0xCF, 0xFD, 0x4A, 0x2C }				// The device KEY when NVM_SOURCE is HEADERS
																			// The Key is in clear here
#define ITSDK_SIGFOX_KEY_PUBLIC		{ 0x00, 0x11, 0x22, 0x33, \
	                                  0x44, 0x55, 0x66, 0x77, \
                                      0x88, 0x99, 0xAA, 0xBB, \
									  0xCC, 0xDD, 0xEE, 0xFF }				// The sigfox PUBLIC key (do not change this)

#define ITSDK_SIGFOX_AUX			{ 0x00, 0x00, 0x00, 0x00, \
									  0x00, 0x00, 0x00, 0x00, \
									  0x00, 0x00, 0x00, 0x00, \
									  0x00, 0x00, 0x00, 0x00 }				// The device AUX when NVM_SOURCE is HEADERS
/*
#define ITSDK_SIGFOX_PAC			{ 0x00, 0x00, 0x00, 0x00, \
									  0x00, 0x00, 0x00, 0x00 }				// The device PAC when NVM_SOURCE is HEADERS
#define ITDSK_SIGFOX_RCZ			0x1										// The default RCZ when NVM_SOURCE is HEADERS
#define ITSDK_SIGFOX_KEY			{ 0x00, 0x00, 0x00, 0x00, \
									  0x00, 0x00, 0x00, 0x00, \
									  0x00, 0x00, 0x00, 0x00, \
									  0x00, 0x00, 0x00, 0x00 }				// The device KEY when NVM_SOURCE is HEADERS
																			// The Key is in clear here
#define ITSDK_SIGFOX_AUX			{ 0x00, 0x00, 0x00, 0x00, \
									  0x00, 0x00, 0x00, 0x00, \
									  0x00, 0x00, 0x00, 0x00, \
									  0x00, 0x00, 0x00, 0x00 }				// The device AUX when NVM_SOURCE is HEADERS
*/
#endif
// +---------------S2LP------------|--------------------------------------|---------------------------------------|
#if ITSDK_SIGFOX_LIB == __SIGFOX_S2LP
#define ITSDK_S2LP_SPI				hspi1								   // SPI To BE USED
																		   // SPI Configured by CubeMX
																		   //  Master, 8b, Polarity Low,
																		   //  first bit msb, CRC disable...

#define ITSDK_S2LP_CS_BANK			 __BANK_A							   // S2LP Chip Select PIN LAYOUT (Activ Low)
#define ITSDK_S2LP_CS_PIN			 __LP_GPIO_1
#define ITSDK_S2LP_SDN_BANK			 __BANK_A							   // S2LP Chip Shutdown PIN LAYOUT (Activ High)
#define ITSDK_S2LP_SDN_PIN			 __LP_GPIO_8
#define ITSDK_S2LP_GPIO0_BANK		 __BANK_A							   // S2LP Interrupt GPIO0 LAYOUT
#define ITSDK_S2LP_GPIO0_PIN		 __LP_GPIO_0						   //   Default PA0 <=> GPIO0 on S2LP
#define ITSDK_S2LP_GPIO1_BANK		 __BANK_A							   // S2LP Interrupt GPIO1 LAYOUT
#define ITSDK_S2LP_GPIO1_PIN		 __LP_GPIO_4						   //   Default PA4 <=> GPIO1 on S2LP
																		   //   Configured as input
#define ITSDK_S2LP_GPIO2_BANK		 __BANK_B							   // S2LP Interrupt GPIO2 LAYOUT
#define ITSDK_S2LP_GPIO2_PIN		 __LP_GPIO_0						   //   Default PB0 <=> GPIO2 on S2LP
																		   //   Configured as input
#define ITSDK_S2LP_GPIO3_BANK		 __BANK_C							   // S2LP Interrupt GPIO3 LAYOUT
#define ITSDK_S2LP_GPIO3_PIN		 __LP_GPIO_0						   //   Default PC0 <=> GPIO3 on S2LP
																		   //   Configured as Rising with pull-down

#define ITSDK_S2LP_CNF_TCX0			__S2LP_W_O_TCXO					   	   // Absence of a TCXO
#define ITSDK_S2LP_CNF_RANGE		0
#define ITSDK_S2LP_CNF_BAND			3
#define ITSDK_S2LP_CNF_FREQ			50000000
#define ITSDK_S2LP_CNF_OFFSET		0
#define ITSDK_SIGFOX_EXTENSIONS	    __SIGFOX_MONARCH			   		  // Customize the sigfox lib (be careful as there is a link with precompiled library)
#endif //__SIGFOX_S2LP
// +------------MURATA------------|--------------------------------------|---------------------------------------|
#if ITSDK_SIGFOX_LIB == __SIGFOX_SX1276
#ifndef ITSDK_SX1276_SPI												   // if not yet defined in configLoRaWan
#define ITSDK_SX1276_SPI			hspi1						   	   	   // SPI handler To BE USED
																		   // SPI Configured by CubeMX
																		   //  Master, 8b, Polarity Low,
																		   //  first bit msb, CRC disable...
#define ITSDK_SX1276_TIM_ID			2								   	   // Timer used => Should not be changed
																		   // Need to b activated in the CubeMx project
#define ITSDK_SX1276_SPIDMATX		hdma_spi1_tx						   // Associated DMA

#define ITSDK_SX1276_RESET_BANK		 		__BANK_C						   // SX1276 GPIO FOR RESET
#define ITSDK_SX1276_RESET_PIN		 		__LP_GPIO_0
#define ITSDK_SX1276_NSS_BANK		 		__BANK_A						   // SX1276 GPIO FOR Activating Low Slave Select NSS
#define ITSDK_SX1276_NSS_PIN		 		__LP_GPIO_15
#define ITSDK_SX1276_TCXO_VCC_BANK	 		__BANK_A						   // SX1276 GPIO FOR Activating TCXO
#define ITSDK_SX1276_TCXO_VCC_PIN	 		__LP_GPIO_12
#define ITSDK_SX1276_DIO_0_BANK	 	 		__BANK_B						   // SX1276 GPIO 0 => Rx/Tx Done interrupt
#define ITSDK_SX1276_DIO_0_PIN	 	 		__LP_GPIO_4
#define ITSDK_SX1276_DIO_1_BANK	 	 		__BANK_B						   // SX1276 GPIO 1 => Rx Timeout interrupt
#define ITSDK_SX1276_DIO_1_PIN	 	 		__LP_GPIO_1
#define ITSDK_SX1276_DIO_2_BANK	 	 		__BANK_B						   // SX1276 GPIO 2 => Fhss Change channel
#define ITSDK_SX1276_DIO_2_PIN	 	 		__LP_GPIO_0
#define ITSDK_SX1276_DIO_3_BANK	 	 		__BANK_C						   // SX1276 GPIO 3 => cadDone/ValidHeader/Crc Error
#define ITSDK_SX1276_DIO_3_PIN	 	 		__LP_GPIO_13
#define ITSDK_SX1276_DIO_4_BANK	 	 		__BANK_A						   // SX1276 GPIO 4 => CAD Detected / Pll lock
#define ITSDK_SX1276_DIO_4_PIN	 	 		__LP_GPIO_5
#define ITSDK_SX1276_DIO_5_BANK	 	 		__BANK_A						   // SX1276 GPIO 5 => Mode Ready / Clk out
#define ITSDK_SX1276_DIO_5_PIN	 	 		__LP_GPIO_4
#define ITSDK_MURATA_ANTSW_RX_BANK 	     	__BANK_A						   // MURATA ANTENNA SWITCH RX
#define ITSDK_MURATE_ANTSW_RX_PIN	     	__LP_GPIO_1
#define ITSDK_MURATA_ANTSW_TXBOOST_BANK  	__BANK_C						   // MURATA TX POWER BOOST
#define ITSDK_MURATE_ANTSW_TXBOOST_PIN	 	__LP_GPIO_1
#define ITSDK_MURATA_ANTSW_TXRFO_BANK    	__BANK_C						   // MURATA TX RFO
#define ITSDK_MURATE_ANTSW_TXRFO_PIN	 	__LP_GPIO_2

#define ITSDK_SIGFOX_EXTENSIONS				__SIGFOX_NONE					   // Murata sigfox lib does not support Monarch
#endif																		   // Corresponding Interrupts needs to
																		   // have an interrupt handler configured.
																		   // EXTI activated for Pins in CubeMW for STM32
																		   // And corresponding PIN add in the Low level Handler (stm32L...it.c)

#endif // __SIGFOX_SX1276
// +-------------OTHERS------------|--------------------------------------|---------------------------------------|

#endif /* IT_SDK_CONFIG_SIGFOX_H_ */

