/*
 * BedRoomKids.h
 *
 *  Created on: 11.06.2016 ã.
 *      Author: theater
 */

#ifndef MODEL_BEDROOMKIDS_H_
#define MODEL_BEDROOMKIDS_H_

#include "Room.h"
#include "TemperatureSensor.h"
#include "OutputControl.h"


class BedRoomKids: public Room {
	private:
		TemperatureSensor tempSensor;
		OutputControl* kidsOne;
	public:
		BedRoomKids();
		BedRoomKids(short outputPinId);
		virtual ~BedRoomKids();
};

#endif /* MODEL_BEDROOMKIDS_H_ */
