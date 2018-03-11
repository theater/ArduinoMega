/*
 * RoomManager.h
 *
 *  Created on: 24.06.2016 ã.
 *      Author: theater
 */

#ifndef MODEL_ROOMMANAGER_H_
#define MODEL_ROOMMANAGER_H_

#include <Room.h>
#include <Util.h>
#include <PubSubClient.h>
#include "Manager.h"

class RoomManager : public Manager {
public:
	virtual ~RoomManager();

	void createRooms();
	Room* addRoom(Room * room);
	void mqttUpdate(const char* sensorTopic, float value);
	static RoomManager* getInstance();
	static RoomManager* manager;

private:
	RoomManager();
};

#endif /* MODEL_ROOMMANAGER_H_ */
