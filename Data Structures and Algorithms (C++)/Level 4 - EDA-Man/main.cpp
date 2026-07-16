/**
 * EDA-Man
 *
 * @copyright Copyright (C) 2022
 * @author Marc S. Ressl
 *
 * @brief Controls an EDA-Man game.
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <raylib.h>

#include "MQTTClient.h"

#include "GameModel.h"
#include "GameView.h"

#include "EDAMan.h"
#include "RedGhost.h"
#include "OrangeGhost.h"
#include "PinkGhost.h"
#include "CyanGhost.h"

using namespace std;

void finishText(void);
void pauseText(void);
void playText(void);

int main(void)
{
    srand(time(NULL));
    MQTTClient mqttClient("controller");

    const int port = 1883;
    if (!mqttClient.connect("localhost", port, "user", "vdivEMMN3SQWX2Ez"))
    {
        cout << "Could not connect." << endl;
        return 1;
    }

    cout << "Connected." << endl;

    // raylib
    InitWindow(640, 480, "EDA-Man Controller");
    SetTargetFPS(60);

    string maze =
        "                            "
        "                            "
        "                            "
        "jbbbbbbbbbbbbonbbbbbbbbbbbbk"
        "s++++++++++++pq++++++++++++r"
        "s+faag+faaag+pq+faaag+faag+r"
        "s#p  q+p   q+pq+p   q+p  q#r"
        "s+v``w+v```w+vw+v```w+v``w+r"
        "s++++++++++++++++++++++++++r"
        "s+faag+fg+faaaaaag+fg+faag+r"
        "s+v``w+pq+v``ih``w+pq+v``w+r"
        "s++++++pq++++pq++++pq++++++r"
        "zccccg+pxaag pq faayq+fcccc{"
        "     s+ph``w vw v``iq+r     "
        "     s+pq          pq+r     "
        "     s+pq d      e pq+r     "
        "jbbbbw+vw r      s vw+vbbbbk"
        "s     +   r      s   +     r"
        "zccccg+fg r      s fg+fcccc{"
        "     s+pq tbbbbbbu pq+r     "
        "     s+pq          pq+r     "
        "     s+pq faaaaaag pq+r     "
        "jbbbbw+vw v``ih``w vw+vbbbbk"
        "s++++++++++++pq++++++++++++r"
        "s+faag+faaag+pq+faaag+faag+r"
        "s+v`iq+v```w+vw+v```w+ph`w+r"
        "s#++pq+++++++  +++++++pq++#r"
        "|ag+pq+fg+faaaaaag+fg+pq+fa}"
        "l`w+vw+pq+v``ih``w+pq+vw+v`m"
        "s++++++pq++++pq++++pq++++++r"
        "s+faaaayxaag+pq+faayxaaaag+r"
        "s+v````````w+vw+v````````w+r"
        "s++++++++++++++++++++++++++r"
        "zcccccccccccccccccccccccccc{"
        "                            "
        "                            ";

    // Setup
    GameModel gameModel(&mqttClient);
    GameView gameView(&mqttClient);

    gameModel.addRobot(new EDAMan);
    gameModel.addRobot(new RedGhost);
    gameModel.addRobot(new OrangeGhost); 
    gameModel.addRobot(new PinkGhost);
    gameModel.addRobot(new CyanGhost);

    // Configure
    gameModel.setGameView(&gameView);
    gameModel.start(maze);

    while (gameModel.getGameState() != GameFinish && mqttClient.isConnected())
    {
        BeginDrawing();
        EndDrawing();

        if ((IsKeyDown(KEY_UP) || IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_LEFT)) && gameModel.getGameState() != GamePause)
        {
            gameModel.setGameState(GamePlaying);
        }

        if (WindowShouldClose())
        {
            gameModel.setGameState(GameFinish);
        }

        if (gameModel.getGameState() == GamePause)
        {
            pauseText();
            if (gameModel.pauseTime > 3.0f)
            {
                gameModel.setGameState(GamePlaying);
            }
            gameModel.pauseTime += (float)GetFrameTime();
        }

        while (gameModel.getGameState() == GamePlaying)
        {
            if (WindowShouldClose())
            {
                gameModel.setGameState(GameFinish);
            }

            if (IsKeyDown(KEY_P))
            {
                gameModel.setGameState(GamePause);
            }

            float deltaTime = (float)GetFrameTime();

            playText();

            vector<MQTTMessage> messages = mqttClient.getMessages();

            if (IsKeyDown(KEY_UP))
            {
                gameModel.setKeyPress(KEY_UP);
            }
            else if (IsKeyDown(KEY_RIGHT))
            {
                gameModel.setKeyPress(KEY_RIGHT);
            }
            else if (IsKeyDown(KEY_DOWN))
            {
                gameModel.setKeyPress(KEY_DOWN);
            }
            else if (IsKeyDown(KEY_LEFT))
            {
                gameModel.setKeyPress(KEY_LEFT);
            }
            else
            {
                gameModel.setKeyPress(0);
            }

            gameModel.update(deltaTime);
            gameView.update(deltaTime);
        }
    }
    finishText();
    CloseWindow();


    cout << "Disconnected." << endl;
}

void pauseText(void)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Restarting", 225, 220, 30, BLACK);
    EndDrawing();
}

void finishText(void)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    // float score = gameModel.getScore();
    DrawText("Score: xxx", 225, 220, 30, BLACK);
    EndDrawing();
}

void playText(void)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("EDAPark Controller", 200, 220, 30, BLACK);
    EndDrawing();
}
