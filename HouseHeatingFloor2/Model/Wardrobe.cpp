/*
 * Wardrobe.cpp
 *
 *  Created on: 27.06.2016 ã.
 *      Author: theater
 */

#include "Wardrobe.h"

Wardrobe::Wardrobe(PubSubClient* mqttClient, bool DEBUG) : Room(id, mqttClient) {
	setDebug(DEBUG);
			if(Debug()) {
				mqttClient->publish("DEBUG","Wardrobe::Wardrobe()");
			}

			// initialize and create Output controllers
			radiatorOne = new OutputControl(WARDROBE_RAD, OFF, RAD_WARDROBE_CB, mqttClient);
			setHasHeatingControl(true);
			// initialize and create sensors
			Sensor* tempSensor = createSensor(TEMPERATURE, mqttClient, SENSOR_WARDROBE_01);
			setTempSensor((TemperatureSensor*)tempSensor);

			// Set MQTT topics to listen to...
			setMqttTopics(topics);
			setLen(length);

			subscribeMqttTopics(mqttClient);
}

Wardrobe::~Wardrobe() {
	delete radiatorOne;
}

// Virtual functions - defined here the outputs associated with specific services (heat, chill, humidity)
void Wardrobe::heatOutputs(bool state) {
	radiatorOne->setPin(state);
}

void Wardrobe::mqttReceive(const char* topic, const char* payload) {
	String strTopic = String(topic);
	String strPayload = String(payload);
	if (strTopic.equals(MODE_WARDROBE)) {
		updateMode(payload);
	} else if (strTopic.equals(DESIRED_TEMP_WARDROBE_01)) {
		updateDesiredTemperature(atof(payload));
	} else if (strTopic.equals(RAD_WARDROBE)) {
		mqttUpdateOutputControl(radiatorOne, payload);
	} else {
		getMqttClient()->publish("DEBUG", "No matching rules found");
	}
}
