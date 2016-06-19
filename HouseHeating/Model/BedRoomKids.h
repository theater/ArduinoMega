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
		OutputControl* kidsRadiatorOne;
		OutputControl* kidsRadiatorTwo;
		OutputControl* chiller;

		//TODO: ugly - fix it somehow later
		const static int length = 4;
		const char * topics[length] = {RAD_KIDS_01, RAD_KIDS_02, DESIRED_KIDS_01, CHILLER};

	public:
		BedRoomKids(PubSubClient* mqttClient, bool DEBUG=false);
		virtual ~BedRoomKids();
		void updateOutputControllers();
		void mqttReceive(const char* strTopic, const char* strPayload);
};

#endif /* MODEL_BEDROOMKIDS_H_ */
