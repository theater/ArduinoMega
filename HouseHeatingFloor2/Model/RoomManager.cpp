/*
 * RoomManager.cpp
 *
 *  Created on: 24.06.2016 ã.
 *      Author: theater
 */

#include "RoomManager.h"

#include <stdbool.h>
#include <string.h>
#include <Util.h>

#include "../Config/Config.h"

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
	for (int i = 0; i < count; i++) {
		Room** room = getRooms();
		delete room[i];
	}
}

Room* RoomManager::createRoom(RoomId id, bool DEBUG) {
	if (rooms[id] == NULL) {
		switch (id) {
		case KIDS_BEDROOM:
			rooms[id] = new BedRoomKids(mqttClient, DEBUG);
			break;
		case CORRIDOR:
			rooms[id] = new Corridor(mqttClient, DEBUG);
			break;
		case BIG_BATHROOM:
			rooms[id] = new BigBathroom(mqttClient, DEBUG);
			break;
		case MASTER_BEDROOM:
			rooms[id] = new MasterBedroom(mqttClient, DEBUG);
			break;
		case WARDROBE:
			rooms[id] = new Wardrobe(mqttClient, DEBUG);
			break;
		case BEDROOM_BATH:
			rooms[id] = new BedroomBath(mqttClient, DEBUG);
			break;
		default:
			break;
		}
	}
	return rooms[id];
}
void RoomManager::sensorUpdate(const char* sensor, float value) {
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
	} else if (!strcmp(sensor, SENSOR_MASTER_BEDROOM_01)) {
		rooms[MASTER_BEDROOM]->updateTempSensor(value);
		return;
	} else if (!strcmp(sensor, SENSOR_WARDROBE_01)) {
		rooms[WARDROBE]->updateTempSensor(value);
		return;
	} else if (!strcmp(sensor, SENSOR_BEDROOM_BATH_01)) {
		rooms[BEDROOM_BATH]->updateTempSensor(value);
		return;
	}  else if (!strcmp(sensor, SENSOR_BEDROOM_BATH_02)) {
		rooms[BEDROOM_BATH]->updateHumSensor(value);
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
