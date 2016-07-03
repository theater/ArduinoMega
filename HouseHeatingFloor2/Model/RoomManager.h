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
#include "BedRoomKids.h"
#include "Corridor.h"
#include "BigBathroom.h"
#include "MasterBedroom.h"
#include "Wardrobe.h"
#include "BedroomBath.h"

class RoomManager : public Manager {
public:
	virtual ~RoomManager();

	Room* createRoom(RoomId id, bool DEBUG=false);
	void sensorsUpdate(const char* sensor, float value);
	static RoomManager* getInstance(PubSubClient* mqttClient);
	static RoomManager* manager;

	// Getters/setters
	PubSubClient* getMqttClient();
	void setMqttClient(PubSubClient* mqttClient);

private:
	RoomManager(PubSubClient* mqttClient);
	PubSubClient* mqttClient;
	Room** room;
};

#endif /* MODEL_ROOMMANAGER_H_ */
