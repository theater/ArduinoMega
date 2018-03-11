/*
 * RoomManager.cpp
 *
 *  Created on: 24.06.2016 ã.
 *      Author: theater
 */

#include "RoomManager.h"

#include <string.h>

#include "LivingRoom.h"

RoomManager* RoomManager::manager;

RoomManager::RoomManager() : Manager(5) {
	addRoom(new LivingRoom(LIVING_ROOM));
}

RoomManager* RoomManager::getInstance() {
	if(manager == NULL) {
		manager = new RoomManager();
	}
	return manager;
}

RoomManager::~RoomManager() {
	for (int i = 0; i < count; i++) {
		Room** room = getRooms();
		delete room[i];
	}
	delete manager;
}

Room* RoomManager::addRoom(Room * room) {
	RoomId id = room->getId();
	rooms[id] = room;
	return room;
}

void RoomManager::createRooms() {

}
void RoomManager::mqttUpdate(const char* sensorTopic, float value) {
}
