/*
 * Manager.cpp
 *
 *  Created on: 26.06.2016 ã.
 *      Author: theater
 */
#include "Manager.h"

Manager::~Manager() {
	// TODO Auto-generated destructor stub
}

Manager::Manager(PubSubClient* mqttClient) {
	this->mqttClient = mqttClient;
	for(int i=0; i<10; i++) {
		rooms[i] = NULL;
	}
}

Room* Manager::getRoom(RoomId id) {
	return rooms[id];
}

PubSubClient* Manager::getMqttClient() {
	return mqttClient;
}

void Manager::setMqttClient(PubSubClient* mqttClient) {
	this->mqttClient = mqttClient;
}

Room** Manager::getRooms(){
	return rooms;
}

const int Manager::getCount() {
	return count;
}
