/**
 * @file Controller.h
 * @author Cristian Meichtry, Candela Gioia Perez, Juan Martin Rodriguez,
 *         Albertina Galan, Santiago Feldman
 * @brief Modulo controlador de los robots
 * @version 1.1
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

class Controller : public MQTTListener
{
public:
    /**
     * @brief Construye un controlador
     *
     * @param client el cliente MQTT
     */
    Controller(MQTTClient2* client, int team);
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
    int team;
    int teamMultiplier;
    MQTTClient2* client;
    Vector3 ballVelocity;
    Vector3 ballPosition;
    uint8_t kickOff;
    uint8_t preKickOff;
    uint8_t freeKick;
    uint8_t preFreeKick;
    uint8_t  penaltyKick;
    uint8_t prePenaltyKick;
    bool pause;
    int playersInGame1;
    bool removedRobot[6];
    vector < Robot*> robotsTeam1;
    array<Vector3, CANT_PLAYERS> positionTeam2;
    array<Vector3, CANT_PLAYERS> velocityTeam2;
    array<Vector3, CANT_PLAYERS> rotationTeam2;
    array<Vector3, CANT_PLAYERS> angularVelocityTeam2;
    const Vector2 rightGoal = { 4.5, 0 };
    const Vector2 leftGoal = { -4.5, 0 };
    Vector2 attackGoal;

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
    void messageAboutRobot(vector<char> payload, string topic);

    /**
     * @brief Agrega un robot al ataque
     *
     */
    void addPlayer(int number, int team);
    /**
     * @brief Agrega un robot arquero
     *
     */
    void addPlayerGoalie(int number, int team);

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

    /**
     * @brief Implementa la estrategia de juego
     * 
     */
    void play();
    /**
     * @brief Se posicionan antes del inicio del juego
     * 
     */
    void preKickOffPositions();
    /**
     * @brief Implementa el saque de mitad de cancha
     * 
     */
    void kickOffSet();
    /**
     * @brief Saca a un robot si sacaron tarjeta
     * 
     */
    void removeRobot();
    /**
     * @brief Vuelve a entrar al robot si expiro la tarjeta
     * 
     */
    void addRobot();
    /**
     * @brief Se posiciona para un tiro libre
     * 
     */
    void preFreeKickSet();
    /**
     * @brief Se posiciona para un penal
     * 
     */
    void prePenaltyKickSet();
    /**
     * @brief Implementa un penal
     * 
     */
    void kickSet();
};
#endif // CONTROLLER_H 