/*****************************************************************//**
* \file   controller.h
* \brief  Controller Class Headaer.
*
* \authors Matias Ezequiel Alvarez, Santiago Feldman
* \date   March 2022
*********************************************************************/

#ifndef CONTROLLERH
#define CONTROLLERH

#include "MQTTClient.h"

using namespace std;

class Controller
{

public:
	Controller();

	bool isTempOK();
	bool isConnected();
	void moveRobot(float, float, float, float);
	float getMotorTemp(char);

private:
	MQTTClient mosquitto;
	void setMotorCurrent(float, char);
	bool isLEDOn = false;
};

#endif // !CONTROLLER.H
