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

#define REOCCURRENCE 150000  // Decision maker triggered every 2.5min

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
		bool humDecisionMaker();
		bool tempDecisionMaker();
		short getDesiredHumidity() const;
		void setDesiredHumidity(short desiredHumidity);
		short getDesiredTemperature() const;
		void setDesiredTemperature(short desiredTemperature);
};

#endif /* MODEL_ROOM_H_ */
