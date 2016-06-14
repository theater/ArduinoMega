/*
 * BedRoomKids.h
 *
 *  Created on: 11.06.2016 ã.
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
		OutputControl* kidsRoomFan;

		//TODO: ugly - fix it somehow later
		const char * mqttTopics[2] = {RAD_KIDS_01, RAD_KIDS_02};

	public:
		BedRoomKids(PubSubClient* mqttClient);
		virtual ~BedRoomKids();
		void updateOutputControllers();
		void mqttSubscribe(const char* const* topics,int len);
		void mqttReceive(String* strTopic, String strPayload);
		void mqttParse( char* strTopic,  char* strPayload);
};

#endif /* MODEL_BEDROOMKIDS_H_ */
