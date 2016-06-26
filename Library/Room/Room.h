/*
 * Room.h
 *
 *  Created on: 11.06.2016 ã.
 *      Author: theater
 */

#ifndef MODEL_ROOM_H_
#define MODEL_ROOM_H_

#include <stdbool.h>

#include "Config.h"
#include "Util.h"
#include "HumiditySensor.h"
#include "TemperatureSensor.h"
#include "MotionSensor.h"
#include "OutputControl.h"
class String;

class PubSubClient;

// Abstract base class for all rooms
class Room {
	private:
		RoomId id;
		PubSubClient* mqttClient;
		Mode mode;

		TemperatureSensor* tempSensor;
		float desiredTemperature;
		bool decisionHeat;
		bool decisionCool;

		HumiditySensor* humSensor;
		short desiredHumidity;
		bool decisionVent;

		MotionSensor* motionSensor;
		bool decisionMotion;

		bool hasHeatingControl;
		bool hasVentControl;
		bool hasMotionControl;
		bool hasLightControl;
		bool hasCoolingControl;

		const char ** mqttTopics;
		int len;

		bool DEBUG;

	public:
		Room(RoomId id, PubSubClient *  mqttClient, bool DEBUG = false);
		virtual ~Room();
		virtual void mqttReceive(const char* topic, const char* payload) = 0;
		virtual void heatOutputs(bool state) = 0; 			// OVERRIDE THESE IN DERRIVED CLASS TO ADD LOGIC.
		virtual void chillOutputs(bool state) = 0;			// OVERRIDE THESE IN DERRIVED CLASS TO ADD LOGIC.
		virtual void humidityOutputs(bool state) = 0;		// OVERRIDE THESE IN DERRIVED CLASS TO ADD LOGIC.

		void updateTempSensor(float tempSensorValue);
		void updateHumSensor(short humSensorValue);
		void updateMotionSensor(bool motionSensorValue);
		void updateSensors(short tempSensorValue,short humSensorValue);
		void updateDesiredValues(short desiredTemperature,short desiredHumidity);
		void updateMode(const char* mode);
		Sensor* createSensor(ControlType type, PubSubClient* mqttClient, char* topic);
		bool containsTopic(const char * topic);
		void subscribeMqttTopics(PubSubClient* mqttClient);
		void mqttSubscribe(const char* const* topics, int len, PubSubClient* const mqttClient);
		void handleMqttCommandOC(OutputControl* outputControl, const char* payload);
		void updateOutputControllers();
		void updateDecisionMakers();

		short getDesiredHumidity() const;
		void setDesiredHumidity(short desiredHumidity);
		float getDesiredTemperature() const;
		void setDesiredTemperature(float desiredTemperature);
		bool getHasLightControl() const;
		void setHasLightControl(bool hasLightControl);
		bool getHasMotionControl() const;
		void setHasMotionControl(bool hasMotionControl);
		PubSubClient* getMqttClient() const;
		void setMqttClient(PubSubClient* mqttClient);
		void updateDesiredTemperature(float desiredTemperature);
		void updateDesiredHumidity(short desiredHumidity);
		void setDebug(bool debug);
		HumiditySensor* getHumSensor();
		void setHumSensor(HumiditySensor* humSensor);
		MotionSensor* getMotionSensor();
		void setMotionSensor(MotionSensor* motionSensor);
		TemperatureSensor* getTempSensor();
		void setTempSensor(TemperatureSensor* tempSensor);
		bool Debug();
		bool getDecisionCool() const;
		void setDecisionCool(bool decisionCool);
		bool getDecisionHeat() const;
		void setDecisionHeat(bool decisionHeat);
		bool getDecisionVent() const;
		void setDecisionVent(bool decisionVent);
		bool getHasCoolingControl() const;
		void setHasCoolingControl(bool hasCoolingControl);
		bool getHasHeatingControl() const;
		void setHasHeatingControl(bool hasHeatingControl);
		bool getHasVentControl() const;
		void setHasVentControl(bool hasVentControl);
		const char** getMqttTopics() const;
		void setMqttTopics(const char** mqttTopics);
		int getLen() const;
		void setLen(int len);
		Mode getMode() const;
		void setMode(Mode mode);
		RoomId getId() const;
		void setId(RoomId id);

		private:
		bool decisionMaker();
		bool ventDecisionMaker();
		bool heatingDecisionMaker();
		bool coolingDecisionMaker();
		void sensorToMqttData();
		void sensorToMqttData(Sensor* sensor, PubSubClient* mqttClient);
};

#endif /* MODEL_ROOM_H_ */
