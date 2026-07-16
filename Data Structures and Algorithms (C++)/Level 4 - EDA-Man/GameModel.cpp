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
 * @brief Controll the principal function of the game
 * @version 0.1
 * @date 2022-05-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include <vector>

#include "GameModel.h"

using namespace std;

#define MAZE_WIDTH 28
#define MAZE_HEIGHT 36
#define MAZE_SIZE (MAZE_WIDTH * MAZE_HEIGHT)
#define MIN_DISTANCE 0.75f

/**
 * @brief Construct a new Game Model:: Game Model object
 *
 * @param mqttClient An MQTTClient object
 */
GameModel::GameModel(MQTTClient *mqttClient)
{
    this->mqttClient = mqttClient;
    gameScore = 0; 
}

GameModel::~GameModel()
{
    for (auto robot : robots)
    {
        delete robot;
    }
};

/**
 * @brief Setter for the GameView.
 *
 * @param gameView A GameView object
 */
void GameModel::setGameView(GameView *gameView)
{
    this->gameView = gameView;
}

/**
 * @brief Adds a robot to the game model.
 *
 * @param robot The robot
 */
void GameModel::addRobot(Robot *robot)
{
    robots.push_back(robot);
}

/**
 * @brief Resets game model to initial game conditions.
 *
 * @param maze A maze
 */
void GameModel::start(string maze)
{
    this->maze = maze;
    this->maze.resize(MAZE_SIZE);

    for (auto c : maze)
    {
        if (c == '+')
            remainingDots++;
        else if (c == '*')
            remainingEnergizers++;
    }

    gameView->start(maze);

    lives = 4;
    eatenFruits.clear();

    gameState = GameStart;
    gameStateTime = 0;
    ghostMode = Chase;

    gameView->setMessage(GameViewMessageReady);
    gameView->setLives(lives);
    gameView->setEatenFruits(eatenFruits);

    for (auto robot : robots)
        robot->start(this, mqttClient);

    // Just for testing
    gameView->playAudio("mainStart");
}

/**
 * @brief Updates game model for current frame.
 *
 * @param deltaTime Number of seconds since the last frame
 */
void GameModel::update(float deltaTime)
{

    Vector2 edaManPos = getRobot(0)->getRobotCurrentMapPosition();
    Vector2 edaManNTile = getRobot(0)->getRobotTargetMapPosition();

    bool isTileOld = false;

    for (auto i : delTiles)
    {
        if (abs(Vector2Distance(edaManPos, i) < DISTANCE))
        {
            isTileOld = true;
        }
    }
    if (!isTileOld && abs(Vector2Distance(edaManPos, edaManNTile) < DISTANCE))
    {
        delTiles.push_back(edaManPos);

        if (delTiles.size() == 244)
        {
            gameState = GameFinish;
        }

        gameView->clearDot((edaManPos.x), (edaManPos.y));

        if (isTileEnergizer(edaManPos))
        {
            setGameMode(Blue);
            gameStateTime = 0;
            gameScore += 50;
        }
        else
        {
            gameScore += 10;
        }

        gameView->setScore(gameScore);

    }

    if (gameState == GamePlaying)
    {
        gameStateTime += deltaTime;

        if (ghostMode == Blue)
        {
            if (gameStateTime > 7.0f)
            {
                setGameMode(Chase);
            }
        }
        else // Dispersion or Chase
        {
            if ((gameStateTime > 0.0f) && (gameStateTime < 4.0f))
            {
                setGameMode(Dispersion);
            }
            else if ((gameStateTime >= 4.0f) && (gameStateTime < 25.0f))
            {
                setGameMode(Chase); // puede ser que solo coman en modo
            }
            else
            {
                gameStateTime = 0.0f;
            }
        }

        if (!checkColision())
        {
            gameView->clearDot((getRobot(0)->getRobotCurrentMapPosition().x), (getRobot(0)->getRobotCurrentMapPosition().y));
            for (auto robot : robots)
            {
                robot->update(deltaTime);
            }
        }
        else // There is a colision, we restart the game
        {
            if (lives >= 1)
            {
                if (getGameMode() != Blue)
                {
                    lives--;
                    gameView->setLives(lives);

                    for (auto robot : robots)
                    {
                        robot->restart();
                    }
                }
            }
            else
            {
                gameState = GameFinish;
            }
        }
    }
}

/**
 * @brief Determine if a tile is free.
 *
 * @param targetMapPosition A tile coordinate
 * @return true Tile is free
 * @return false Tile is not free
 */
bool GameModel::isTileFree(Vector2 tilePosition)
{
    if ((tilePosition.x < 0) || (tilePosition.x >= MAZE_WIDTH))
        return false;

    if ((tilePosition.y < 0) || (tilePosition.y >= MAZE_HEIGHT))
        return false;

    char tile = maze[(int)tilePosition.y * MAZE_WIDTH + (int)tilePosition.x];

    return (tile == ' ') || (tile == '+') || (tile == '#');
}

/**
 * @brief Return the game mode status
 *
 * @return GameMode: GameMode status
 */
GhostMode GameModel::getGameMode()
{
    return ghostMode;
}

/**
 * @brief Return a pointer to the robot object
 *
 * @param i : Numer of the robot
 * @return Robot* : Pointer to the robot
 */
Robot *GameModel::getRobot(int i)
{
    return robots[i];
}
/**
 * @brief Return the last key pressed in the game
 *
 * @return int : Key
 */
int GameModel::getLastKeyPressed()
{
    return keyPressed;
}

/**
 * @brief Return the gameTime since the start
 *
 * @return float : Time
 */
float GameModel::getGameTime(void)
{
    return gameStateTime;
}

/**
 * @brief Set the current key press
 *
 * @param keyPressed : Key press
 */
void GameModel::setKeyPress(int keyPressed)
{
    this->keyPressed = keyPressed;
}

/**
 * @brief Set the game mode into:
 *
 * @param gameMode
 */
void GameModel::setGameMode(GhostMode gameMode)
{
    this->ghostMode = gameMode;
}

/**
 * @brief Check if the mapPosition where teh robot is, is a Energizer
 * 
 * @param position 
 * @return true : Position is a Energizer
 * @return false : Position isn't a Energizer
 */
bool GameModel::isTileEnergizer(Vector2 position)
{
    if (
        (abs(Vector2Distance(position, {26.5f, 26.5f})) < DISTANCE) ||
        (abs(Vector2Distance(position, {26.5f, 6.5f})) < DISTANCE) ||
        (abs(Vector2Distance(position, {1.5f, 6.5f})) < DISTANCE) ||
        (abs(Vector2Distance(position, {1.5f, 26.5f})) < DISTANCE))
    {
        return true;
    }
    return false; // sisi
}
/**
 * @brief Return the current gameState
 *
 * @return int : Enum of the gameState
 */
GameState GameModel::getGameState(void)
{
    return gameState;
}

/**
 * @brief Set the gameState
 *
 * @param gameState : Game state from the enum GameState
 */
void GameModel::setGameState(GameState gameState)
{
    this->gameState = gameState;
}

/**
 * @brief Check if the EDAMan has colied with a ghost
 *
 * @return true : Colision
 * @return false : No colision
 */
bool GameModel::checkColision(void)
{
    static int counter;
    Vector2 mapPositionEDAMan = getRobot(0)->getMapPosition(getRobot(0)->getRobotSetpoint());

    for (int i = 1; i <= robots.size() - 1; i++)
    {
        Vector2 mapPositionGhost = getRobot(i)->getMapPosition(getRobot(i)->getRobotSetpoint());
        if (abs(Vector2Distance(mapPositionEDAMan, mapPositionGhost)) < MIN_DISTANCE)
        {
            gameState = GamePause;
            gameStateTime = 0;
            pauseTime = 0;

            if (getGameMode() != Blue)
            {
                counter = 1;
            }

            if (getGameMode() == Blue)
            {
                switch (counter)
                {
                case 1:
                    gameScore += 100;
                    break;
                case 2:
                    gameScore += 500;
                    break;
                case 3:
                    gameScore += 1500;
                    break;
                case 4:
                    gameScore += 2500;
                    break;
                default:
                    counter = 1;
                    break;
                }

                getRobot(i)->restart();
                counter++;
            }
            return true;
        }
    }

    return false;
}

/**
 * @brief Get the current score
 *
 * @return int : score
 */
int GameModel::getScore()
{
    return gameScore;
}