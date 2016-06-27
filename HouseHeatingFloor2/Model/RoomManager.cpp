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
			rooms[id] = new Corridor(mqttClient);
			break;
		case BIG_BATHROOM:
			rooms[id] = new BigBathroom(mqttClient);
			break;
		case MASTER_BEDROOM:
			rooms[id] = new MasterBedroom(mqttClient);
			break;
		case WARDROBE:
			rooms[id] = new Wardrobe(mqttClient);
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
	} else if (!strcmp(sensor, SENSOR_BIGBATH_01)) {
		rooms[BIG_BATHROOM]->updateTempSensor(value);
		return;
	} else if (!strcmp(sensor, SENSOR_BIGBATH_02)) {
		rooms[BIG_BATHROOM]->updateHumSensor(value);
		return;
	} else  if (!strcmp(sensor, SENSOR_MASTER_BEDROOM_01)) {
		rooms[MASTER_BEDROOM]->updateTempSensor(value);
		return;
	} else  if (!strcmp(sensor, SENSOR_WARDROBE_01)) {
		rooms[WARDROBE]->updateTempSensor(value);
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
