/*
 * HeatingAdapter.cpp
 *
 *  Created on: 13.06.2016 ã.
 *      Author: theater
 */

#include "HeatingAdapter.h"

#include <Arduino.h>
#include <string.h>
#include <WString.h>
//#include "../Config/Config.h"

HeatingAdapter::HeatingAdapter(PubSubClient* mqttClient, bool DEBUG) {
	this->DEBUG = DEBUG;
	setMqttClient(mqttClient);
	if(DEBUG) {
//		Serial.println("Calling HeatingAdapter constructor");
		mqttClient->publish("DEBUG","HeatingAdapter::HeatingAdapter");
	}
}

HeatingAdapter::~HeatingAdapter() {
}

void HeatingAdapter::mqttCallback(char* topic, byte* payload, unsigned int length) {
	char cPayload[10];
	for (int i = 0; i <= length; i++) {
		cPayload[i] = (char) payload[i];
	}
	cPayload[length] = '\0';
	String strPayload = String(cPayload);
	String strTopic = String(topic);
	mqttReceive(topic, cPayload);
}

void HeatingAdapter::mqttSubscribe(PubSubClient* mqttClient) {
}

void HeatingAdapter::mqttReceive(const char* topic, const char* payload) {
}

void HeatingAdapter::sensorUpdate(const char* sensor, short value) {
//	example:
//	if (!strcmp(sensor, SENSOR_KIDS_01)) {
//		bedRoomKids->updateTempSensor(value);
//		return;
//	} else if (!strcmp(sensor, SENSOR_KIDS_02)) {
//		bedRoomKids->updateHumSensor(value);
//		return;
//	}
}

void HeatingAdapter::updateRoomDesiredValue(const char* room, ControlType type, short value) {
	//example:
//	switch (type) {
//		case TEMPERATURE:
//			updateDesiredTemperature(room, value);
//			break;
//		case HUMIDITY:
//			updateDesiredHumidity(room, value);
//			break;
//		default:
//			break;
//	}
}

void HeatingAdapter::updateDesiredTemperature(const char* room, short value) {
//	if (!strcmp(room, KIDS_BEDROOM)) {
//		bedRoomKids->updateDesiredTemperature(value);
//		if (DEBUG) mqttClient->publish("DEBUG", "Updated desired temperatures");
//	}
//
//	if (DEBUG) mqttClient->publish("DEBUG", "No matching rule.(HeatingAdapter::updateDesiredTemperature)");
}

void HeatingAdapter::updateDesiredHumidity(const char* room, short value) {
//	if (!strcmp(room, KIDS_BEDROOM)) {
//		bedRoomKids->updateDesiredHumidity(value);
//	}
}

// Getters/setters

PubSubClient* HeatingAdapter::getMqttClient() const {
	return mqttClient;
}

void HeatingAdapter::setMqttClient(PubSubClient* mqttClient) {
	this->mqttClient = mqttClient;
}

