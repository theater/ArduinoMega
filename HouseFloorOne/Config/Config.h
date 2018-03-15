/*
 * Config.h
 *
 *  Created on: 11.06.2016 ã.
 *      Author: theater
 */

#ifndef CONFIG_H_
#define CONFIG_H_

// SERIAL SETTINGS
#define BAUD_RATE 115200

// IP Address
// Ethernet settings
#define MAC_ADDRESS {0x00,0x01,0x02,0x03,0x04,0x37}
#define IP_ADDRESS 192,168,254,37

// DEFAULT VALUES
#define DEFAULT_DESIRED_TEMP 			25
#define DEFAULT_DESIRED_HUMIDITY 		65
#define REOCCURRENCE 					30000  		// Decision maker triggered on every xxxxx ms

// PIN assignments
#define DHT_BIG_BATH					8
#define ONE_WIRE_PIN_01 				7

// 	MQTT topics
// Modes
#define MODE_LR							"home/floor1/livingRoom/mode/1"

//	Radiators (outputs)
#define RAD_KIDS_01						"home/floor2/kids/radiator/1"
#define RAD_KIDS_01_CB					"home/floor2/kids/radiator/1cb"

// Temperature sensors
#define SENSOR_LR_01					"home/floor1/livingRoom/temperature/1"
#define SENSOR_LR_02					"home/floor1/livingRoom/temperature/2"

#define DESIRED_TEMP_KIDS_01			"home/floor2/kids/desired/temperature/1"

const DS18B20ConfigDefinition oneWireSensors[] = {
		{ {0x28, 0xff, 0x3e, 0x53, 0x4e, 0x4, 0x0, 0xc0}, SENSOR_LR_01 },
		{ {0x28, 0xff, 0x98, 0x69, 0x4c, 0x4, 0x0, 0x73}, SENSOR_LR_02 }
};

// Aliases
#define ON true						// boolean alias for ON
#define OFF false  					// boolean alias for OFF

#define FAST true					// boolean alias for fan speed pin - fast
#define SLOW false					// boolean alias for fan speed pin - slow

#endif /* CONFIG_H_ */

