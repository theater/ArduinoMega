/*
 * RoomManager.cpp
 *
 *  Created on: 24.06.2016 ã.
 *      Author: theater
 */

#include "RoomManager.h"

RoomManager::RoomManager(PubSubClient* mqttClient) : Manager(mqttClient){
	this->mqttClient = mqttClient;
}

RoomManager* RoomManager::getInstance(PubSubClient* mqttClient) {
	if(manager == NULL) {
		manager = new RoomManager(mqttClient);
	}
	return manager;
}

RoomManager::~RoomManager() {
}

Room* RoomManager::createRoom(RoomId id) {
	if (rooms[id] == NULL) {
		switch (id) {
		case KIDS_BEDROOM:
			rooms[id] = new BedRoomKids(mqttClient);
			break;
		case CORRIDOR:
			rooms[id] = new Corridor(mqttClient, true);
			break;
		default:
			break;
		}
	}
	return rooms[id];
}
void RoomManager::sensorsUpdate(const char* sensor, short value) {
	if (!strcmp(sensor, SENSOR_KIDS_01)) {
		rooms[KIDS_BEDROOM]->updateTempSensor(value);
		return;
	} else if (!strcmp(sensor, SENSOR_CORRIDOR_01)) {
		rooms[CORRIDOR]->updateTempSensor(value);
		return;
	}
}

// Getters and setters
PubSubClient* RoomManager::getMqttClient() {
	return mqttClient;
}

void RoomManager::setMqttClient(PubSubClient* mqttClient) {
	this->mqttClient = mqttClient;
}
