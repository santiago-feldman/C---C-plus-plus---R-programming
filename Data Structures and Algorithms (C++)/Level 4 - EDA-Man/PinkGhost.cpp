#include "PinkGhost.h"


void PinkGhost::start(GameModel* gameModel, MQTTClient *mqttClient)
{
    robotId = "robot3";
    
    this->gameModel = gameModel;
    this->mqttClient = mqttClient;

    restart();

    isMoving = 0;

    imageIndex = 18;
    currentImageIndex = 18;
    lastImageTime = 0;

    setDisplay(imageIndex);

}

void PinkGhost::restart()
{
    targetMapPosition = {14.5f, 18.0f};
    targetMapRotation = DirectionLeft;
    setpoint = getSetpoint(targetMapPosition);
    setpoint.rotation = (float) ((targetMapRotation - 1) * 90);

    liftTo({setpoint.position.x, 0.5, setpoint.position.y});
    setSetpoint(setpoint);
}

void PinkGhost::getPersecutionModeMapPosition()
{
    Vector2 EDAManMapPosition = gameModel->getRobot(0)->getRobotTargetMapPosition();
    Direction EDAManMapRotation = gameModel->getRobot(0)->getRobotTargetMapDirection();

    switch (EDAManMapRotation)
    {
    case DirectionUp:
        EDAManMapPosition.y += 4;
        break;

    case DirectionDown:
        EDAManMapPosition.y -= 4;
        break;

    case DirectionLeft:
        EDAManMapPosition.x -= 4;
        break;

    case DirectionRight:
        EDAManMapPosition.x += 4;
        break;
    }

    objectiveMapPoint = EDAManMapPosition;
}

void PinkGhost::getDispersionModeMapPosition()
{
    objectiveMapPoint = {3.5f, 0.5f};
}