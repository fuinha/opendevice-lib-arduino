/*
 * ******************************************************************************
 *  Copyright (c) 2013-2014 CriativaSoft (www.criativasoft.com.br)
 *  All rights reserved. This program and the accompanying materials
 *  are made available under the terms of the Eclipse Public License v1.0
 *  which accompanies this distribution, and is available at
 *  http://www.eclipse.org/legal/epl-v10.html
 *
 *  Contributors:
 *  Ricardo JL Rufino - Initial API and Implementation
 * *****************************************************************************
 */

#ifndef OPENDEVICE_CONFIG_H_
#define OPENDEVICE_CONFIG_H_

#include <Arduino.h>
#include <EEPROM.h>

#if defined(__COMPILING_AVR_LIBC__)
#include <avr/eeprom.h>
#endif

#ifndef __cplusplus
#error A C++ compiler is required!
#endif

// STATIC CONFIGURATION
// =====================================

#define DEBUG_SETUP	  0 // set 1 to enable (receiving debug)
#define DEBUG_CON	  0 // set 1 to enable (receiving debug)
#define ENABLE_SERIAL 1

#define API_VERSION   1 // software version of this library
#define OPENDEVICE_LIBRARY_VERSION 050


#define DEFAULT_BAUD 115200
#define DEFAULT_SERVER_PORT 8182
#define DISCOVERY_PORT 6142
#define KEEP_ALIVE_INTERVAL 30000
#define KEEP_ALIVE_MAX_MISSING 3
#define ENABLE_DEVICE_INTERRUPTION 0
#define ENABLE_REMOTE_WIFI_SETUP 0   // disable to reduce flash usage
#define ENABLE_SSL 0 // disable to reduce flash/memory usage (tested only for MQTT/ESP8266)

#ifndef ENABLE_DHCP
#define ENABLE_DHCP 1  /* if you need save flash memory disable this
                          Another important config to save flash memory is disable UDP of UIPEthernet (UIPEthernet/utility/uipethernet-conf.h) */
#endif


#if defined(ESP8266)
	#define DEFAULT_BAUD 115200
#endif

#if defined(__AVR_ATtinyX313__) || defined(__AVR_ATtinyX4__) || defined(__AVR_ATtinyX5__)
#define DATA_BUFFER  16
#define MAX_LISTENERS 2
#define MAX_DEVICE 5
#define MAX_COMMAND 5 // this is used for user command callbacks
#define MAX_COMMAND_STRLEN 5
#define READING_INTERVAL 100 // sensor reading interval (ms)
#else
#define DATA_BUFFER  160
#define MAX_LISTENERS 10
#define MAX_DEVICE 10
#define MAX_COMMAND 10 // this is used for user command callbacks
#define MAX_COMMAND_STRLEN 14
#define READING_INTERVAL 100 // sensor reading interval (ms)
#endif


// May be better use: https://github.com/mrRobot62/Arduino-logging-library OU -VDEBUG(see ESP8266)
enum DebugTarget{
	DEBUG_SERIAL,
	DEBUG_CURRENT
};

enum ConnectionMode{
	CONNECTION_MODE_CLIENT,
	CONNECTION_MODE_SERVER
};

namespace od {


// DYNAMIC CONFIGURATION
	// =====================================

	typedef struct{
		bool saved =  false;
		char * moduleName = "OpenDevice";
		char * server = "api.opendevice.io";
		char * appID = "*";
		uint8_t id[6] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }; // MAC
		uint8_t ip[4] = { 0, 0, 0, 0 };
		uint8_t devicesLength = 0;
		int devicesStart = 0;
		int devicesEnd = 0;
		uint8_t pinReset = 2;
		bool debugMode = false;
		bool keepAlive = true;
		uint8_t debugTarget = DEBUG_SERIAL;
		ConnectionMode connectionMode = CONNECTION_MODE_SERVER;

		void load(){
			#if defined(ESP8266)
				EEPROM.begin(4096);
			#else
				EEPROM.begin(EEPROM.length());
			#endif

			// TODO: change to get and pt;
			#if defined(__COMPILING_AVR_LIBC__)
			eeprom_read_block((void*)this, (void*)0, sizeof(this));
			#endif
		}

		void save(){
			#if defined(__COMPILING_AVR_LIBC__)
			saved = true;
			eeprom_write_block((void*)this, (void*)0, sizeof(this));
			#endif
		}

	} ConfigClass;

	extern ConfigClass Config;

	static void loadConfig(){
		#if defined(__COMPILING_AVR_LIBC__)
		eeprom_read_block((void*)&Config, (void*)0, sizeof(Config));
		#endif
	}
	static void saveConfig(){
		Config.saved = true;
		#if defined(__COMPILING_AVR_LIBC__)
		eeprom_write_block((void*)&Config, (void*)0, sizeof(Config));
		#endif
	}
}


#endif /* OPENDEVICE_CONFIG_H_ */
