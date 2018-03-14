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

RoomManager::RoomManager() : Manager(){
}

RoomManager* RoomManager::getInstance() {
	if(manager == NULL) {
		manager = new RoomManager();
	}
	return manager;
}

RoomManager::~RoomManager() {
	for (int i = 0; i < roomCount; i++) {
		Room** room = getRooms();
		delete room[i];
	}
}

Room* RoomManager::addRoom(Room * room) {
	RoomId id = room->getId();
	rooms[id] = room;
	return rooms[id];
}

void RoomManager::createRooms() {
	createRoom(KIDS_BEDROOM, new BedRoomKids());
	createRoom(CORRIDOR, new Corridor());
	createRoom(BIG_BATHROOM, new BigBathroom());
	createRoom(MASTER_BEDROOM, new MasterBedroom());
	createRoom(WARDROBE, new Wardrobe());
	createRoom(BEDROOM_BATH, new BedroomBath());
}
void RoomManager::mqttUpdate(const char* sensorTopic, float value) {
	if (!strcmp(sensorTopic, SENSOR_KIDS_01)) {
		rooms[KIDS_BEDROOM]->updateTempSensor(value);
		return;
	} else if (!strcmp(sensorTopic, SENSOR_CORRIDOR_01)) {
		rooms[CORRIDOR]->updateTempSensor(value);
		return;
	} else if (!strcmp(sensorTopic, SENSOR_BIGBATH_01)) {
		rooms[BIG_BATHROOM]->updateTempSensor(value);
		return;
	} else if (!strcmp(sensorTopic, SENSOR_BIGBATH_02)) {
		rooms[BIG_BATHROOM]->updateHumSensor(value);
		return;
	} else if (!strcmp(sensorTopic, SENSOR_MASTER_BEDROOM_01)) {
		rooms[MASTER_BEDROOM]->updateTempSensor(value);
		return;
	} else if (!strcmp(sensorTopic, SENSOR_WARDROBE_01)) {
		rooms[WARDROBE]->updateTempSensor(value);
		return;
	} else if (!strcmp(sensorTopic, SENSOR_BEDROOM_BATH_01)) {
		rooms[BEDROOM_BATH]->updateTempSensor(value);
		return;
	}  else if (!strcmp(sensorTopic, SENSOR_BEDROOM_BATH_02)) {
		rooms[BEDROOM_BATH]->updateHumSensor(value);
		return;
	}
}
