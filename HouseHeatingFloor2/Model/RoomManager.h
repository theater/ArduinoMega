/*
 * RoomManager.h
 *
 *  Created on: 24.06.2016 �.
 *      Author: theater
 */

#ifndef MODEL_ROOMMANAGER_H_
#define MODEL_ROOMMANAGER_H_

#include <Room.h>
#include <Util.h>
#include <PubSubClient.h>
#include "BedRoomKids.h"
#include "Manager.h"


class RoomManager : public Manager {
public:
	virtual ~RoomManager();

	Room* createRoom(RoomId id);
	void sensorsUpdate(const char* sensor, short value);
	static RoomManager* getInstance(PubSubClient* mqttClient);
	static RoomManager* manager;

	// Getters/setters
	Room** getRooms();
private:
	RoomManager(PubSubClient* mqttClient);
	PubSubClient* mqttClient;
};

#endif /* MODEL_ROOMMANAGER_H_ */
