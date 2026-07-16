/**
 * @file Robot.cpp
 * @author Cristian Meichtry, Candela Gioia Perez, Juan Martin Rodriguez,
 *         Albertina Galan, Santiago Feldman
 * @brief Definicion del funcionamiento de los robots
 * @version 1.1
 * @date 2022-05-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "Robot.h"
#include <iostream>
#include <map>
#include <raylib.h>
#include <raymath.h>
#include <string.h>

#define MOTOR_GET(n, s) "robot1/motor" + to_string(n) + "/" + s
#define RADIUSBALL 0.0215f
#define RADIUSROBOT 0.09f
#define DIFERENCE 0.005f
using namespace std;

Robot::Robot(MQTTClient2* client, int number, int team) 
{
    numberPlayer = number;
    numberPlayerString = to_string(numberPlayer);
    numberTeam = to_string(team);
    topics = {
        "robot" + numberTeam + "." + numberPlayerString + "/motion/state",
        "robot" + numberTeam + "." + numberPlayerString + "/power/powerConsumption",
        "robot" + numberTeam + "." + numberPlayerString + "/power/batteryLevel",
        "robot" + numberTeam + "." + numberPlayerString + "/pid/parameters/set",
        "robot" + numberTeam + "." + numberPlayerString + "/pid/setpoint/set",
        "robot" + numberTeam + "." + numberPlayerString + "/dribbler/voltage/set",
        "robot" + numberTeam + "." + numberPlayerString + "/kicker/chargeVoltage/set",
        "robot" + numberTeam + "." + numberPlayerString + "/kicker/kick/cmd",
        "robot" + numberTeam + "." + numberPlayerString + "/display/lcd/set",
        "robot" + numberTeam + "." + numberPlayerString + "/display/leftEye/set",
        "robot" + numberTeam + "." + numberPlayerString + "/display/rightEye/set",
        "robot" + numberTeam + "." + numberPlayerString + "/kicker/chip/cmd"
    };

    this->client = client;  
    this->team = team;
    string camiseta =  "../camisetas/camiseta" + numberPlayerString + ".png";
    displayImage = LoadImage(camiseta.c_str());
    setDisplay();
    parameters = { 5, 0, 10, 0.01, 0, 0.003};
    publishData(topics[3], parameters);
    chargeKicker();
}

Robot::~Robot() 
{
    UnloadImage(displayImage);
}

void Robot::movement(float x,  float z)
{
    bool move = false;
    parameters =  { 5, 0, 10, 0.01, 0, 0.003};
    publishData(topics[3], parameters);
    if (team == 1)
    {
        if (!((x > 3.5) && (z > -1 && z < 1)))
        {
            move = true;
        }
    }
    else if (!((x < -3.5) && (z > -1 && z < 1)))
    {
        move = true;
    }
    if (move == true)
    {
        float angle = angleDirection(x, z);
        vector<float> posicion = {x, z, angle};
        publishData(topics[4], posicion);
    }
}

void Robot::rotate(float x, float z)
{
    float angle = angleDirection(x, z);
    vector<float> posicion = { position.x, position.z, angle};
    publishData(topics[4], posicion);
}

void Robot::publishData(string topic, vector<float> & value)
{
    vector<char> message;
    message.resize(sizeof(float) * value.size());
    memcpy(message.data(), value.data(), sizeof(float) * value.size());
    client->publish(topic, message);
}

float Robot::angleDirection(float x, float z)
{
    float angle = atan((x - position.x) / (z - position.z)) * 180 / PI;
    if (z - position.z < 0)                                //Segundo y tercer cuadrante
    {
        angle += 180;
    }
    else if ((z - position.z) > 0 && (x - position.x) < 0) //Cuarto cuadrante
    {
        angle += 360;
    }
    return angle;
}

void Robot::setDisplay()
{
    ImageFormat(&displayImage, PIXELFORMAT_UNCOMPRESSED_R8G8B8);
    const int dataSize = 16 * 16 * 3;
    vector<char> payload(dataSize);
    memcpy(payload.data(), displayImage.data, dataSize);
    client->publish(topics[8], payload);
}

void Robot::setEyes(Color leftEye, Color rightEye)
{
    vector<char> payload(3);
    payload[0] = leftEye.r;
    payload[1] = leftEye.g;
    payload[2] = leftEye.b;
    client->publish(topics[9], payload);

    payload[0] = rightEye.r;
    payload[1] = rightEye.g;
    payload[2] = rightEye.b;
    client->publish(topics[10], payload);
}

void Robot::setDribbler(Vector3 ballPosition, bool state)
{
    if((Vector3Distance(ballPosition, position) <= 0.3f) && state)
    {
        vector<float> payload = { 1.0f };
        publishData(topics[5], payload);
    }
    else
    {
        vector<float> payload = { 0.0f };
        publishData(topics[5], payload);
    }
}

void Robot::chargeKicker()
{
    vector<float> payload = { 150.0f };
    publishData(topics[6], payload);
}

void Robot::fireKicker()
{
    vector<float> payload = { 0.3f };
    publishData(topics[7], payload);
    chargeKicker();
}

void Robot::fireChipper()
{
    vector<float> payload = { 0.3f };
    publishData(topics[11], payload);
    chargeKicker();
}

void Robot::setPosition(Vector3 position)
{
    this->position = position;
}
void Robot::setVelocity(Vector3 velocity)
{
    this->velocity = velocity;
}
void Robot::setRotation(Vector3 rotation)
{
    this->rotation = rotation;
}
void Robot::setAngularVelocity(Vector3 angularVelocity) 
{
    this->angularVelocity = angularVelocity;
}

void Robot::defendGoal(Vector3 ballPosition)
{

}