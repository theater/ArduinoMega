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
		bool decisionHeating;

		HumiditySensor* humSensor;
		short desiredHumidity;
		bool decisionFan;

		MotionSensor* motionSensor;

		bool hasTemperatureControl;
		bool hasHumidityControl;
		bool hasMotionControl;
		bool hasLightControl;

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
		bool getDecisionFan() const;
		void setDecisionFan(bool decisionFan);
		bool getDecisionHeating() const;
		void setDecisionHeating(bool decisionHeating);
		bool getHasHumidityControl() const;
		void setHasHumidityControl(bool hasHumidityControl);
		bool getHasLightControl() const;
		void setHasLightControl(bool hasLightControl);
		bool getHasMotionControl() const;
		void setHasMotionControl(bool hasMotionControl);
		bool getHasTemperatureControl() const;
		void setHasTemperatureControl(bool hasTemperatureControl);
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

	private:
		bool decisionMaker();
		bool humDecisionMaker();
		bool tempDecisionMaker();
};

#endif /* MODEL_ROOM_H_ */
