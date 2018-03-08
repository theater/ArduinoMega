/*
 * Config.h
 *
 *  Created on: 22.06.2016 ã.
 *      Author: theater
 */

#ifndef ROOM_CONFIG_H_
#define ROOM_CONFIG_H_

// DEBUG
const bool DEBUG = false;

// DEFAULT VALUES
#define DEFAULT_DESIRED_TEMP 		25
#define DEFAULT_DESIRED_HUMIDITY 	65

//MQTT initialization
#define MQTT_SERVER 192,168,254,40
#define MQTT_CLIENT_NAME "HeatingControl-FL2"
#define MQTT_USER "user"
#define MQTT_PASSWORD "mqttPass"

// Ethernet settings
#define MAC_ADDRESS {0x00,0x01,0x02,0x03,0x04,0x37}
#define IP_ADDRESS 192,168,254,37


// Aliases
#define ON true						// boolean alias for ON
#define OFF false  					// boolean alias for OFF

#define FAST true					// boolean alias for fan speed pin - fast
#define SLOW false					// boolean alias for fan speed pin - slow

#endif /* ROOM_CONFIG_H_ */
