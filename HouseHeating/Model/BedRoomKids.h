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

// specific implementation for Kids bedroom
class BedRoomKids: public Room {
	private:
		OutputControl* kidsRadiatorOne;
		OutputControl* kidsRadiatorTwo;
		OutputControl* kidsRoomFan;
	public:
		BedRoomKids();
		virtual ~BedRoomKids();
		void updateOutputControllers();
};

#endif /* MODEL_BEDROOMKIDS_H_ */
