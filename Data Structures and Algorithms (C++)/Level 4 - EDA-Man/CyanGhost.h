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
 * @brief Controll the CyanGhost in the game
 * @version 0.1
 * @date 2022-05-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef CYANGHOST_H
#define CYANGHOST_H

#include "Ghost.h"

class CyanGhost : public Ghost
{
public:
    void start(GameModel *gameModel_, MQTTClient *mqttClient_);

private:
    void getPersecutionModeMapPosition();
    void getDispersionModeMapPosition();
    void restart();
};

#endif