/*
 * Manager.cpp
 *
 *  Created on: 26.06.2016 ã.
 *      Author: theater
 */
#include <Manager.h>

Manager::~Manager() {
	delete this->rooms;
	for (int i = 0; i < count; i++) {
		delete rooms[i];
	}
}

Manager::Manager(int count) {
	this->count = count;
	this->rooms = new Room*[count];
	for (int i = 0; i < count; i++) {
		rooms[i] = NULL;
	}
}

void Manager::mqttSubscribe() {
	for (int i = 0; i < count; i++) {
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

void Manager::mqttReceive(const char* topic, const char* payload) {
	for (int i = 0; i < count; i++) {
		if (rooms[i] != NULL && rooms[i]->containsTopic(topic)) {
			rooms[i]->mqttReceive(topic, payload);
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
	return count;
}
