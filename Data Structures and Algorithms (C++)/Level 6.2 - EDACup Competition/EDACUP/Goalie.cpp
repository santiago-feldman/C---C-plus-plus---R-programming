/**
 * @file Goalie.cpp
 * @author Cristian Meichtry, Candela Gioia Perez, Juan Martin Rodriguez,
 *         Albertina Galan, Santiago Feldman
 * @brief Robot arquero
 * @version 1.1
 * @date 2022-05-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "Goalie.h"
#include <raymath.h>

Goalie::Goalie(MQTTClient2* client, int number, int team):
Robot(client, number, team)
{
    this->client = client;
    this->numberPlayer = number;
    this->team = team;
    if(team == 1)
        goalCoords = {-4.5,0,0};
    else 
        goalCoords = {4.5,0,0};

    movement(goalCoords.x, goalCoords.z);
}

Goalie::~Goalie()
{

}

void Goalie::defendGoal(Vector3 ballPosition)
{
    float m;
    Vector3 newCoords = {0.0,0.0,0.0};

    setDribbler(position, true);

    m = ballPosition.z/(ballPosition.x - goalCoords.x);
    if (goalCoords.x < 0)
        newCoords.x = sqrt(1/(1+pow(m,2))) + goalCoords.x;
    else
        newCoords.x = -sqrt(1/(1+pow(m,2))) + goalCoords.x;
    newCoords.z = m * (newCoords.x - goalCoords.x);
    movement(newCoords.x, newCoords.z );

    if (Vector3Distance(position,newCoords) <= 0.01)
        rotate(ballPosition.x, ballPosition.z);

    if (ballPosition.x <= -3.5 && ballPosition.z >= -1 && ballPosition.z <= 1)
        movement(ballPosition.x, ballPosition.z);
}