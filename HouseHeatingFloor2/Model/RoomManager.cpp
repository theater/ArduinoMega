/*
 * RoomManager.cpp
 *
 *  Created on: 24.06.2016 ã.
 *      Author: theater
 */

#include "RoomManager.h"

RoomManager::RoomManager(PubSubClient* mqttClient) {
	this->mqttClient = mqttClient;
}

RoomManager::~RoomManager() {
}

Room* RoomManager::createRoom(RoomId id) {
	if (rooms[id] == NULL) {
			switch(id) {
			case KIDS_BEDROOM: rooms[id] = new BedRoomKids(mqttClient);
			default: return NULL;
			}
		}
		return rooms[id];
}

Room* RoomManager::getRoom(RoomId id) {
	return createRoom(id);
}

RoomManager* RoomManager::getInstance(PubSubClient* mqttClient) {
	if(manager == NULL) {
		manager = new RoomManager(mqttClient);
	}
	return manager;
}

// Getters and setters
Room** RoomManager::getRooms() {
	return rooms;
}
