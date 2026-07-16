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
 * @brief Controll the playable Robot in the game
 * @version 0.1
 * @date 2022-05-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "EDAMan.h"

#include <vector>
#include <iostream>
#include <string>

#define ANGLE 0.01f

using namespace std;

/**
 * @brief Start the main robot
 *
 * @param gameModel Reference to the game model
 * @param mqttClient Reference to the mqttClient
 */
void EDAMan::start(GameModel *gameModel, MQTTClient *mqttClient)
{
    robotId = "robot1";

    this->gameModel = gameModel;
    this->mqttClient = mqttClient;

    restart();

    isMoving = 0;

    imageIndex = 1;
    currentImageIndex = 0;
    lastImageTime = 0;

    setDisplay(imageIndex);
}

void EDAMan::restart()
{
    targetMapPosition = {14.5f, 26.5f};
    targetMapRotation = DirectionLeft;
    setpoint = getSetpoint(targetMapPosition);
    setpoint.rotation = (float)((targetMapRotation - 1) * 90);

    liftTo({setpoint.position.x, 0.5, setpoint.position.y});
    setSetpoint(setpoint);
}

/**
 * @brief Robot Update that analice if move the setpoint
 *
 * @param deltaTime : deltaTime since the last update
 */
void EDAMan::update(float deltaTime)
{
    Vector2 currentMapPosition = getMapPosition(setpoint);
    keyPressed = gameModel->getLastKeyPressed();

    if ((abs(targetMapPosition.x - currentMapPosition.x) > DISTANCE) ||
        (abs(targetMapPosition.y - currentMapPosition.y) > DISTANCE) ||
        (abs((targetMapRotation - 1) * 90.0f - setpoint.rotation)) > ANGLE)
    {
        isMoving = 1;
    }

    else
    {
        isMoving = 0;
    }

    if (isMoving)
    {
        if (gameModel->getGameMode() == Blue)
        {
            updateSetpoint(0.6f, deltaTime);
        }
        else // Dispersion mode or chase mode
        {
            updateSetpoint(0.5f, deltaTime);
        }
        setSetpoint(setpoint);
    }

    else if (keyPressed)
    {
        moveRobot();
        if (gameModel->getGameMode() == Blue)
        {
            updateSetpoint(0.6f, deltaTime);
        }
        else // Dispersion mode or chase mode
        {
            updateSetpoint(0.5f, deltaTime);
        }
        setSetpoint(setpoint);
    }

    updateImage();
}

/**
 * @brief Analice the keyboard entry and determinate the next position
 *
 */
void EDAMan::moveRobot()
{
    Vector2 nextPosition;

    switch (keyPressed)
    {
    case KEY_UP:
        targetMapRotation = DirectionUp;
        nextPosition.x = targetMapPosition.x;
        nextPosition.y = targetMapPosition.y - 1;
        break;
    case KEY_LEFT:
        targetMapRotation = DirectionLeft;
        nextPosition.x = targetMapPosition.x - 1;
        nextPosition.y = targetMapPosition.y;
        break;
    case KEY_RIGHT:
        targetMapRotation = DirectionRight;
        nextPosition.y = targetMapPosition.y;
        nextPosition.x = targetMapPosition.x + 1;
        break;
    case KEY_DOWN:
        targetMapRotation = DirectionDown;
        nextPosition.x = targetMapPosition.x;
        nextPosition.y = targetMapPosition.y + 1;
        break;
    }

    if (gameModel->isTileFree(nextPosition))
    {
        targetMapPosition.x = nextPosition.x;
        targetMapPosition.y = nextPosition.y;
    }
}

/**
 * @brief Update the EDAMan image
 *
 */
void EDAMan::updateImage(void)
{
    float actualTime = gameModel->getGameTime();
    if (actualTime - lastImageTime > 1.0f)
    {
        if (currentImageIndex == (imageIndex + 1))
        {
            currentImageIndex--;
        }
        else
        {
            currentImageIndex++;
        }
        lastImageTime = actualTime;
    }
    setDisplay(currentImageIndex);
}