/*
 * mqtt.cpp
 *
 *  Created on: 12.06.2016 ã.
 *      Author: theater
 */

#include <Config.h>
#include <Manager.h>
#include <MqttUtil.h>
#include <PubSubClient.h>
#include <stddef.h>
#include <WString.h>

Manager* manager;

bool MqttUtil::mqttConnect(PubSubClient* const mqttClient, Manager* const roomManager) {
	if (manager != roomManager) {
		manager = roomManager;
	}
	if (!mqttClient->connected()) {
		if (mqttClient->connect(MQTT_CLIENT_NAME, MQTT_USER, MQTT_PASSWORD)) {
			String str = MQTT_CLIENT_NAME;
			mqttClient->publish(MQTT_CLIENT_NAME, MQTT_CLIENT_NAME);
			if (manager != NULL) {
				manager->mqttSubscribe();
			}
			return true;
		} else {
			return false;
		}
	} else
		return true;
}

void MqttUtil::mqttPublish(PubSubClient* mqttClient, const char* topic, const char* value) {
	mqttClient->publish(topic, value);
}

void MqttUtil::mqttCallback(char* topic, byte* payload, unsigned int length) {
	char cPayload[10];
	for (int i = 0; i <= length; i++) {
		cPayload[i] = (char) payload[i];
	}
	cPayload[length] = '\0';
	mqttSendUpdatedData(topic, cPayload);
}

void MqttUtil::mqttSendUpdatedData(char* topic, char* payload) {
	manager->mqttReceive(topic, payload);
}
