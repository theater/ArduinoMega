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
	Manager();
	virtual ~Manager();

	Room* addRoom(Room * room);
	void updateReceived(const char* topic, const char* strPayload);
	static void mqttCallback(const char* topic, uint8_t* payload, unsigned int length);
	void mqttSubscribe();
	Room* getRoom(RoomId id);

	// Getters and setters
	Room** getRooms();
	int getCount();

protected:
	int roomCount;
	Room** rooms;

};

#endif /* ROOM_MANAGER_H_ */
