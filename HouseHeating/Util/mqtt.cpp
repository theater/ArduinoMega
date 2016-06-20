/*
 * mqtt.cpp
 *
 *  Created on: 12.06.2016 ã.
 *      Author: theater
 */

#include "mqtt.h"

#include <Arduino.h>
#include <PubSubClient.h>
#include <stdbool.h>
#include <WString.h>

#include "../Config/Config.h"
#include "../Model/HeatingAdapter.h"

HeatingAdapter* adapter;
bool mqttConnect(PubSubClient* const mqttClient, HeatingAdapter* const inputAdapter) {
	if (adapter != inputAdapter) {
		adapter = inputAdapter;
	}
	if (!mqttClient->connected()) {
		if (mqttClient->connect(MQTT_CLIENT_NAME, MQTT_USER, MQTT_PASSWORD)) {
			String str = MQTT_CLIENT_NAME;
			mqttClient->publish(MQTT_CLIENT_NAME, MQTT_CLIENT_NAME);
			if (inputAdapter != NULL) {
				mqttSubscribe(mqttClient, inputAdapter);
			}
			return true;
		} else {
			return false;
		}
	} else
		return true;
}

void mqttSubscribe(PubSubClient* const mqttClient, HeatingAdapter* const inputAdapter) {
	inputAdapter->mqttSubscribe(mqttClient);
}

void mqttPublish(PubSubClient* mqttClient, const char* topic, const char* value) {
	mqttClient->publish(topic, value);
}

void mqttCallback(char* topic, byte* payload, unsigned int length) {
	char cPayload[10];
	for (int i = 0; i <= length; i++) {
		cPayload[i] = (char) payload[i];
	}
	cPayload[length] = '\0';
//	String strPayload = String(cPayload);
//	String strTopic = String(topic);
	mqttSendUpdatedData(topic, cPayload);
}

void mqttSendUpdatedData(char* topic, char* payload) {
	adapter->mqttReceive(topic, payload);
}
