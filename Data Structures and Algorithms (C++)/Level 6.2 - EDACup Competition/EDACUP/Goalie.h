/**
 * @file Goalie.h
 * @author Cristian Meichtry, Candela Gioia Perez, Juan Martin Rodriguez,
 *         Albertina Galan, Santiago Feldman
 * @brief Robot arquero
 * @version 1.1
 * @date 2022-05-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef GOALIE_H
#define GOALIE_H

#include "Robot.h"

class Goalie : public Robot
{
public:
    /**
     * @brief Constuye un robot arquero
     * 
     * @param client MQTTclient
     * @param number numero de robot en el equipo
     * @param team numero del equipo
     */
    Goalie(MQTTClient2* client, int number, int team);
    /**
     * @brief Destruye al robot arquero
     * 
     */
    ~Goalie();

    /**
     * @brief Defiende el arco de su equipo
     * 
     * @param ballPosition posicion de la pelota
     */
    void defendGoal(Vector3 ballPosition);

private:
    MQTTClient2* client;
    int numberPlayer;
    Vector3 goalCoords;
    int team;
};

#endif //GOALIE_H
