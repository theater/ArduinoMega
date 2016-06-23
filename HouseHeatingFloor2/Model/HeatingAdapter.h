/*
 * HeatingAdapter.h
 *
 *  Created on: 13.06.2016 ã.
 *      Author: theater
 */

#ifndef MODEL_HEATINGADAPTER_H_
#define MODEL_HEATINGADAPTER_H_

#include <PubSubClient.h>
#include <UIPClient.h>
#include "BedRoomKids.h"
#include "Adapter.h"

class HeatingAdapter : public Adapter {
	private:
		PubSubClient* mqttClient;
		BedRoomKids* bedRoomKids;
		bool DEBUG;
	public:
		HeatingAdapter(PubSubClient* mqttClient, bool DEBUG = false);
		virtual ~HeatingAdapter();
		//MQTT
		void mqttCallback(char* topic, byte* payload, unsigned int length);
		void mqttReceive(const char* topic, const char* strPayload);
		void mqttSubscribe(PubSubClient* mqttClient);

		// Connectors to rooms
		void sensorUpdate(const char* sensor, short value);
		void updateRoomDesiredValue(const char* room, ControlType type, short value);

		// Getters/setters
		BedRoomKids* getBedRoomKids() const;
		void setBedRoomKids(BedRoomKids* bedRoomKids);
		PubSubClient* getMqttClient() const;
		void setMqttClient(PubSubClient* mqttClient);

	private:
		void updateDesiredTemperature(const char* room, short value);
		void updateDesiredHumidity(const char* room, short value);
};

#endif /* MODEL_HEATINGADAPTER_H_ */
