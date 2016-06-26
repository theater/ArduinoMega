/*
 * BedRoomKids.h
 *
 *  Created on: 11.06.2016 ã.
 *      Author: theater
 */

#ifndef MODEL_KIDSBEDROOM_H_
#define MODEL_KIDSBEDROOM_H_

#include <WString.h>

#include "../Config/Config.h"
#include "OutputControl.h"
#include "Room.h"

// specific implementation for Kids bedroom
class KidsBedroom: public Room {
	private:
		const static RoomId id=KIDS_BEDROOM;

		OutputControl* kidsRadiatorOne;
		OutputControl* kidsRadiatorTwo;

		//TODO: ugly - fix it somehow later
		const static int length = 4;
		const char * topics[length] = {	RAD_KIDS_01,
										RAD_KIDS_02,
										DESIRED_TEMP_KIDS_01,
										MODE_KIDS
									};

	public:
		KidsBedroom(PubSubClient* mqttClient, bool DEBUG=false);
		virtual ~KidsBedroom();
		void updateOutputControllers();
		void mqttReceive(const char* strTopic, const char* strPayload);
		void heatOutputs(bool state);
};

#endif /* MODEL_KIDSBEDROOM_H_ */
