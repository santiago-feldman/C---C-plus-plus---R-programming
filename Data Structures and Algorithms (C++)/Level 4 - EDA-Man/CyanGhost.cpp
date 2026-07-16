/**
 * EDA-Man
 *
 * @copyright Copyright (C) 2022
 * @author Marc S. Ressl
 *
 * @brief Controls an EDA-Man game.
 */

/**
 * @author Solari Agustin
 *         Viola Santiago
 *         Fisher Agustin
 *         Feldmann Santiago
 * 
 * @brief Controll the CyanGhost in the game
 * @version 0.1
 * @date 2022-05-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "CyanGhost.h"
#include "Robot.h"

#include <string>

using namespace std;

void CyanGhost::start(GameModel *gameModel, MQTTClient *mqttClient)
{
    robotId = "robot5";

    this->gameModel = gameModel;
    this->mqttClient = mqttClient;

    restart();

    isMoving = 0;
    imageIndex = 20;
    currentImageIndex = 0;
    lastImageTime = 0;

    setDisplay(imageIndex);
}

void CyanGhost::restart()
{
    targetMapPosition = {14.0f, 18.5f};
    targetMapRotation = DirectionLeft;
    setpoint = getSetpoint(targetMapPosition);
    setpoint.rotation = (float)((targetMapRotation - 1) * 90);

    liftTo({setpoint.position.x, 0.5, setpoint.position.y});
    setSetpoint(setpoint);
}

void CyanGhost::getPersecutionModeMapPosition()
{
    Vector2 targetTile;
    Vector2 EDAManMapPosition = gameModel->getRobot(0)->getRobotTargetMapPosition();
    Direction EDAManMapRotation = gameModel->getRobot(0)->getRobotTargetMapDirection();
    Vector2 redGhostMapPosition = gameModel->getRobot(1)->getRobotTargetMapPosition();

    switch (EDAManMapRotation)
    {
    case DirectionUp:
        EDAManMapPosition.y -= 2;
        break;

    case DirectionLeft:
        EDAManMapPosition.x -= 2;
        break;

    case DirectionDown:
        EDAManMapPosition.y += 2;
        break;

    case DirectionRight:
        EDAManMapPosition.x += 2;
        break;

    default:
        break;
    }

    targetTile = Vector2Subtract(Vector2Scale(EDAManMapPosition, 2), redGhostMapPosition);

    objectiveMapPoint = targetTile;
}

void CyanGhost::getDispersionModeMapPosition()
{
    objectiveMapPoint = {0.5f, 35.5f};
}