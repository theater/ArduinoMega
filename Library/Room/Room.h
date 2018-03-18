/*
 * Room.h
 *
 *  Created on: 11.06.2016 ã.
 *      Author: theater
 */

#ifndef MODEL_ROOM_H_
#define MODEL_ROOM_H_

#include <Arduino.h>
#include <Util.h>
#include <Sensor.h>
#include <OutputControl.h>
#include <Mode.h>
#include <DesiredSensorValue.h>


// Abstract base class for all rooms
class Room {
	protected:
		Sensor** sensors;
		OutputControl** outputs;
		DesiredSensorValue** desiredValues;
		RoomId id;
		Mode* mode;

	public:
		Room(RoomId id);
		virtual ~Room();
//		void heatOutputs(bool state) = 0; 			// OVERRIDE THESE IN DERRIVED CLASS TO ADD LOGIC.
//		void chillOutputs(bool state) = 0;			// OVERRIDE THESE IN DERRIVED CLASS TO ADD LOGIC.
//		void humidityControl(bool state, bool fanSpeed) = 0;		// OVERRIDE THESE IN DERRIVED CLASS TO ADD LOGIC.

		void updateItems(const char* topic, const char* strPayload);

		Sensor* addSensor(Sensor* sensor);
		void updateSensors(const char* id, const char* value);

		void createMode(Mode* mode);
		void updateMode(const char* id, const char* value);

		void addDesiredValue(DesiredSensorValue * desiredValue);
		void updateDesiredValues(const char* id, const char* value);

//		void updateOutputControllers();



		ModeType getMode() const;
		void setMode(ModeType mode);

		void subscribeMqttTopics();
		void mqttUpdateSensors(const char* topic, const char* value);
		void mqttUpdateOutputControl(OutputControl* outputControl, const char* payload);
		void updateDecisionMakers();

		RoomId getId() const;
		void setId(RoomId id);

		private:
		bool decisionMaker();
		bool ventDecisionMaker();
		bool heatingDecisionMaker();
};

#endif /* MODEL_ROOM_H_ */
