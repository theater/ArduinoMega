// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _HouseFloorOne_H_
#define _HouseFloorOne_H_
//add your includes for the project HouseFloorOne here
#include "Arduino.h"
#include <ethernet_comp.h>
#include <HardwareSerial.h>
#include <IPAddress.h>
#include "MqttUtil.h"
#include <OneWire.h>
#include <PubSubClient.h>
#include <stddef.h>
#include <stdint.h>
#include <UIPClient.h>
#include <UIPEthernet.h>
#include <Util.h>
#include "Config/Config.h"


//end of add your includes here


//add your function definitions for the project HouseFloorOne here

void mqttCallback(const char* topic, uint8_t* payload, unsigned int length);
void sensorsUpdate();
void reconnect();
void freeMemoryToMQTT();

//Do not add code below this line
#endif /* _HouseFloorOne_H_ */
