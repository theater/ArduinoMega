/*
 * mqtt.h
 *
 *  Created on: 12.06.2016 ã.
 *      Author: theater
 */

#ifndef UTIL_MQTT_H_
#define UTIL_MQTT_H_

#include <Arduino.h>

class Manager;
class PubSubClient;


class MqttUtil {
public:
	static bool mqttConnect(PubSubClient* const mqttClient, Manager* const inputAdapter);
	static void mqttPublish(PubSubClient* mqttClient, const char* topic, const char* value);
	static void mqttCallback(char* topic, byte* payload, unsigned int length);
	static void mqttSendUpdatedData(char* topic, char* payload);
};

#endif /* UTIL_MQTT_H_ */
