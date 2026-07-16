/**
 * @file main.cpp
 * @author Cristian Meichtry, Candela Gioia Perez, Juan Martin Rodriguez,
 *         Albertina Galan, Santiago Feldman
 * @brief Modulo principal
 * @version 0.1
 * @date 2022-05-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "MQTTClient2.h"
#include "Controller.h"

int main ()
{
    MQTTClient2 client;
    Controller control(&client);
    client.setListener(&control);
    client.run();
    return 0;
}