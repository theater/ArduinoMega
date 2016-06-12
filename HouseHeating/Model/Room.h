/*
 * Room.h
 *
 *  Created on: 11.06.2016 �.
 *      Author: theater
 */

#ifndef MODEL_ROOM_H_
#define MODEL_ROOM_H_

#include "HumiditySensor.h"
#include "TemperatureSensor.h"

// Abstract base class for all rooms
class Room {
	private:
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

	public:
		Room();
		virtual ~Room();
		virtual void updateOutputControllers() = 0;
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
	private:
		bool decisionMaker();
		bool humDecisionMaker();
		bool tempDecisionMaker();

};

#endif /* MODEL_ROOM_H_ */
