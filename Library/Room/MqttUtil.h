/*
 * mqtt.h
 *
 *  Created on: 12.06.2016 ã.
 *      Author: theater
 */

#ifndef UTIL_MQTT_H_
#define UTIL_MQTT_H_

#include <Arduino.h>
#include <Config.h>
#include <PubSubClient.h>
#include <UIPClient.h>
#include <UIPEthernet.h>

class MqttUtil {
public:
	static bool connect();
	static bool isConnected();
	static void publish(const char* topic, const char* value);
	static void subscribe(const char* topic);
	static void initializeMqttUtil(PubSubClient * client);
	static void loop();



private:
	static PubSubClient *mqttClient;
	static void (*callback)(const char*, uint8_t*, unsigned int);
};

#endif /* UTIL_MQTT_H_ */
