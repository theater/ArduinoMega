/*
 * Room.h
 *
 *  Created on: 11.06.2016 ã.
 *      Author: theater
 */

#ifndef MODEL_ROOM_H_
#define MODEL_ROOM_H_

class Room {
	private:
		short desiredTemperature;
		short desiredHumidity;
	public:
		Room();
		virtual ~Room();

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
