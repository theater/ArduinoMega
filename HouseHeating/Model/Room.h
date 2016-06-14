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

class String;

class PubSubClient;

// Abstract base class for all rooms
class Room {
	private:
		PubSubClient* mqttClient;
		short desiredTemperature;
		TemperatureSensor tempSensor;
		bool decisionHeating;

		short desiredHumidity;
		HumiditySensor humSensor;
		bool decisionFan;

		bool hasTemperatureControl;
		bool hasHumidityControl;
		bool hasMotionControl;
		bool hasLightControl;

		const bool DEBUG = true;

	public:
		Room(PubSubClient * mqttClient);
		virtual ~Room();
		virtual void updateOutputControllers() = 0;
		void updateTempSensor(short tempSensorValue);
		void updateHumSensor(short tempSensorValue);
		void updateSensors(short tempSensorValue,short humSensorValue);
		void updateDesiredValues(short desiredTemperature,short desiredHumidity);

		short getDesiredHumidity() const;
		void setDesiredHumidity(short desiredHumidity);
		short getDesiredTemperature() const;
		void setDesiredTemperature(short desiredTemperature);
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
		void updateDesiredTemperature(short desiredTemperature);
		void updateDesiredHumidity(short desiredHumidity);

	private:
		bool decisionMaker();
		bool humDecisionMaker();
		bool tempDecisionMaker();
};

#endif /* MODEL_ROOM_H_ */
