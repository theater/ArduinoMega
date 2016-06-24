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
#include "RoomManager.h"

HeatingAdapter::HeatingAdapter(RoomManager* roomManager, PubSubClient* mqttClient, bool DEBUG) {
	this->DEBUG = DEBUG;
	setMqttClient(mqttClient);
	if(DEBUG) {
		mqttClient->publish("DEBUG","HeatingAdapter::HeatingAdapter");
	}
	this->roomManager = roomManager;
	rooms = roomManager->getRooms();
}

HeatingAdapter::~HeatingAdapter() {
}

void HeatingAdapter::mqttSubscribe() {
//	for(int i=0; i<10 ; i++) {
//		if(rooms[i]) {
//			rooms[i]->subscribeMqttTopics(mqttClient);
//		}
//	}
	rooms[KIDS_BEDROOM]->subscribeMqttTopics(mqttClient);
}

void HeatingAdapter::mqttReceive(const char* topic, const char* payload) {
//	for (int i = 0; i < 10; i++) {
//		if (rooms[i] != NULL && rooms[i]->containsTopic(topic)) {
//			rooms[i]->mqttReceive(topic, payload);
//		}
//	}
	rooms[KIDS_BEDROOM]->mqttReceive(topic, payload);
}

void HeatingAdapter::sensorUpdate(const char* sensor, short value) {
	if (!strcmp(sensor, SENSOR_KIDS_01)) {
		rooms[KIDS_BEDROOM]->updateTempSensor(value);
		return;
	} else if (!strcmp(sensor, SENSOR_KIDS_02)) {
		rooms[KIDS_BEDROOM]->updateHumSensor(value);
		return;
	}
}

// Getters/setters

PubSubClient* HeatingAdapter::getMqttClient() const {
	return mqttClient;
}

void HeatingAdapter::setMqttClient(PubSubClient* mqttClient) {
	this->mqttClient = mqttClient;
}

