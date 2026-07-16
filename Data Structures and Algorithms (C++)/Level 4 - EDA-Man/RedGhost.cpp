#include "RedGhost.h"
#include "Robot.h"

#include <iostream>

using namespace std;


void RedGhost::start(GameModel* gameModel, MQTTClient *mqttClient)
{
    robotId = "robot2";
    
    this->gameModel = gameModel;
    this->mqttClient = mqttClient;

    restart();

    isMoving = 0;

    imageIndex = 16;
    currentImageIndex = 0;
    lastImageTime = 0;
}
void RedGhost::restart(void)
{
    targetMapPosition = {14.0f, 18.0f};
    targetMapRotation = DirectionLeft;
    setpoint = getSetpoint(targetMapPosition);
    setpoint.rotation = (float) ((targetMapRotation - 1) * 90);

    liftTo({setpoint.position.x, 0.5, setpoint.position.y});
    setSetpoint(setpoint);
}

void RedGhost::getPersecutionModeMapPosition()
{
    objectiveMapPoint = gameModel->getRobot(0)->getRobotCurrentMapPosition();
}

void RedGhost::getDispersionModeMapPosition()
{
    objectiveMapPoint = {25.5f , 0.5f};
}
