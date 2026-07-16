/**
 * @file Controller.h
 * @author Cristian Meichtry, Candela Gioia Perez, Juan Martin Rodriguez,
 *         Albertina Galan, Santiago Feldman
 * @brief Modulo controlador de los robots
 * @version 0.1
 * @date 2022-05-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef  CONTROLLER_H
#define  CONTROLLER_H

#include "MQTTClient2.h"
#include "Robot.h"
#include <array>

#define CANT_PLAYERS 6
using namespace std;

class Controller: public MQTTListener
{
public: 
    /**
     * @brief Construye un controlador
     * 
     * @param client el cliente MQTT
     */
    Controller(MQTTClient2* client);
    /**
     * @brief Destruye el controlador
     * 
     */
    ~Controller();
    /**
     * @brief Recibe e interpreta los mensajes MQTT para gestionar el juego
     * 
     * @param topic 
     * @param payload 
     */
    void onMessage(std::string topic, std::vector<char> payload);

private:
    MQTTClient2* client;
    Vector3 ballVelocity;
    Vector3 ballPosition;
    int kickOff;
    int preKickOff;
    int freeKick;
    int preFreeKick;
    int penaltyKick;
    int prePenaltyKick;
    bool pause;
    int playersInGame1;
    int playersInGame2;
    vector < Robot*> robotsTeam1;
    array<Vector3,CANT_PLAYERS> positionTeam2;
    array<Vector3, CANT_PLAYERS> velocityTeam2;
    array<Vector3, CANT_PLAYERS> rotationTeam2;
    array<Vector3, CANT_PLAYERS> angularVelocityTeam2;
    const Vector2 rightGoal = {4.5, 0};
    const Vector2 leftGoal = { -4.5, 0 };

    /**
     * @brief Interpreta todos los mensajes relativos al juego
     * 
     * @param payload valor del mensaje
     * @param index indice del mensaje
     */
    void messageGame(vector<char> payload, int index);
    /**
     * @brief Interpreta todos los mensajes relativos a los robots
     * 
     * @param payload valor del mensaje
     * @param topic mensaje
     */
    void messageRobot (vector<char> payload, string topic);

    /**
     * @brief Agrega un robot a la defensa
     * 
     */
    void addPlayerDefense();
    /**
     * @brief Agrega un robot al ataque
     * 
     */
    void addPlayerLeading();
    /**
     * @brief Agrega un robot arquero
     * 
     */
    void addPlayerGoalie();

    /**
     * @brief Convierte un mensaje de vector al tipo de dato requerido
     * 
     * @tparam T el tipo de dato requerido
     * @param vector el vector a convertir
     * @return T 
     */
    template <typename T>
    T convertMessage(std::vector<char>& vector)
    {
        void* pt = vector.data();
        return (*(T*)pt);
    }
};
#endif // CONTROLLER_H 