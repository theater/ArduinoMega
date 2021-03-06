/*
 * BedRoomKids.h
 *
 *  Created on: 11.06.2016 �.
 *      Author: theater
 */

#ifndef MODEL_BEDROOMKIDS_H_
#define MODEL_BEDROOMKIDS_H_

#include <WString.h>

#include "../Config/Config.h"
#include "OutputControl.h"
#include "Room.h"

// specific implementation for Kids bedroom
class BedRoomKids: public Room {
	private:
		const static RoomId id=KIDS_BEDROOM;

		OutputControl* radiatorOne;
		OutputControl* radiatorTwo;

		//TODO: ugly - fix it somehow later
		const static int length = 4;
		const char * topics[length] = {	RAD_KIDS_01,
										RAD_KIDS_02,
										DESIRED_TEMP_KIDS_01,
										MODE_KIDS
									};

	public:
		BedRoomKids();
		virtual ~BedRoomKids();
		void updateOutputControllers();
		void mqttReceive(const char* strTopic, const char* strPayload);
		void heatOutputs(bool state);
		void chillOutputs(bool state) {};
		void humidityControl(bool state, bool fanSpeed){};
};

#endif /* MODEL_BEDROOMKIDS_H_ */
