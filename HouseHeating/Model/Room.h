/*
 * Room.h
 *
 *  Created on: 11.06.2016 ã.
 *      Author: theater
 */

#ifndef MODEL_ROOM_H_
#define MODEL_ROOM_H_

#include <Timer.h>

#include "TemperatureSensor.h"

#define REOCCURRENCE 150000  // Decision maker triggered every 2.5min

class Room {
	private:
		short desiredTemperature;
		short desiredHumidity;
		Timer decisionTimer;
		TemperatureSensor tempSensor;
	public:
		Room();
		virtual ~Room();

		void decisionMaker();

		short getDesiredHumidity() const {
			return desiredHumidity;
		}

		void setDesiredHumidity(short desiredHumidity) {
			this->desiredHumidity = desiredHumidity;
		}

		short getDesiredTemperature() const {
			return desiredTemperature;
		}

		void setDesiredTemperature(short desiredTemperature) {
			this->desiredTemperature = desiredTemperature;
		}
};

#endif /* MODEL_ROOM_H_ */
