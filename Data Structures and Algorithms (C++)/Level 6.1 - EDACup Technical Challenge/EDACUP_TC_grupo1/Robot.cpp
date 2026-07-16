/**
 * @file Robot.cpp
 * @author Cristian Meichtry, Candela Gioia Perez, Juan Martin Rodriguez,
 *         Albertina Galan, Santiago Feldman
 * @brief Definicion del funcionamiento de los robots
 * @version 0.1
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

Robot::Robot(MQTTClient2* client, int number) 
{
    numberPlayer = number;
    numberPlayerString = to_string(numberPlayer);
    topics = {
        "robot1." + numberPlayerString + "/motion/state",
        "robot1." + numberPlayerString + "/power/powerConsumption",
        "robot1." + numberPlayerString + "/power/batteryLevel",
        "robot1." + numberPlayerString + "/pid/parameters/set",
        "robot1." + numberPlayerString + "/pid/setpoint/set",
        "robot1." + numberPlayerString + "/dribbler/voltage/set",
        "robot1." + numberPlayerString + "/kicker/chargeVoltage/set",
        "robot1." + numberPlayerString + "/kicker/kick/cmd",
        "robot1." + numberPlayerString +"/display/lcd/set",
        "robot1." + numberPlayerString + "/display/leftEye/set",
        "robot1." + numberPlayerString + "/display/rightEye/set",
        "robot1." + numberPlayerString + "/kicker/chip/cmd"
    };

    this->client = client;  

    for (int i = 1; i <= 4; i++) 
    {
        client->subscribe(MOTOR_GET(i, "voltage"));
        client->subscribe(MOTOR_GET(i, "current"));
        client->subscribe(MOTOR_GET(i, "rpm"));
        client->subscribe(MOTOR_GET(i, "temperature"));
    }

    string camiseta =  "../camisetas/camiseta1.png";
    displayImage = LoadImage(camiseta.c_str());
    setDisplay();
    parameters =  { 20, 0, 20, 0.01, 0, 0.003};
    publishData(topics[3], parameters);
    chargeKicker();

}

Robot::~Robot() 
{
    UnloadImage(displayImage);
}

void Robot::movement(float x,  float z) 
{
    float angle = angleDirection(x,z);
    vector<float> posicion = { x ,z , angle };
    publishData(topics[4], posicion);
}

void Robot::rotate(float x, float z)
{
    float angle = angleDirection(x, z);
    vector<float> posicion = { position.x, position.z, angle };
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


void Robot::setDribbler(Vector3 ballPosition)
{
    if(Vector3Distance(ballPosition, position) <= 0.3f)
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
    vector<float> payload = { 200.0f };
    publishData(topics[6], payload);
}

void Robot::fireKicker()
{
    vector<float> payload = { 1.0f };
    publishData(topics[7], payload);
    chargeKicker();
}

void Robot::fireChipper()
{
    vector<float> payload = { 1.0f };
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