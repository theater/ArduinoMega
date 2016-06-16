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
class HeatingAdapter {
	private:
		PubSubClient* mqttClient;
		BedRoomKids* bedRoomKids;
	public:
		HeatingAdapter(PubSubClient* mqttClient);
		virtual ~HeatingAdapter();
		//MQTT
		void mqttCallback(char* topic, byte* payload, unsigned int length);
		void mqttReceive(char* topic, char* strPayload);

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
