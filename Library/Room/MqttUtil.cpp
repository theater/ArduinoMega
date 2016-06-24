/*
 * mqtt.cpp
 *
 *  Created on: 12.06.2016 ã.
 *      Author: theater
 */

#include "MqttUtil.h"

#include <Arduino.h>
#include <PubSubClient.h>
#include <stdbool.h>
#include <WString.h>

#include "Adapter.h"
#include "Config.h"

Adapter* adapter;
bool MqttUtil::mqttConnect(PubSubClient* const mqttClient, Adapter* const inputAdapter) {
	if (adapter != inputAdapter) {
		adapter = inputAdapter;
	}
	if (!mqttClient->connected()) {
		if (mqttClient->connect(MQTT_CLIENT_NAME, MQTT_USER, MQTT_PASSWORD)) {
			String str = MQTT_CLIENT_NAME;
			mqttClient->publish(MQTT_CLIENT_NAME, MQTT_CLIENT_NAME);
			if (inputAdapter != NULL) {
				mqttSubscribe(inputAdapter);
			}
			return true;
		} else {
			return false;
		}
	} else
		return true;
}

void MqttUtil::mqttSubscribe(Adapter* const inputAdapter) {
	inputAdapter->mqttSubscribe();
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
	adapter->mqttReceive(topic, payload);
}
