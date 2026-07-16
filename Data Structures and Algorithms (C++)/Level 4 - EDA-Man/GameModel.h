/**
 * @file GameModel.h
 * @author Marc S. Ressl
 * @brief EDA-Man game model
 * @version 0.1
 * @date 2022-04-12
 *
 * @copyright Copyright (c) 2022
 *
 */

/**
 * @author Solari Agustin
 *         Viola Santiago
 *         Fisher Agustin
 *         Feldmann Santiago
 *
 * @version 0.1
 * @date 2022-05-03
 *
 * @copyright Copyright (c) 2022
 */

#ifndef _GAMEMODEL_H
#define _GAMEMODEL_H

class Robot;

/**
 * @brief GameState status
 */
enum GameState
{
    GameStart,
    GamePlaying,
    GamePause,
    GameFinish,
};

/**
 * @brief GameMode status
 */
enum GhostMode
{
    Dispersion,
    Chase,
    Blue,
};

#include <string>
#include <list>
#include <vector>
#include <raylib.h>
#include <unordered_set>
#include <map>

#include "MQTTClient.h"
#include "GameView.h"
#include "Robot.h"

using namespace std;

class GameModel
{
public:
    GameModel(MQTTClient *mqttClient);
    ~GameModel();

    void start(std::string maze);
    void addRobot(Robot *robot);
    void update(float deltaTime);
    bool checkColision(void);

    // Seters
    void setKeyPress(int keyPressed);
    void setGameView(GameView *gameView);
    void setGameMode(GhostMode gameMode);
    void setGameState(GameState gameState);

    // Geters
    int getLastKeyPressed();
    GhostMode getGameMode(void);
    float getGameTime(void);
    Robot *getRobot(int);
    GameState getGameState(void);
    int getScore(void);

    bool isTileFree(Vector2 position);
    bool isTileEnergizer(Vector2 position);

    float pauseTime;

private:
    MQTTClient *mqttClient;
    GameView *gameView;

    std::string maze;
    std::vector<Robot *> robots;
    std::list<int> eatenFruits;
    std::vector<Vector2> delTiles;

    GameState gameState;
    GhostMode ghostMode;

    // Private Information
    float gameStateTime;
    int remainingDots;
    int remainingEnergizers;
    int lives;
    int keyPressed;
    int gameScore;
};

#endif