/**
 * @file main.cpp
 * @author Cristian Meichtry, Candela Gioia Perez, Juan Martin Rodriguez,
 *         Albertina Galan, Santiago Feldman
 * @brief Modulo principal
 * @version 1.1
 * @date 2022-05-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>

#include "MQTTClient2.h"
#include "Controller.h"

using namespace std;

int main (int argc, char **argv)
{
    //Introducir el numero de equipo
    int team = 0;
    if(argc > 1)
    {
        if(*argv[1] == '1')
            team = 1;
        else if (*argv[1] == '2')
            team = 2;
        else
        {
            cout << "El numero de equipo es invalido." << endl;
            return 1;
        }
    }
    if ((team == 1) || (team == 2))
    {
        MQTTClient2 client;
        Controller control(&client, team);
        client.setListener(&control);
        client.run();
    }
    return 0;
}