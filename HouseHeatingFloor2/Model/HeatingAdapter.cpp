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

void HeatingAdapter::mqttSubscribe(PubSubClient* mqttClient) {
	bedRoomKids->subscribeMqttTopics(mqttClient);
}

void HeatingAdapter::mqttReceive(const char* topic, const char* payload) {
	if (bedRoomKids->containsTopic(topic)) {
		bedRoomKids->mqttReceive(topic, payload);
	}
}

void HeatingAdapter::sensorUpdate(const char* sensor, short value) {
	if (!strcmp(sensor, SENSOR_KIDS_01)) {
		bedRoomKids->updateTempSensor(value);
		return;
	} else if (!strcmp(sensor, SENSOR_KIDS_02)) {
		bedRoomKids->updateHumSensor(value);
		return;
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

