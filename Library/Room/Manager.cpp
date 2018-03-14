/*
 * Manager.cpp
 *
 *  Created on: 26.06.2016 ã.
 *      Author: theater
 */

#include <Manager.h>
#include <stddef.h>
#include <stdint.h>

Manager::Manager() {
	this->roomCount = ROOM_COUNT + 1;
	this->rooms = new Room*[roomCount];
	for (int i = 0; i < roomCount; i++) {
		rooms[i] = NULL;
	}
}

Manager::~Manager() {
	for (int i = 0; i < roomCount; i++) {
		Room** room = getRooms();
		delete room[i];
	}
	delete this->rooms;
}

Room* Manager::addRoom(Room * room) {
	RoomId id = room->getId();
	rooms[id] = room;
	return room;
}

void Manager::mqttSubscribe() {
	for (int i = 0; i < roomCount; i++) {
		if (rooms[i]) {
			rooms[i]->subscribeMqttTopics();
		}
	}
}

void Manager::mqttCallback(const char* topic, uint8_t* payload, unsigned int length) {
	char cPayload[10];
	for (int i = 0; i <= length; i++) {
		cPayload[i] = (char) payload[i];
	}
	cPayload[length] = '\0';
//	mqttReceive(topic, cPayload);
}

void Manager::updateReceived(const char* id, const char* value) {
	for(int i = 0 ; i < roomCount ; i++) {
		if(rooms[i] != NULL) {
			rooms[i]->updateItems(id, value);
		}
	}
}

Room* Manager::getRoom(RoomId id) {
	return rooms[id];
}

Room** Manager::getRooms() {
	return rooms;
}

int Manager::getCount() {
	return roomCount;
}
