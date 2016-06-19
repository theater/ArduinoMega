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
		OutputControl* chiller;

		//TODO: ugly - fix it somehow later
		const static int len = 4;
		const char * mqttTopics[len] = {RAD_KIDS_01, RAD_KIDS_02, DESIRED_KIDS_01, CHILLER};

		void handleOutputControl(OutputControl* outputControl, const char* payload);
		void mqttSubscribe(const char* const* topics,int len, PubSubClient* const mqttClient);

	public:
		BedRoomKids(PubSubClient* mqttClient, bool DEBUG=false);
		virtual ~BedRoomKids();
		void subscribeMqttTopics(PubSubClient* mqttClient);
		void updateOutputControllers();
		void mqttReceive(const char* strTopic, const char* strPayload);
		void mqttParse( char* strTopic,  char* strPayload);
		const char** getMqttTopics();
		bool containsTopic(const char* topic);

		static const int getLen();
};

#endif /* MODEL_BEDROOMKIDS_H_ */
