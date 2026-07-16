/**
 * Robot base class.
 *
 * @copyright Copyright (C) 2022
 * @author Marc S. Ressl
 */

#ifndef _ROBOT_H
#define _ROBOT_H

#include <string>

#include "raylib.h"
#include <raymath.h>
#include "MQTTClient.h"
#include "GameModel.h"

#define DISTANCE 0.05f

class GameModel;
/**
 * @brief Dynamic position information of the robot
 *
 */
struct Setpoint
{
    Vector2 position;
    float rotation;
};

/**
 * @brief Dynamic rotation information of the robot
 *
 */
enum Direction
{
    DirectionNone,
    DirectionDown,
    DirectionRight,
    DirectionLeft,
    DirectionUp
};

class Robot
{
public:
    Robot();
    virtual ~Robot();

    virtual void start(GameModel *gameModel, MQTTClient *mqttClient);// = 0;
    virtual void update(float deltaTime) = 0;
    virtual void restart(void) = 0;

    Vector2 getRobotTargetMapPosition();
    Vector2 getRobotCurrentMapPosition();
    Direction getRobotTargetMapDirection();
    Setpoint getRobotSetpoint();
    Vector2 getMapPosition(Setpoint setpoint);
    Setpoint getSetpoint(Vector2 targetMapPosition);

protected:
    MQTTClient *mqttClient;
    GameModel *gameModel;
    std::string robotId;

    Image displayImages;

    Vector2 targetMapPosition;   // Position target
    Direction targetMapRotation; // Rotation target

    Setpoint setpoint; // Dynamic robot position

    bool isMoving; // Flag of the move to the robot

    int currentImageIndex;
    int imageIndex;
    float lastImageTime;

   


    void setSetpoint(Setpoint setpoint);
    void liftTo(Vector3 destination);
    void setDisplay(int imageIndex);
    void setEyes(Color leftEye, Color rightEye);
    void updateSetpoint(float velocity, float deltatime);
    virtual void updateImage() = 0;

};

#endif // ROBOT_H