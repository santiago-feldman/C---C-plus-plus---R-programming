/**
 * EDA-Man
 *
 * @copyright Copyright (C) 2022
 * @author Marc S. Ressl
 *
 * @brief Controls an EDA-Man game.
 */

/**
 * @author Solari Agustin
 *         Viola Santiago
 *         Fisher Agustin
 *         Feldmann Santiago
 * 
 * @brief Controll the Playable Robot in the game
 * @version 0.1
 * @date 2022-05-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef PLAYER
#define PLAYER


#include "Robot.h"

class EDAMan: public Robot
{
public:
    void start(GameModel* gameModel, MQTTClient *mqttClient);
    void update(float deltaTime);
    void moveRobot();   
    void restart();      
 
private:
    void updateImage();
    int keyPressed;
};

#endif