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
#include "MqttUtil.h"

// Abstract base class for all rooms
class Room {

	protected:
		Sensor* sensors[];
		RoomId id;
		Mode mode;

	private:
		TemperatureSensor* tempSensor;
		float desiredTemperature;
		bool decisionHeat;
		bool decisionCool;

		HumiditySensor* humSensor;
		short desiredHumidity;
		bool decisionFan;
		bool fanSpeed;

		MotionSensor* motionSensor;
		bool decisionMotion;

		bool hasHeatingControl;
		bool hasVentControl;
		bool hasMotionControl;
		bool hasLightControl;
		bool hasCoolingControl;

		const char ** mqttTopics;
		int len;

		static const int FAN_HIGH_SPEED_TRESHOLD = 15;
		static const double HEATER_TRESHOLD_DEVIATION = 0.5;
		static const int FAN_DEVIATION_TRESHOLD = 3;

	public:
		Room(RoomId id);
		virtual ~Room();
		virtual void mqttReceive(const char* topic, const char* payload) = 0;
//		void heatOutputs(bool state) = 0; 			// OVERRIDE THESE IN DERRIVED CLASS TO ADD LOGIC.
//		void chillOutputs(bool state) = 0;			// OVERRIDE THESE IN DERRIVED CLASS TO ADD LOGIC.
//		void humidityControl(bool state, bool fanSpeed) = 0;		// OVERRIDE THESE IN DERRIVED CLASS TO ADD LOGIC.

		void updateTempSensor(float tempSensorValue);
		void updateHumSensor(short humSensorValue);
		void updateMotionSensor(bool motionSensorValue);
		void updateSensors(short tempSensorValue,short humSensorValue);
		void updateDesiredValues(short desiredTemperature,short desiredHumidity);
		void updateMode(const char* mode);
		Sensor* createSensor(ControlType type, char* topic, boolean directlyAttached=true);
		bool containsTopic(const char * topic);
		void subscribeMqttTopics();
		void mqttUpdateSensors(const char* topic, const char* value);
		void mqttUpdateOutputControl(OutputControl* outputControl, const char* payload);
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
		void setHasFanControl(bool hasVentControl);
		const char** getMqttTopics() const;
		void setMqttTopics(const char** mqttTopics);
		int getLen() const;
		void setLen(int len);
		Mode getMode() const;
		void setMode(Mode mode);
		RoomId getId() const;
		void setId(RoomId id);
		bool getFanSpeed();
		void setFanSpeed(bool fanSpeed);

		private:
		bool decisionMaker();
		bool ventDecisionMaker();
		bool heatingDecisionMaker();
		bool coolingDecisionMaker();
		void sensorToMqttData();
		void sensorToMqttData(Sensor* sensor);
};

#endif /* MODEL_ROOM_H_ */
