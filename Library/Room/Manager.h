/*
 * Manager.h
 *
 *  Created on: 26.06.2016 ã.
 *      Author: theater
 */

#ifndef ROOM_MANAGER_H_
#define ROOM_MANAGER_H_

#include "Util.h"
#include "Room.h"

class Manager {
public:
	Manager(int count);
	virtual ~Manager();

	virtual Room* addRoom(Room * room) = 0;
	virtual void mqttUpdate(const char* sensor, float value) = 0;
	void mqttReceive(const char* topic, const char* strPayload);
	static void mqttCallback(const char* topic, uint8_t* payload, unsigned int length);
	void mqttSubscribe();
	Room* getRoom(RoomId id);

	// Getters and setters
	Room** getRooms();
	int getCount();

protected:
	int count;
	Room** rooms;

};

#endif /* ROOM_MANAGER_H_ */
