/*
 * Room.h
 *
 *  Created on: 11.06.2016 ã.
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
		short desiredHumidity;
		TemperatureSensor tempSensor;
		HumiditySensor humSensor;
		bool decisionHeating;
		bool decisionFan;
	public:
		Room();
		virtual ~Room();
		virtual void updateOutputControllers() = 0;
		void updateSensors(short tempSensorValue,short humSensorValue);

		bool decisionMaker();
		short getDesiredHumidity() const;
		void setDesiredHumidity(short desiredHumidity);
		short getDesiredTemperature() const;
		void setDesiredTemperature(short desiredTemperature);
		bool getDecisionFan() const;
		void setDecisionFan(bool decisionFan);
		bool getDecisionHeating() const;
		void setDecisionHeating(bool decisionHeating);

	private:
		bool humDecisionMaker();
		bool tempDecisionMaker();
};

#endif /* MODEL_ROOM_H_ */
