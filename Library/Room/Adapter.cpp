/*
 * HeatingAdapter.cpp
 *
 *  Created on: 23.06.2016 ã.
 *      Author: theater
 */

#include "Adapter.h"

Adapter::Adapter(Manager* manager, PubSubClient* mqttClient, bool DEBUG) {
	this->DEBUG = DEBUG;
	this->mqttClient = mqttClient;
	if (DEBUG) {
		mqttClient->publish("DEBUG", "HeatingAdapter::HeatingAdapter");
	}
	this->manager = manager;
	rooms = manager->getRooms();
	count = manager->getCount();
}

Adapter::~Adapter() {
	// TODO Auto-generated destructor stub
}

void Adapter::mqttSubscribe() {
	for (int i = 0; i < count; i++) {
		if (rooms[i]) {
			rooms[i]->subscribeMqttTopics(mqttClient);
		}
	}
}

void Adapter::mqttReceive(const char* topic, const char* payload) {
	for (int i = 0; i < count; i++) {
		if (rooms[i] != NULL && rooms[i]->containsTopic(topic)) {
			rooms[i]->mqttReceive(topic, payload);
		}
	}
}

void Adapter::sensorUpdate(const char* sensor, float value) {
	manager->sensorsUpdate(sensor, value);
}
