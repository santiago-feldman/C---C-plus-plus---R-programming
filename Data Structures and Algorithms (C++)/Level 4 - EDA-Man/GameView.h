/**
 * @file GameView.h
 * @author Marc S. Ressl
 * @brief Controls the EDA-Man views (LED floor and jukebox)
 * @version 0.1
 * @date 2022-04-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _GAMEVIEW_H
#define _GAMEVIEW_H

#include <list>
#include <string>
#include <vector>

#include "MQTTClient.h"

/**
 * @brief A message for the GameView setMessage method.
 * 
 */
enum GameViewMessage
{
    GameViewMessageNone,
    GameViewMessageReady,
    GameViewMessageGameOver,
};

/**
 * Controls the EDA-Man views (LED Floor and Jukebox)
 */
class GameView
{
public:
    GameView(MQTTClient *mqttClient);

    //Inicilize functions
    void start(std::string maze);
    void update(float time);

    //Seters
    void setFruit(int x, int y, int fruitIndex);
    void setMessage(GameViewMessage value);
    void setScore(int value);
    void setHighScore(int value);
    void setLives(int numberOfLives);
    void setEatenFruits(std::list<int> &eatenFruits);
    void setTiles(int x, int y, int palette, std::string s);

    //Clears
    void clearScreen();
    void clearDot(int x, int y);

    //Audio
    void playAudio(std::string audioId);
    void stopAudio(std::string audioId);

private:
    struct Energizer
    {
        int x;
        int y;
    };

    MQTTClient *mqttClient;
    GameViewMessage gameViewMessage;

    std::list<Energizer> energizers;

    float time;
    bool blink1Up;
    bool blinkEnergizers;

};

#endif
