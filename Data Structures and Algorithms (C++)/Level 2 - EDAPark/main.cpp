/*****************************************************************//**
* \file   main.cpp
* \brief  EDAPark. Main module.
*
* \authors Matias Ezequiel Alvarez, Santiago Feldman
* \date   March 2022
*********************************************************************/

#include "Controller.h"
#include "View.h"
#include "raylib.h"

#define SCALE_FACTOR 5

using namespace std;

int main()
{
	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "EDA level 2");

	Controller robotito;
	View drawer;

	float xAxis, yAxis, zAxis;
	float xAxisCpy = 0, yAxisCpy = 0, zAxisCpy = 0;

	// Game loop
	while (!WindowShouldClose() && robotito.isConnected())
	{
		if (robotito.isTempOK())
		{
			zAxis = IsKeyDown(KEY_Q) - IsKeyDown(KEY_E);
			yAxis = IsKeyDown(KEY_W) - IsKeyDown(KEY_S);
			xAxis = IsKeyDown(KEY_D) - IsKeyDown(KEY_A);

			if (xAxis != xAxisCpy || yAxis != yAxisCpy || zAxis != zAxisCpy)
			{
				robotito.moveRobot(xAxis, yAxis, zAxis, SCALE_FACTOR);
				xAxisCpy = xAxis;
				yAxisCpy = yAxis;
				zAxisCpy = zAxis;
			}
		}

		BeginDrawing();
		ClearBackground(BLACK);
		drawer.drawFixed();
		drawer.drawDinamic();
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
