/*
 * Config.h
 *
 *  Created on: 11.06.2016 �.
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
#define MODE_KIDS						"home/floor2/kids/mode/1"
#define MODE_KIDS_CB					"home/floor2/kids/mode/1cb"

//	Radiators (outputs)
#define RAD_KIDS_01						"home/floor2/kids/radiator/1"
#define RAD_KIDS_01_CB					"home/floor2/kids/radiator/1cb"

// Temperature sensors
#define SENSOR_LR_01					"home/floor1/livingRoom/temperature/1"

#define DESIRED_TEMP_KIDS_01			"home/floor2/kids/desired/temperature/1"


// Aliases
#define ON true						// boolean alias for ON
#define OFF false  					// boolean alias for OFF

#define FAST true					// boolean alias for fan speed pin - fast
#define SLOW false					// boolean alias for fan speed pin - slow

#endif /* CONFIG_H_ */


