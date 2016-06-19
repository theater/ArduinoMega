/*
 * Room.h
 *
 *  Created on: 11.06.2016 ã.
 *      Author: theater
 */

#ifndef MODEL_ROOM_H_
#define MODEL_ROOM_H_

#include <stdbool.h>

#include "HumiditySensor.h"
#include "TemperatureSensor.h"
#include "MotionSensor.h"
class String;

class PubSubClient;

// Abstract base class for all rooms
class Room {
	private:
		PubSubClient* mqttClient;

		TemperatureSensor* tempSensor;
		float desiredTemperature;
		bool decisionHeat;
		bool decisionCool;

		HumiditySensor* humSensor;
		short desiredHumidity;
		bool decisionVent;

		MotionSensor* motionSensor;

		bool hasHeatingControl;
		bool hasVentControl;
		bool hasMotionControl;
		bool hasLightControl;
		bool hasCoolingControl;

		int len;
		const char ** mqttTopics;

		bool DEBUG;

	public:
		Room(PubSubClient *  mqttClient, bool DEBUG = false);
		virtual ~Room();
		virtual void updateOutputControllers() = 0;
		void updateTempSensor(float tempSensorValue);
		void updateHumSensor(short humSensorValue);
		void updateSensors(short tempSensorValue,short humSensorValue);
		void updateDesiredValues(short desiredTemperature,short desiredHumidity);
		Sensor* createSensor(ControlType type, PubSubClient* mqttClient, char* topic);

		short getDesiredHumidity() const;
		void setDesiredHumidity(short desiredHumidity);
		float getDesiredTemperature() const;
		void setDesiredTemperature(float desiredTemperature);
		bool getHasLightControl() const;
		void setHasLightControl(bool hasLightControl);
		bool getHasMotionControl() const;
		void setHasMotionControl(bool hasMotionControl);
		PubSubClient* getMqttClient() const;
		void setMqttClient(PubSubClient* mqttClient);
		void updateDesiredTemperature(float desiredTemperature);
		void updateDesiredHumidity(short desiredHumidity);
		void setDebug(bool debug);
		HumiditySensor* getHumSensor();
		void setHumSensor(HumiditySensor* humSensor);
		MotionSensor* getMotionSensor();
		void setMotionSensor(MotionSensor* motionSensor);
		TemperatureSensor* getTempSensor();
		void setTempSensor(TemperatureSensor* tempSensor);
		bool Debug();
		bool getDecisionCool() const;
		void setDecisionCool(bool decisionCool);
		bool getDecisionHeat() const;
		void setDecisionHeat(bool decisionHeat);
		bool getDecisionVent() const;
		void setDecisionVent(bool decisionVent);
		bool getHasCoolingControl() const;
		void setHasCoolingControl(bool hasCoolingControl);
		bool getHasHeatingControl() const;
		void setHasHeatingControl(bool hasHeatingControl);
		bool getHasVentControl() const;
		void setHasVentControl(bool hasVentControl);
		const char** getMqttTopics() const;
		void setMqttTopics(const char** mqttTopics);

			private:
		bool decisionMaker();
		bool ventDecisionMaker();
		bool heatingDecisionMaker();
		bool coolingDecisionMaker();
};

#endif /* MODEL_ROOM_H_ */
