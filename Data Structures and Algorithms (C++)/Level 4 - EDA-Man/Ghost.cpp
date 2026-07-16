#include "Ghost.h"
#include "Robot.h"

#include <stdbool.h>
#include <string>
#include <raylib.h>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <map>

#define MIN_DISTANCE 0.001f

using namespace std;

void Ghost::update(float deltaTime)
{
    setTargetMapPosition();
    Vector2 actualMapPosition = getMapPosition(setpoint);
    if ((abs(targetMapPosition.x - actualMapPosition.x) < DISTANCE) &&
        (abs(targetMapPosition.y - actualMapPosition.y) < DISTANCE))
    {
        move();
    }
    if (gameModel->getGameMode() == Blue)
    {
        updateSetpoint(0.35f, deltaTime);
        virtualImageIndex = 24;
        currentImageIndex = 24;
    }
    else // Dispersion mode or chase mode
    {
        updateSetpoint(0.4f, deltaTime);
        virtualImageIndex = imageIndex;
        currentImageIndex = imageIndex;
    }
    setSetpoint(setpoint);
    updateImage();
}

void Ghost::move(void)
{
    Vector2 previousMapPosition = targetMapPosition;

    switch (targetMapRotation)
    {
    case DirectionUp:
        targetMapPosition.y -= 1;
        break;
    case DirectionLeft:
        targetMapPosition.x -= 1;
        break;
    case DirectionDown:
        targetMapPosition.y += 1;
        break;
    case DirectionRight:
        targetMapPosition.x += 1;
        break;
    default:
        break;
    }

    vector<Vector2> posibleNextPositions =
        {
            {targetMapPosition.x, targetMapPosition.y - 1},
            {targetMapPosition.x - 1, targetMapPosition.y},
            {targetMapPosition.x, targetMapPosition.y + 1},
            {targetMapPosition.x + 1, targetMapPosition.y}};

    float minDistance = MAZE;
    int nextPositionIndex = 0;

    for (int i = 0; i < posibleNextPositions.size(); i++)
    {
        if (((abs(posibleNextPositions[i].x - previousMapPosition.x) > MIN_DISTANCE) || abs(posibleNextPositions[i].y - previousMapPosition.y) > MIN_DISTANCE) && gameModel->isTileFree(posibleNextPositions[i]))
        {
            float distance = Vector2Distance(objectiveMapPoint, posibleNextPositions[i]);

            if (distance < minDistance)
            {
                minDistance = distance;
                nextPositionIndex = i;
            }
        }
    }

    switch (nextPositionIndex)
    {
    case 0:
        targetMapRotation = DirectionUp;
        break;
    case 1:
        targetMapRotation = DirectionLeft;
        break;
    case 2:
        targetMapRotation = DirectionDown;
        break;
    case 3:
        targetMapRotation = DirectionRight;
        break;
    default:
        break;
    }
}

void Ghost::getBlueModeMapPosition()
{
    int mapTargetY = rand() % MAZE_HEIGHT;
    int mapTargetX = rand() % MAZE_WIDTH;

    objectiveMapPoint = {(float)(mapTargetX + 0.5), (float)(mapTargetY + 0.5)};
}

void Ghost::setTargetMapPosition()
{
    switch (gameModel->getGameMode())
    {
    case Dispersion:
        getDispersionModeMapPosition();

        break;

    case Chase:
        getPersecutionModeMapPosition();
        
        break;

    case Blue:
        getBlueModeMapPosition();
        
        break;
    }
}

void Ghost::updateImage(void)
{
    float actualTime = gameModel->getGameTime();

    if (actualTime - lastImageTime > 1.0f)
    {

        if (currentImageIndex == (virtualImageIndex + 1))
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