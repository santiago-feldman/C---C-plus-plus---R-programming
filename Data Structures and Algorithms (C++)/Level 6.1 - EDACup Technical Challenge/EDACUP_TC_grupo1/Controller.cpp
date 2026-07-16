/**
 * @file Controller.cpp
 * @author Cristian Meichtry, Candela Gioia Perez, Juan Martin Rodriguez,
 *         Albertina Galan, Santiago Feldman
 * @brief Modulo controlador de los robots
 * @version 0.1
 * @date 2022-05-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "MQTTClient2.h"
#include "Controller.h"
#include <array>
#include <iostream>
#include <raymath.h>

enum mensajes{
    STATE=0,
    PRE_KICK_OFF,
    KICK_OFF,
    PRE_FREE_KICK,
    FREE_KICK,
    PRE_PENAL_KICK,
    PENALTY_KICK, 
    PAUSE,
    CONTINUE,
    REMOVE_ROBOT,
    ADD_ROBOT
};

const array<string, 11> topics = {
    "ball/motion/state",
    "edacup/preKickOff",
    "edacup/kickOff",
    "edacup/preFreeKick",
    "edacup/freeKick",
    "edacup/prePenaltyKick",
    "edacup/penaltyKick",
    "edacup/pause",
    "edacup/continue",
    "edacup/removeRobot",
    "edacup/addRobot",
};


Controller:: Controller (MQTTClient2* client)
{
    playersInGame1 = CANT_PLAYERS;
    playersInGame2 = CANT_PLAYERS;
    robotsTeam1.reserve(CANT_PLAYERS);
    
    this->client = client;
    this->client->connect("Controller", "127.0.0.1", 1883,  "user","vdivEMMN3SQWX2Ez");
    
    for (auto &i : topics)
       this->client->subscribe(i);

    for (int i = 1; i <= 6; i++)
    {
        this->client->subscribe("robot1." + to_string(i) +"/motion/state");
        this->client->subscribe("robot2." + to_string(i) +"/motion/state");
    }
    this->client->subscribe("*");

    for (int i = 0; i < CANT_PLAYERS; i++)
    {
        addPlayerGoalie();
    }
}

Controller:: ~Controller()
{
    for (auto robot : robotsTeam1)
        delete robot;
}

void Controller::onMessage(std::string topic, std::vector<char> payload)
{

    //Mensajes robot
    if(topic.substr(0,5) == "robot") 
    { 
        messageRobot(payload, topic);
    }   
    //Mesajes juegos
    else                            
    { 
        int index=-1;
        for (int i = 0; i< topics.size(); i++)
        {
            if((topics[i]) == topic)
                index = i;         
        }
        messageGame(payload, index);
    }
    robotsTeam1[0]->setDribbler(ballPosition);
    robotsTeam1[0]->movement(ballPosition.x, ballPosition.z);
    if ((Vector3Distance(ballPosition, robotsTeam1[0]->position)) < 0.1115)
    {
        robotsTeam1[0]->rotate(leftGoal.x, leftGoal.y);
        //Apunta al arco y patea 
        if (abs(robotsTeam1[0]->rotation.y 
                - robotsTeam1[0]->angleDirection(leftGoal.x, leftGoal.y)) < 0.4)
        {
            robotsTeam1[0]->fireKicker();
        }
    }
}

void Controller:: messageRobot(vector<char> payload, string topic)
{
    char team = '1';

    Vector3 pos = {*((float*)(&(payload[0]))) , *((float*)(&(payload[4]))) ,  *((float*)(&(payload[8])))};
    Vector3 vel = {*((float*)(&(payload[12]))) , *((float*)(&(payload[16]))) ,  *((float*)(&(payload[20])))};
    Vector3 rot = {*((float*)(&(payload[24]))) , *((float*)(&(payload[28]))) ,  *((float*)(&(payload[32])))};
    Vector3 angVel = {*((float*)(&(payload[36]))) , *((float*)(&(payload[40]))) ,  *((float*)(&(payload[44])))};

    int index = 0;
    for (int i = 1; i<=CANT_PLAYERS; i++)
    {
        if ((topic.substr(7,1) == to_string(i)))
        {
           index=i; 
        }
    }
    
    if( topic[5] == team)
    {
        robotsTeam1[index-1]->setPosition(pos);
        robotsTeam1[index-1]->setVelocity(vel);
        robotsTeam1[index-1]->setRotation(rot);
        robotsTeam1[index-1]->setAngularVelocity(angVel);
    }
    else
    {
        positionTeam2[index-1] = pos;
        velocityTeam2[index-1] = vel;
        rotationTeam2[index-1] = rot;
        angularVelocityTeam2[index-1] = angVel;
    }
}

void Controller:: messageGame(vector<char> payload, int index)
{
    switch (index)
    {
        case STATE:
            ballPosition.x = *((float*)(&(payload[0])));
            ballPosition.y = *((float*)(&(payload[4])));
            ballPosition.z = *((float*)(&(payload[8])));
            ballVelocity.x = *((float*)(&(payload[12])));
            ballVelocity.y = *((float*)(&(payload[16])));
            ballVelocity.z = *((float*)(&(payload[20])));
            break;
        case PRE_KICK_OFF:
            preKickOff = convertMessage<int>(payload);
            break;
        case KICK_OFF:
            kickOff = convertMessage<int>(payload);
            break;
        case PRE_FREE_KICK:
            preFreeKick = convertMessage<int>(payload);
            break;
        case FREE_KICK:
            freeKick = convertMessage<int>(payload);
            break;
        case PRE_PENAL_KICK:
            prePenaltyKick = convertMessage<int>(payload);
            break;
        case PENALTY_KICK:
            penaltyKick = convertMessage<int>(payload);
            break;
        case PAUSE:
            pause = true;
            break;
        case CONTINUE:
            pause = false;
            break;
        case REMOVE_ROBOT:
            if (convertMessage<int>(payload) == 1)   
                playersInGame1--;
            else
                playersInGame2--;
            break;
        case ADD_ROBOT:
            if (convertMessage<int>(payload) == 1)
                playersInGame1++;
            else
                playersInGame2++;
            break;
        default:            
            break;
    }
}

void Controller::addPlayerDefense()
{
    robotsTeam1.push_back(new Robot(client, 1)); 
}

void Controller::addPlayerLeading() 
{
    robotsTeam1.push_back(new Robot(client, 1));
}

void Controller::addPlayerGoalie()
{
    robotsTeam1.push_back(new Robot(client, 1));
}
