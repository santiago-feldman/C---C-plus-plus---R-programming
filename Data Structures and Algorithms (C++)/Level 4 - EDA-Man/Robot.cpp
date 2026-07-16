/**
 * Robot base class.
 *
 * @copyright Copyright (C) 2022
 * @author Marc S. Ressl
 */

#include <cstring>
#include <iostream>
#include <vector>
#include "Robot.h"

using namespace std;

/**
 * @brief Construct a new robot
 * 
 */
Robot::Robot()
{
    // To-Do: set your path!
    displayImages = LoadImage("../RobotImages.png");     
}

/**
 * @brief Destroy the robot
 * 
 */
Robot::~Robot()
{
    UnloadImage(displayImages);
}

/**
 * @brief  Initializes the robot
 *
 */
void Robot::start(GameModel*, MQTTClient *mqttClient_)
{
}

/**
 * @brief Converts a setpoint to a mapPosition.
 *
 * @param setpoint The setpoint
 * @return Vector2 : The map position
 */
Vector2 Robot::getMapPosition(Setpoint setpoint)
{
    Vector2 mapPosition;

    mapPosition.x = (10.0F * (1.4F + setpoint.position.x));
    mapPosition.y = (10.0F * (1.8F - setpoint.position.y));

    return mapPosition;
}

/**
 * @brief Converts the map position in to a setpoint.
 *
 * @param MapPosition The tile position
 * @return : Setpoint The setpoint
 */
Setpoint Robot::getSetpoint(Vector2 MapPosition)
{
    Setpoint setpoint;
    setpoint.position.x = -1.4F + 0.1F * MapPosition.x;
    setpoint.position.y = 1.8F - 0.1F * MapPosition.y;
    setpoint.rotation = this->setpoint.rotation;

    return setpoint;
}

/**
 * @brief Sets the robot controller setpoint.
 *
 * @param setpoint The setpoint
 */
void Robot::setSetpoint(Setpoint setpoint)
{
    this->setpoint = setpoint;

    vector<char> payload(12);

    *((float *)&payload[0]) = setpoint.position.x;
    *((float *)&payload[4]) = setpoint.position.y;
    *((float *)&payload[8]) = setpoint.rotation;

    mqttClient->publish(robotId + "/pid/setpoint/set", payload);
}

/**
 * @brief Lifts the robot to a destination coordinate
 *
 * @param destination The destination coordinate (x: left-right, y: up-down, z: forward-back)
 */
void Robot::liftTo(Vector3 destination)
{
    vector<char> payload(12);

    *((float *)&payload[0]) = destination.x;
    *((float *)&payload[4]) = destination.y;
    *((float *)&payload[8]) = destination.z;

    mqttClient->publish("hook/" + robotId + "/cmd", payload);
}

/**
 * @brief Sets image on the display
 *
 * @param imageIndex The index of the image (see RobotImages.png)
 */
void Robot::setDisplay(int imageIndex)
{
    Rectangle selectRectangle = {16.0F * imageIndex, 0, 16, 16};
    Image selectedImage = ImageFromImage(displayImages, selectRectangle);

    const int dataSize = 16 * 16 * 3;
    vector<char> payload(dataSize);
    memcpy(payload.data(), selectedImage.data, dataSize);

    UnloadImage(selectedImage);

    mqttClient->publish(robotId + "/display/lcd/set", payload);
}

/**
 * @brief Set robot eyes.
 *
 * @param leftEye Left eye color
 * @param rightEye Right eye color.
 */
void Robot::setEyes(Color leftEye, Color rightEye)
{
    vector<char> payload(3);
    payload[0] = leftEye.r;
    payload[1] = leftEye.g;
    payload[2] = leftEye.b;
    mqttClient->publish(robotId + "/display/leftEye/set", payload);

    payload[0] = rightEye.r;
    payload[1] = rightEye.g;
    payload[2] = rightEye.b;
    mqttClient->publish(robotId + "/display/rightEye/set", payload);
}


void Robot::updateSetpoint(float velocity, float deltatime)
{
    float distance = velocity * deltatime;

    Setpoint destinationSetPoint = getSetpoint(targetMapPosition);

    Vector2 deltaDistance = Vector2Subtract(destinationSetPoint.position, setpoint.position);

    setpoint.position = Vector2Add(setpoint.position, Vector2Scale(Vector2Normalize(deltaDistance), distance) );

    Vector2 currentMapPosition = getMapPosition(setpoint);
    
    if((abs(targetMapPosition.x - currentMapPosition.x) < DISTANCE) && 
        (abs(targetMapPosition.y - currentMapPosition.y) < DISTANCE))
    {
        setpoint.rotation = (float)((targetMapRotation - 1) * 90);
    }
}

/**
 * @brief Get the target map position
 * 
 * @return Vector2 : Map position
 */
Vector2 Robot::getRobotTargetMapPosition()
{
    return targetMapPosition;
}

/**
 * @brief Get the target map rotation
 * 
 * @return Direction : Map direction
 */
Direction Robot::getRobotTargetMapDirection()
{
    return targetMapRotation;
}

/**
 * @brief Get the current setpoint of the robot
 * 
 * @return Setpoint : Robot position and rotation
 */
Setpoint Robot::getRobotSetpoint()
{
    return setpoint;
}

Vector2 Robot::getRobotCurrentMapPosition()
{
    return getMapPosition(setpoint);
}