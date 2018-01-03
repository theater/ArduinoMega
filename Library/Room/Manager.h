/*
 * Manager.h
 *
 *  Created on: 26.06.2016 ã.
 *      Author: theater
 */

#ifndef ROOM_MANAGER_H_
#define ROOM_MANAGER_H_

#include "Room.h"
#include <Util.h>
#include <PubSubClient.h>


class Manager {
public:
	Manager(PubSubClient* mqttClient);
	virtual ~Manager();

	virtual Room* createRoom(RoomId id, bool DEBUG) = 0;
	virtual void sensorUpdate(const char* sensor, float value) = 0;
	void mqttReceive(const char* topic, const char* strPayload);
	void mqttSubscribe();
	Room* getRoom(RoomId id);

	// Getters and setters
	PubSubClient* getMqttClient();
	void setMqttClient(PubSubClient* mqttClient);
	Room** getRooms();
	const int getCount();

protected:
	static const int count = 10;
	Room* rooms[count];

private:
	PubSubClient* mqttClient;

};

#endif /* ROOM_MANAGER_H_ */
