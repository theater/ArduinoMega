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

// NETWORK SETTINGS
// MQTT stuff
#define MQTT_SERVER {192,168,254,40}
#define MQTT_CLIENT_NAME "HeatingControl-FL2"

// Ethernet settings
#define MAC_ADDRESS {0x00,0x01,0x02,0x03,0x04,0x37}
#define IP_ADDRESS 192,168,254,37

// DEFAULT VALUES
#define DEFAULT_DESIRED_TEMP 			25
#define DEFAULT_DESIRED_HUMIDITY 		65
#define REOCCURRENCE 					30000  		// Decision maker triggered on every xxxxx ms

// PIN assignments
#define DHT_BIG_BATH					8
#define ONE_WIRE_PIN_01 				9
#define DHT_BEDROOM_BATH				10
#define KIDS_BEDROOM_RAD_ONE 			30   			// KIDS RADIATOR ONE IS ON PIN 30
#define KIDS_BEDROOM_RAD_TWO 			31  			// KIDS RADIATOR TWO IS ON PIN 31
#define CORRIDOR_RAD_ONE 				32				// CORRIDOR RADIATOR ONE IS ON PIN 32
#define CORRIDOR_RAD_TWO 				33				// CORRIDOR RADIATOR TWO IS ON PIN 33
#define BIG_BATH_RAD_ONE 				34				// Big bathroom radiator one  - pin 34
#define BIG_BATH_RAD_TWO 				35				// Big bathroom radiator two  - pin 35
#define BIG_BATH_FAN_SWITCH				45				// Big bathroom fan  - pin 43
#define BIG_BATH_FAN_SPEED				46				// Big bathroom fan  - pin 43
#define MASTER_BEDROOM_RAD 				36				// Our bedroom radiator - pin 36
#define WARDROBE_RAD 					37				// Wardrobe room radiator - pin 37
#define BEDROOM_BATH_RAD				40				// Small bathroom next to our bedroom radiator - pin 40
#define BEDROOM_FAN_SWITCH				41				// Small bathroom next to our bedroom fan-on off switch pin 41
#define BEDROOM_FAN_SPEED				43				// Small bathroom next to our bedroom fan-speed control pin 43
#define FAN_PIN							42				// Just to test fan logic

// 	MQTT topics
// Modes
#define MODE_KIDS						"home/floor2/kids/mode/1"
#define MODE_KIDS_CB					"home/floor2/kids/mode/1cb"
#define MODE_CORRIDOR					"home/floor2/corridor/mode/1"
#define MODE_CORRIDOR_CB				"home/floor2/corridor/mode/1cb"
#define MODE_BIGBATH					"home/floor2/bigbath/mode/1"
#define MODE_BIGBATH_CB					"home/floor2/bigbath/mode/1cb"
#define MODE_MASTER_BEDROOM				"home/floor2/bedroom/mode/1"
#define MODE_MASTER_BEDROOM_CB			"home/floor2/bedroom/mode/1cb"
#define MODE_WARDROBE					"home/floor2/wardrobe/mode/1"
#define MODE_WARDROBE_CB				"home/floor2/wardrobe/mode/1cb"
#define MODE_BEDROOM_BATH				"home/floor2/bedroombath/mode/1"
#define MODE_BEDROOM_BATH_CB			"home/floor2/bedroombath/mode/1cb"

//	Radiators (outputs)
#define RAD_KIDS_01						"home/floor2/kids/radiator/1"
#define RAD_KIDS_01_CB					"home/floor2/kids/radiator/1cb"
#define RAD_KIDS_02						"home/floor2/kids/radiator/2"
#define RAD_KIDS_02_CB					"home/floor2/kids/radiator/2cb"
#define RAD_CORRIDOR_01 				"home/floor2/corridor/radiator/1"
#define RAD_CORRIDOR_01_CB 				"home/floor2/corridor/radiator/1cb"
#define RAD_CORRIDOR_02 				"home/floor2/corridor/radiator/2"
#define RAD_CORRIDOR_02_CB 				"home/floor2/corridor/radiator/2cb"
#define RAD_BIGBATH_01					"home/floor2/bigbath/radiator/1"
#define RAD_BIGBATH_01_CB				"home/floor2/bigbath/radiator/1cb"
#define RAD_BIGBATH_02					"home/floor2/bigbath/radiator/2"
#define RAD_BIGBATH_02_CB				"home/floor2/bigbath/radiator/2cb"
#define RAD_MASTER_BEDROOM				"home/floor2/masterbedroom/radiator/1"
#define RAD_MASTER_BEDROOM_CB			"home/floor2/masterbedroom/radiator/1cb"
#define RAD_WARDROBE					"home/floor2/wardrobe/radiator/1"
#define RAD_WARDROBE_CB					"home/floor2/wardrobe/radiator/1cb"
#define RAD_BEDROOM_BATH				"home/floor2/bedroombath/radiator/1"
#define RAD_BEDROOM_BATH_CB				"home/floor2/bedroombath/radiator/1cb"
#define FAN_SWITCH_BIGBATH				"home/floor2/bigbath/fan/1"
#define FAN_SWITCH_BIGBATH_CB			"home/floor2/bigbath/fan/1cb"
#define FAN_SPEED_BIGBATH				"home/floor2/bigbath/fan/1/speed"
#define FAN_SPEED_BIGBATH_CB			"home/floor2/bigbath/fan/1/speed/cb"
#define FAN_SWITCH_BEDROOM_BATH			"home/floor2/bedroombath/fan/1"
#define FAN_SWITCH_BEDROOM_BATH_CB		"home/floor2/bedroombath/fan/1/cb"
#define FAN_SPEED_BEDROOM_BATH			"home/floor2/bedroombath/fan/1/speed"
#define FAN_SPEED_BEDROOM_BATH_CB		"home/floor2/bedroombath/fan/1/speed/cb"

// Temperature sensors
#define SENSOR_KIDS_01					"home/floor2/kids/temperature/1"
#define SENSOR_CORRIDOR_01				"home/floor2/corridor/temperature/1"
#define SENSOR_BIGBATH_01				"home/floor2/bigbath/temperature/1"
#define SENSOR_MASTER_BEDROOM_01		"home/floor2/masterbedroom/temperature/1"
#define SENSOR_WARDROBE_01				"home/floor2/wardrobe/temperature/1"
#define SENSOR_BEDROOM_BATH_01			"home/floor2/bedroombath/temperature/1"

// Humidity sensors
//#define SENSOR_BIGBATH_02				"home/floor2/big"
#define SENSOR_BIGBATH_02				"home/floor2/bigbath/humidity/1"
#define SENSOR_BEDROOM_BATH_02			"home/floor2/bedroombath/humidity/1"

// Setters / desired values
#define DESIRED_TEMP_KIDS_01			"home/floor2/kids/desired/temperature/1"
#define DESIRED_TEMP_CORRIDOR_01		"home/floor2/corridor/desired/temperature/1"
#define DESIRED_TEMP_BIGBATH_01			"home/floor2/bigbath/desired/temperature/1"
#define DESIRED_TEMP_MASTER_BEDROOM_01	"home/floor2/masterbedroom/desired/temperature/1"
#define DESIRED_TEMP_WARDROBE_01		"home/floor2/wardrobe/desired/temperature/1"
#define DESIRED_TEMP_BEDROOM_BATH_01	"home/floor2/bedroombath/desired/temperature/1"
#define DESIRED_HUM_BIGBATH_01			"home/floor2/bigbath/desired/humidity/1"
#define DESIRED_HUM_BEDROOM_BATH_01		"home/floor2/bedroombath/desired/humidity/1"


// Aliases
#define ON true						// boolean alias for ON
#define OFF false  					// boolean alias for OFF

#define FAST true					// boolean alias for fan speed pin - fast
#define SLOW false					// boolean alias for fan speed pin - slow

#endif /* CONFIG_H_ */



