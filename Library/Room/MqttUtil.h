/*
 * mqtt.h
 *
 *  Created on: 12.06.2016 ã.
 *      Author: theater
 */

#ifndef UTIL_MQTT_H_
#define UTIL_MQTT_H_

#include <stdbool.h>
#include <PubSubClient.h>

#include "C:/eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.5/cores/arduino/Arduino.h"
#include "C:/eclipse/arduinoPlugin/tools/arduino/avr-gcc/4.8.1-arduino5/lib/gcc/avr/4.8.1/include/stdbool.h"
#include "Adapter.h"


class MqttUtil {
public:
	static bool mqttConnect(PubSubClient* const mqttClient, Adapter* const inputAdapter);
	static void mqttSubscribe(Adapter* const inputAdapter);
	static void mqttPublish(PubSubClient* mqttClient, const char* topic, const char* value);
	static void mqttCallback(char* topic, byte* payload, unsigned int length);
	static void mqttSendUpdatedData(char* topic, char* payload);
};

#endif /* UTIL_MQTT_H_ */
