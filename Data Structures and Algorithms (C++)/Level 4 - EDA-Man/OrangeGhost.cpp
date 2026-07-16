#include "OrangeGhost.h"

#include <string>

using namespace std;

void OrangeGhost::start(GameModel *gameModel, MQTTClient *mqttClient)
{
    robotId = "robot4";

    this->gameModel = gameModel;
    this->mqttClient = mqttClient;

    restart();

    isMoving = 0;

    imageIndex = 22;
    currentImageIndex = 0;
    lastImageTime = 0;

    setDisplay(imageIndex);
}

void OrangeGhost::restart()
{
    targetMapPosition = {13.5f, 18.0f};
    targetMapRotation = DirectionLeft;
    setpoint = getSetpoint(targetMapPosition);
    setpoint.rotation = (float)((targetMapRotation - 1) * 90);

    liftTo({setpoint.position.x, 0.5, setpoint.position.y});
    setSetpoint(setpoint);
}

void OrangeGhost::getDispersionModeMapPosition()
{
    objectiveMapPoint = {27.5f, 35.5f};
}

void OrangeGhost::getPersecutionModeMapPosition()
{
    Vector2 EDAManMapPosition = gameModel->getRobot(0)->getRobotTargetMapPosition();
    if (Vector2Distance(targetMapPosition, EDAManMapPosition) < 8)
    {
        getDispersionModeMapPosition();
    }
    else
    {
        objectiveMapPoint = EDAManMapPosition;
    }
}