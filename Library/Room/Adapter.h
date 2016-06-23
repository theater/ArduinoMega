/*
 * HeatingAdapter.h
 *
 *  Created on: 23.06.2016 ã.
 *      Author: theater
 */

#ifndef ROOM_ADAPTER_H_
#define ROOM_ADAPTER_H_
#include <PubSubClient.h>

class Adapter {
public:
	Adapter();
	virtual ~Adapter();
	virtual void mqttReceive(const char* topic, const char* strPayload) = 0;
	virtual void mqttSubscribe(PubSubClient *mqttClient) = 0;
};

#endif /* ROOM_ADAPTER_H_ */
