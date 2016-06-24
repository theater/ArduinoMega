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
#include "BedRoomKids.h"


class RoomManager {
public:
	virtual ~RoomManager();

	static RoomManager* getInstance(PubSubClient* mqttClient);
	Room* createRoom(RoomId id);
	Room* getRoom(RoomId id);

	// Getters/setters
	Room** getRooms();
private:
	static RoomManager* manager;
	Room* rooms[10];
	PubSubClient* mqttClient;

	RoomManager(PubSubClient* mqttClient);
};

#endif /* MODEL_ROOMMANAGER_H_ */
