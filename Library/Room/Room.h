/*
 * Room.h
 *
 *  Created on: 11.06.2016 ã.
 *      Author: theater
 */

#ifndef MODEL_ROOM_H_
#define MODEL_ROOM_H_

#include <Arduino.h>
#include <Mode.h>
#include <Util.h>
#include <Sensor.h>
#include <OutputControl.h>


// Abstract base class for all rooms
class Room {

	protected:
		Sensor** sensors;
		OutputControl** outputs;
		RoomId id;
		Mode* mode;

	private:
		float desiredTemperature;
		bool decisionHeat;
		bool decisionCool;

		short desiredHumidity;
		bool decisionFan;
		bool fanSpeed;

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
//		void heatOutputs(bool state) = 0; 			// OVERRIDE THESE IN DERRIVED CLASS TO ADD LOGIC.
//		void chillOutputs(bool state) = 0;			// OVERRIDE THESE IN DERRIVED CLASS TO ADD LOGIC.
//		void humidityControl(bool state, bool fanSpeed) = 0;		// OVERRIDE THESE IN DERRIVED CLASS TO ADD LOGIC.

		Sensor* addSensor(Sensor* sensor);
		void updateItems(const char* topic, const char* strPayload);
		void updateSensors(const char* id, const char* value);
		void updateMode(const char* id, const char* value);



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
		ModeType getMode() const;
		void setMode(ModeType mode);
		void createMode(Mode* mode);
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
