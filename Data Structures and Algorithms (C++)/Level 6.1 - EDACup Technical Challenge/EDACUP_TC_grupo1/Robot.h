/**
 * @file Robot.h
 * @author Cristian Meichtry, Candela Gioia Perez, Juan Martin Rodriguez,
 *         Albertina Galan, Santiago Feldman
 * @brief Definicion del funcionamiento de los robots
 * @version 0.1
 * @date 2022-05-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef ROBOT_H
#define ROBOT_H

#include "MQTTClient2.h"
#include "raylib.h"
#include <map>
#include <cmath>
#include <array>

using namespace std;

#define NOMINALCURRENT 1.0f
#define CLOCKWISE to_vector(NOMINALCURRENT)
#define COUNTERCLOCKWISE to_vector(-NOMINALCURRENT)
#define Y_OFFSET 20

class Robot
{
public:
	/**
	 * @brief Construye un nuevo Robot
	 * 
	 * @param client MQTTClient  
	 * @param number el numero de robot
	 */
	Robot(MQTTClient2* client, int number);
	/**
	 * @brief Destruye al Robot
	 * 
	 */
	~Robot();

	/**
	 * @brief Mueve el robot hacia un setpoint
	 * 
	 * @param x Las coordenadas del setpoint
	 * @param z 
	 */
	void movement(float  x, float  z);
	/**
	 * @brief Gira el robot
	 * 
	 * @param x Coordenadas de referencia para la rotacion
	 * @param z 
	 */
	void rotate(float x, float z);

	/**
	 * @brief Coloca la camiseta en el display del Robot
	 * 
	 */
	void setDisplay();
	/**
	 * @brief Setea los ojos del robot
	 * 
	 * @param leftEye el color para cada ojo
	 * @param rightEye 
	 */
	void setEyes(Color leftEye, Color rightEye);

	/**
	 * @brief Setea la posicion del robot
	 * 
	 * @param position 
	 */
	void setPosition( Vector3 position);
	/**
	 * @brief Setea la velocidad
	 * 
	 * @param velocity 
	 */
	void setVelocity( Vector3 velocity);
	/**
	 * @brief Setea la rotacion
	 * 
	 * @param rotation 
	 */
	void setRotation(Vector3 rotation);
	/**
	 * @brief Setea la velocidad angular
	 * 
	 * @param angularVelocity 
	 */
	void setAngularVelocity(Vector3 angularVelocity);

	/**
	 * @brief Enciende el dribbler
	 * 
	 * @param ballPosition solamente si esta en la proximidad de la pelota
	 */
	void setDribbler(Vector3 ballPosition);
	/**
	 * @brief Carga el kicker
	 * 
	 */
	void chargeKicker();
	/**
	 * @brief Dispara el kicker
	 * 
	 */
	void fireKicker();
	/**
	 * @brief Dispara el chipper
	 * 
	 */
	void fireChipper();

	/**
	* @brief Calcula el angulo de movimiento
	*
	* @param x Las referencias respecto a las cuales calcular el angulo
	* @param y
	* @return float
	*/
	float angleDirection(float x, float y);

	Vector3 position;
	Vector3 rotation;
	
private:
	/**
	 * @brief Publica un topic con su valor
	 * 
	 * @param topic 
	 * @param value 
	 */
	void publishData(string topic, vector<float>& value);

	MQTTClient2* client;
	Vector3 velocity;
	Vector3 angularVelocity;
	Image displayImage;
	int numberPlayer;
	string numberPlayerString;
	int isConnected;
	map<string, vector<char>> sensorData;
	vector<string> topics;
	vector<float> parameters;
};
#endif //ROBOT_H