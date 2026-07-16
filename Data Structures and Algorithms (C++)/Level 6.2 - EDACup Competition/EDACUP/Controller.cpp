/**
 * @file Controller.cpp
 * @author Cristian Meichtry, Candela Gioia Perez, Juan Martin Rodriguez,
 *         Albertina Galan, Santiago Feldman
 * @brief Modulo controlador de los robots
 * @version 1.1
 * @date 2022-05-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "MQTTClient2.h"
#include "Controller.h"
#include "Goalie.h"
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


Controller:: Controller (MQTTClient2* client, int team)
{
    this->team = team;

    playersInGame1 = CANT_PLAYERS;

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

    addPlayer(1, team);
    addPlayer(2, team);
    addPlayer(3, team);
    addPlayer(4, team);
    addPlayer(5, team);
    addPlayerGoalie(6, team);

    if(team == 1)
    {
        attackGoal = {4.5,0};
        teamMultiplier = -1;
    }    
    else
    { 
        attackGoal = {-4.5,0};
        teamMultiplier = 1;
    }

    for (auto i : removedRobot)
        i = false;

    preKickOff = 0;
    kickOff = 0;
    prePenaltyKick = 0;
    penaltyKick = 0;
    freeKick = 0;
    preFreeKick = 0;
    pause = true;
  
    preKickOffPositions();
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
        messageAboutRobot(payload, topic);
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

    if(!pause)
        play();
}

void Controller:: messageAboutRobot(vector<char> payload, string topic)
{
    string teamString = to_string(team);

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
    
    if( topic[5] == teamString[0])
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
            preKickOff = convertMessage<uint8_t>(payload);
            preKickOffPositions();            
            break;
        case KICK_OFF:
            kickOff = convertMessage<uint8_t>(payload);
            kickSet();
            break;
        case PRE_FREE_KICK:
            preFreeKick = convertMessage<uint8_t>(payload);
            preFreeKickSet();
            break;
        case FREE_KICK:
            freeKick = convertMessage<uint8_t>(payload);
            kickSet();
            break;
        case PRE_PENAL_KICK:
            prePenaltyKick = convertMessage<uint8_t>(payload);
            prePenaltyKickSet();
            break;
        case PENALTY_KICK:
            penaltyKick = convertMessage<uint8_t>(payload);
            kickSet();
            break;
        case PAUSE:
            pause = true;
            preKickOffPositions();
            robotsTeam1[0]->setDribbler(ballPosition, false);
            break;
        case CONTINUE:
            pause = false;
            play();
            break;
        case REMOVE_ROBOT:
            if (convertMessage<uint8_t>(payload) == (uint8_t)team)
            {
                playersInGame1--;
                removeRobot();
            }
            break;
        case ADD_ROBOT:
            if (convertMessage<uint8_t>(payload) == (uint8_t)team)
            { 
                playersInGame1++;
                addRobot();
            }            
            break;
        default:           
            break;
    }
}

void Controller::addPlayer(int number, int team) 
{
    robotsTeam1.push_back(new Robot(client, number, team));
}

void Controller::addPlayerGoalie(int number, int team)
{
    robotsTeam1.push_back(new Goalie(client, number, team));
}

void Controller::removeRobot()
{
    static int i = 1;
  
    if (playersInGame1 == 0)
    { 
        removedRobot[0] = true;
        i = 0;
    }
    robotsTeam1[i]->movement(0 + i * 0.5, 3.5);
    removedRobot[i++] = true;
    if (i == 5)
        i= 1;    
}

void Controller::addRobot()
{
    for (int i = 0; i < CANT_PLAYERS; i++)
    {
        if (removedRobot[i])
        { 
            removedRobot[i] = false;
            switch (i)
            {
            case 0:
                robotsTeam1[0]->movement(0.7 * teamMultiplier, 0);
                break;
            case 1:
                robotsTeam1[1]->movement(3.3 * teamMultiplier, 1.5);
                break;
            case 2:
                robotsTeam1[2]->movement(2.5 * teamMultiplier, 0.5);
                break;
            case 3:
                robotsTeam1[3]->movement(2.5 * teamMultiplier, -0.5);
                break;
            case 4:
                robotsTeam1[4]->movement(3.3 * teamMultiplier, -1.5);
                break;
            case 5:
                robotsTeam1[5]->defendGoal(ballPosition);
                break;
            default:
                break;
            }
            break;
        }
    }
}

void Controller::play()
{
    robotsTeam1[0]->setDribbler(ballPosition, true);

    if ((Vector3Distance(ballPosition, robotsTeam1[0]->position)) > 0.1115)
        robotsTeam1[0]->movement(ballPosition.x, ballPosition.z);  

    if ((Vector3Distance(ballPosition, robotsTeam1[0]->position)) < 0.1115)
    {
        robotsTeam1[0]->rotate(attackGoal.x , attackGoal.y + 0.3);
        //Apunta al arco y patea 
        if (abs(robotsTeam1[0]->rotation.y
            - robotsTeam1[0]->angleDirection(attackGoal.x, attackGoal.y + 0.3)) < 0.4)
        {
            robotsTeam1[0]->fireKicker();
        }
    }

    //El arquero defiende
    robotsTeam1[5]->defendGoal(ballPosition);
}

void Controller::preKickOffPositions()
{
    robotsTeam1[0]->movement(teamMultiplier * 0.7, 0);
    robotsTeam1[1]->movement(teamMultiplier * 3.3, 1.5);
    robotsTeam1[2]->movement(teamMultiplier * 2.5, 0.5);
    robotsTeam1[3]->movement(teamMultiplier * 2.5, -0.5);
    robotsTeam1[4]->movement(teamMultiplier * 3.3,-1.5);
    robotsTeam1[5]->defendGoal(ballPosition);
}

void Controller::preFreeKickSet()
{
    if (preFreeKick != team)
    {
        robotsTeam1[0]->movement(2.5 * teamMultiplier, 0.6);
        robotsTeam1[1]->movement(2.5 * teamMultiplier, 0.2);
        robotsTeam1[2]->movement(2.5 * teamMultiplier, 0.0);
        robotsTeam1[3]->movement(2.5 * teamMultiplier, -0.2);
        robotsTeam1[4]->movement(2.5 * teamMultiplier, -0.6);
    }
    else
        robotsTeam1[0]->movement(ballPosition.x - 0.1, ballPosition.z - 0.1);
}

void Controller::kickSet()
{
    if ((penaltyKick == team) || (kickOff == team) || (freeKick == team))
        play();

    pause = false;
}

void Controller::prePenaltyKickSet()
{
    if (prePenaltyKick == team)
    {
        robotsTeam1[1]->movement(0, 2.5);
        robotsTeam1[2]->movement(0, 2.0);
        robotsTeam1[3]->movement(0, -2.5);
        robotsTeam1[4]->movement(0, -2);
        robotsTeam1[0]->movement(ballPosition.x - 0.1, ballPosition.z - 0.1);
    }
    else
    {
        robotsTeam1[0]->movement(-4.3 * teamMultiplier, 2.5);
        robotsTeam1[1]->movement(-4.3 * teamMultiplier, 2.0);
        robotsTeam1[2]->movement(-4.3 * teamMultiplier, 1.5);
        robotsTeam1[3]->movement(-4.3 * teamMultiplier, -2.0);
        robotsTeam1[4]->movement(-4.3 * teamMultiplier, -2.5);
    }
}