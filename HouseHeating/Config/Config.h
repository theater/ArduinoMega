/*
 * Config.h
 *
 *  Created on: 11.06.2016 ã.
 *      Author: theater
 */

#ifndef CONFIG_H_
#define CONFIG_H_
#include "Restricted.h"

// DEBUG
const bool DEBUG = true;

// NETWORK SETTINGS
// MQTT stuff
#define MQTT_SERVER {192,168,254,30}
#define MQTT_CLIENT_NAME "HeatingControl-FL2"

// Ethernet settings
#define MAC_ADDRESS {0x00,0x01,0x02,0x03,0x04,0x37}
#define IP_ADDRESS 192,168,254,37

// DEFAULT VALUES
#define DEFAULT_DESIRED_TEMP 	25
#define DEFAULT_DESIRED_HUMIDITY 65
#define REOCCURRENCE 			30000  		// Decision maker triggered on every xxxxx ms

// ROOMS
#define KIDS_BEDROOM "Kids bedroom"
#define OUR_BEDROOM "Our bedroom"
#define OUR_BATHROOM "Our bathroom"
#define CORRIDOR "Corridor"
#define WARDROBE "Wardrobe"
#define BIG_BATHROOM "Big bathroom"


// PIN assignments
#define DHT_PIN					8
#define ONE_WIRE_PIN_01 			9
#define KIDS_BEDROOM_RAD_ONE 	30   			// KIDS RADIATOR ONE IS ON PIN 30
#define KIDS_BEDROOM_RAD_TWO 	31  			// KIDS RADIATOR TWO IS ON PIN 31
#define CORRIDOR_RAD_ONE 		32				// CORRIDOR RADIATOR ONE IS ON PIN 32
#define CORRIDOR_RAD_TWO 		33				// CORRIDOR RADIATOR TWO IS ON PIN 33
#define BIG_BATH_RAD_ONE 		34				// Big bathroom radiator one  - pin 34
#define BIG_BATH_RAD_TWO 		35				// Big bathroom radiator two  - pin 35
#define OUR_BEDROOM_RAD 		36				// Our bedroom radiator - pin 36
#define WARDROBE_RAD 			37				// Wardrobe room radiator - pin 37
#define SMALL_BATH_RAD 			40				// Small bathroom next to our bedroom - pin 40


// 	MQTT topics
//	Radiators (outputs)
#define RAD_KIDS_01					"home/floor2/kids/radiator/1"
#define RAD_KIDS_01_CB				"home/floor2/kids/radiator/1cb"
#define RAD_KIDS_02					"home/floor2/kids/radiator/2"
#define RAD_KIDS_02_CB				"home/floor2/kids/radiator/2cb"
#define RAD_CORRIDOR_01 			"home/floor2/corridor/radiator/1"
#define RAD_CORRIDOR_02 			"home/floor2/corridor/radiator/2"
#define RAD_BIGBATH_01				"home/floor2/bigbath/radiator/1"
#define RAD_BIGBATH_02				"home/floor2/bigbath/radiator/2"
#define RAD_BEDROOM					"home/floor2/bedroom/radiator/1"
#define RAD_WARDROBE				"home/floor2/wardrobe/radiator/1"
#define RAD_BEDROOM_BATH			"home/floor2/bedroombath/radiator/1"
// Temperature sensors
#define SENSOR_KIDS_01				"home/floor2/kids/temperature/1"
#define SENSOR_CORRIDOR_01			"home/floor2/corridor/temperature/1"
#define SENSOR_BIGBATH_01			"home/floor2/bigbath/temperature/1"
#define SENSOR_BEDROOM_01			"home/floor2/bedroom/temperature/1"
#define SENSOR_WARDROBE_01			"home/floor2/wardrobe/temperature/1"
#define SENSOR_BEDROOM_BATH_01		"home/floor2/bedroombath/temperature/1"
// Humidity sensors
#define SENSOR_BIGBATH_02			"home/floor2/bigbath/humidity/1"
#define SENSOR_BEDROOM_BATH_02		"home/floor2/bedroombath/humidity/1"
// Setters / desired values
#define DESIRED_KIDS_01				"home/floor2/kids/desired/temperature/1"


// Aliases
#define ON true						// boolean alias for ON
#define OFF false  					// boolean alias for OFF

#endif /* CONFIG_H_ */


