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

HeatingAdapter::HeatingAdapter(PubSubClient* mqttClient) {
	setMqttClient(mqttClient);
	bedRoomKids = new BedRoomKids(this->mqttClient);
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

void HeatingAdapter::mqttReceive(char* topic, char* payload) {
	if(strcmp(topic, SENSOR_KIDS_01)) {
		bedRoomKids->updateTempSensor(atoi(payload));
	}
}

void HeatingAdapter::sensorUpdate(const char* sensor, short value) {
	if (strcmp(sensor, SENSOR_KIDS_01)) {
		bedRoomKids->updateTempSensor(value);
		return;
	}
}

void HeatingAdapter::updateRoomDesiredValue(const char* room, ControlType type, short value) {
	switch (type) {
		case TEMPERATURE:
			if (DEBUG) Serial.println("Updating temperature");
			updateDesiredTemperature(room, value);
			break;
		case HUMIDITY:
			if (DEBUG) Serial.println("Updating humidity");
			updateDesiredHumidity(room, value);
			break;
		default:
			if (DEBUG) Serial.println("DEFAULT returning");
			break;
	}
}

void HeatingAdapter::updateDesiredTemperature(const char* room, short value) {
	if (!strcmp(room, KIDS_BEDROOM)) {
		if (DEBUG) Serial.println("Update desired temperature");
		bedRoomKids->updateDesiredTemperature(value);
	}
	if (DEBUG) Serial.println("No matching rule.(HeatingAdapter::updateDesiredTemperature)");
}

void HeatingAdapter::updateDesiredHumidity(const char* room, short value) {
	if (!strcmp(room, KIDS_BEDROOM)) {
		if (DEBUG) Serial.println("Update desired temperature");
		bedRoomKids->updateDesiredHumidity(value);
	}
	if (DEBUG) Serial.println("No matching rule.(HeatingAdapter::updateDesiredTemperature)");
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

