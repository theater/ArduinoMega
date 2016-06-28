/*
 * HeatingAdapter.h
 *
 *  Created on: 23.06.2016 ã.
 *      Author: theater
 */

#ifndef ROOM_ADAPTER_H_
#define ROOM_ADAPTER_H_
#include <PubSubClient.h>
#include "Manager.h"

class Adapter {
private:
	PubSubClient* mqttClient;
	Manager* manager;
	Room** rooms;
	int count;

	bool DEBUG;
public:
	Adapter(Manager* roomManager, PubSubClient* mqttClient, bool DEBUG = false);
	virtual ~Adapter();
	void mqttReceive(const char* topic, const char* strPayload);
	void mqttSubscribe();
	void sensorUpdate(const char* sensor, float value);
};

#endif /* ROOM_ADAPTER_H_ */
