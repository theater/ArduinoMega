/*
 * Config.h
 *
 *  Created on: 22.06.2016 ã.
 *      Author: theater
 */

#ifndef ROOM_CONFIG_H_
#define ROOM_CONFIG_H_

#include "Restricted.h"


// DEFAULT VALUES
#define DEFAULT_DESIRED_TEMP 		25
#define DEFAULT_DESIRED_HUMIDITY 	65

//MQTT initializa
#define MQTT_SERVER {192,168,254,30}
#define MQTT_CLIENT_NAME "HeatingControl-FL2"   // CHANGE THIS ! ! !

// Aliases
#define ON true						// boolean alias for ON
#define OFF false  					// boolean alias for OFF



#endif /* ROOM_CONFIG_H_ */
