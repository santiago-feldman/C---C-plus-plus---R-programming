/*****************************************************************//**
* \file   Controller.cpp
* \brief  Controller Class Code.
*
* \authors Matias Ezequiel Alvarez, Santiago Feldman.
* \date   March 2022
*********************************************************************/

#include "Controller.h"
#include "raylib.h"

#define BASE_CURRENT 0.5 // A
#define MAX_TEMP 125	 // C
#define ROTATION 50

enum
{
	MOTOR_1 = 1,
	MOTOR_2,
	MOTOR_3,
	MOTOR_4,
	MOTOR_NUM
};

using namespace std;

vector<char> float2vector(float num);
float vector2float(vector<char> source);

/// @brief Controller Class Constructor.
Controller::Controller() : mosquitto("controller")
{
	mosquitto.connect("127.0.0.1", 1883, "user", "vdivEMMN3SQWX2Ez");
	mosquitto.subscribe("robot1/+/+");
}

/// @brief Robot Movement Method.
/// @param "x" Axis.
/// @param "y" Axis.
/// @param "z" Axis.
/// @param Scale.
void Controller::moveRobot(float xAxis, float yAxis, float zAxis, float scale)
{
	float translationCurrent = scale * BASE_CURRENT;
	float rotationCurrent = (scale * BASE_CURRENT) / ROTATION;

	setMotorCurrent(translationCurrent * (-xAxis + yAxis) + rotationCurrent * zAxis, MOTOR_1);
	setMotorCurrent(translationCurrent * (-xAxis - yAxis) + rotationCurrent * zAxis, MOTOR_2);
	setMotorCurrent(translationCurrent * (xAxis - yAxis) + rotationCurrent * zAxis, MOTOR_3);
	setMotorCurrent(translationCurrent * (xAxis + yAxis) + rotationCurrent * zAxis, MOTOR_4);
}

/// @brief Sets the motors´ Current.
/// @param Current to set motor to (float).
/// @param Motor Number (char).
void Controller::setMotorCurrent(float current, char motorNum)
{
	switch (motorNum)
	{
	case MOTOR_1:
		mosquitto.publish("robot1/motor1/current/set", float2vector(current));
		break;

	case MOTOR_2:
		mosquitto.publish("robot1/motor2/current/set", float2vector(current));
		break;

	case MOTOR_3:
		mosquitto.publish("robot1/motor3/current/set", float2vector(current));
		break;

	case MOTOR_4:
		mosquitto.publish("robot1/motor4/current/set", float2vector(current));
		break;

	default:
		break;
	}
}

/// @brief Gets the motors´ temperature.
/// @param motorNum Motor Number (char).
/// @return Temperature (float).
float Controller::getMotorTemp(char motorNum)
{
	vector<MQTTMessage> messages = mosquitto.getMessages();
	size_t msgSize = messages.size();
	float temperature = 0;

	switch (motorNum)
	{
	case MOTOR_1:
		for (size_t i = 0; i < msgSize; i++)
		{
			if (messages[i].topic == "robot1/motor1/temperature")
			{
				temperature = vector2float(messages[i].payload);
			}
		}
		break;

	case MOTOR_2:
		for (size_t i = 0; i < msgSize; i++)
		{
			if (messages[i].topic == "robot1/motor2/temperature")
			{
				temperature = vector2float(messages[i].payload);
			}
		}
		break;

	case MOTOR_3:
		for (size_t i = 0; i < msgSize; i++)
		{
			if (messages[i].topic == "robot1/motor3/temperature")
			{
				temperature = vector2float(messages[i].payload);
			}
		}
		break;

	case MOTOR_4:
		for (size_t i = 0; i < msgSize; i++)
		{
			if (messages[i].topic == "robot1/motor4/temperature")
			{
				temperature = vector2float(messages[i].payload);
			}
		}
		break;

	default:
		break;
	}

	messages.clear();

	return temperature;
}

/// @brief Checks if the Motor's Temperature is below the Threshold (125 C)
/// @return Bool.
bool Controller::isTempOK()
{
	for (int i = MOTOR_1; i < MOTOR_NUM; i++)
	{
		if (getMotorTemp(i) > MAX_TEMP)
			return false;
	}
	return true;
}

/// @brief Checks if a connection is established.
/// @return Bool.
bool Controller::isConnected()
{
	return mosquitto.isConnected();
}

/// @brief Converts a float value into a vector<char>.
/// @param Float value to be converted to a vector<char>.
/// @return Vector<char> with the float value.
vector<char> float2vector(float num)
{
	vector<char> destination(sizeof(float));
	memcpy(destination.data(), &num, sizeof(float));
	return destination;
}

/// @brief Converts a vector<char> into a float value.
/// @param vector<char> to be converted to a float value.
/// @return Float value.
float vector2float(vector<char> source)
{
	float result;
	memcpy(&result, source.data(), source.size());
	return result;
}