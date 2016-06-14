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
bool mqttConnect(PubSubClient* mqttClient, HeatingAdapter* inputAdapter) {
	if(adapter != inputAdapter) {
		adapter = inputAdapter;
	}
	if (!mqttClient->connected()) {
		if (mqttClient->connect("ArduinoNANO-AQ", "mqttuser", "MqTtUser")) {
			mqttClient->publish("Arduino", "Arduino-AQ is UP");
			mqttSubscribe(mqttClient);
//      Serial.write("Connected to MQTT\n");
			return true;
		} else {
//       Serial.write("Error connecting to MQTT\n");
			return false;
		}
	} else
		return true;
}

void mqttSubscribe(PubSubClient* mqttClient) {
	mqttClient->subscribe(RAD_KIDS_01);
	mqttClient->subscribe(RAD_KIDS_02);
	mqttClient->subscribe(RAD_CORRIDOR_01);
	mqttClient->subscribe(RAD_CORRIDOR_02);
	mqttClient->subscribe(RAD_BIGBATH_01);
	mqttClient->subscribe(RAD_BIGBATH_02);
	mqttClient->subscribe(RAD_BEDROOM);
	mqttClient->subscribe(RAD_WARDROBE);
	mqttClient->subscribe(RAD_BEDROOM_BATH);
}

void mqttPublish(PubSubClient* mqttClient, const char* topic, const char* value) {
	mqttClient->publish(topic, value);
}

void mqttCallback(char* topic, byte* payload, unsigned int length) {
  char cPayload[10];
  for (int i=0; i<=length; i++) {
    cPayload[i]=(char)payload[i];
  }
  cPayload[length]='\0';
  String strPayload = String(cPayload);
  String strTopic = String(topic);
  mqttSendUpdated(topic, cPayload);
}

void mqttSendUpdated(char* topic, char* payload) {
	adapter->mqttReceive(topic, payload);
}
