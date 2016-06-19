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

		//TODO: ugly - fix it somehow later
		const static int len = 3;
		const char * mqttTopics[len] = {RAD_KIDS_01, RAD_KIDS_02, DESIRED_KIDS_01};
	public:
		BedRoomKids(PubSubClient* mqttClient, bool DEBUG=false);
		virtual ~BedRoomKids();
		void updateOutputControllers();
		void mqttSubscribe(const char* const* topics,int len, PubSubClient* const mqttClient);
		void mqttReceive(const char* strTopic, const char* strPayload);
		void mqttParse( char* strTopic,  char* strPayload);
		const char** getMqttTopics();
		bool containsTopic(const char* topic);

		static const int getLen();
};

#endif /* MODEL_BEDROOMKIDS_H_ */
