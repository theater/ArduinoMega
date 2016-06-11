/*
 * BedRoomKids.h
 *
 *  Created on: 11.06.2016 ã.
 *      Author: theater
 */

#ifndef MODEL_BEDROOMKIDS_H_
#define MODEL_BEDROOMKIDS_H_

#include "../Config/Config.h"
#include "OutputControl.h"
#include "Room.h"
#include "TemperatureSensor.h"

class BedRoomKids: public Room {
	private:
		OutputControl* kidsRadiatorOne;
		OutputControl* kidsRadiatorTwo;
	public:
		BedRoomKids();
		virtual ~BedRoomKids();
};

#endif /* MODEL_BEDROOMKIDS_H_ */
