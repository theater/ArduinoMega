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
#include <UIPClient.h>
#include "../Config/Config.h"

HeatingAdapter::HeatingAdapter(PubSubClient* mqttClient, bool DEBUG) {
	this->DEBUG = DEBUG;
	setMqttClient(mqttClient);
	bedRoomKids = new BedRoomKids(mqttClient, this->DEBUG);
	if(DEBUG) {
//		Serial.println("Calling HeatingAdapter constructor");
		mqttClient->publish("DEBUG","HeatingAdapter::HeatingAdapter");
	}
}

HeatingAdapter::~HeatingAdapter() {
	delete bedRoomKids;
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

void HeatingAdapter::mqttReceive(const char* topic, const char* payload) {
	if(!strcmp(topic, RAD_KIDS_01)||!strcmp(topic, RAD_KIDS_02)) {
		bedRoomKids->mqttReceive(topic, payload);
	}
}

void HeatingAdapter::sensorUpdate(const char* sensor, short value) {
	if (!strcmp(sensor, SENSOR_KIDS_01)) {
		bedRoomKids->updateTempSensor(value);
		return;
	}
}

void HeatingAdapter::updateRoomDesiredValue(const char* room, ControlType type, short value) {
	switch (type) {
		case TEMPERATURE:
			updateDesiredTemperature(room, value);
			break;
		case HUMIDITY:
			updateDesiredHumidity(room, value);
			break;
		default:
			break;
	}
}

void HeatingAdapter::updateDesiredTemperature(const char* room, short value) {
	if (DEBUG) mqttClient->publish("DEBUG", "HeatingAdapter::updateDesiredTemperature");

	if (!strcmp(room, KIDS_BEDROOM)) {
		bedRoomKids->updateDesiredTemperature(value);
		if (DEBUG) mqttClient->publish("DEBUG", "Updated desired temperatures");
	}

	if (DEBUG) mqttClient->publish("DEBUG", "No matching rule.(HeatingAdapter::updateDesiredTemperature)");
}

void HeatingAdapter::updateDesiredHumidity(const char* room, short value) {
	if (!strcmp(room, KIDS_BEDROOM)) {
		bedRoomKids->updateDesiredHumidity(value);
	}
}

// Getters/setters

BedRoomKids* HeatingAdapter::getBedRoomKids() const {
	return bedRoomKids;
}

void HeatingAdapter::setBedRoomKids(BedRoomKids* bedRoomKids) {
	this->bedRoomKids = bedRoomKids;
}

PubSubClient* HeatingAdapter::getMqttClient() const {
	return mqttClient;
}

void HeatingAdapter::setMqttClient(PubSubClient* mqttClient) {
	this->mqttClient = mqttClient;
}

