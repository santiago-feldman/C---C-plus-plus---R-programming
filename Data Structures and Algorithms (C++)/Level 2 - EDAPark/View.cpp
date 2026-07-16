/*****************************************************************//**
* \file   View.cpp
* \brief  View Class Code.
*
* \authors Matias Ezequiel Alvarez, Santiago Feldman
* \date   March 2022
*********************************************************************/

#include "View.h"
#include "raylib.h"

#define XPOS 15
#define YPOS1 90
#define YPOS2 110
#define FONTSIZE1 14
#define FONTSIZE2 22

enum
{
	MOTOR_1 = 1,
	MOTOR_2,
	MOTOR_3,
	MOTOR_4,
	MOTOR_NUM
};

using namespace std;

/// @brief Shows the instructions on screen
void View::drawFixed()
{
	DrawText("Robotito", XPOS, 15, 30, RED);
	DrawText("Go forward with W", XPOS, 60, FONTSIZE1, WHITE);
	DrawText("Go backwards with S", XPOS, 90, FONTSIZE1, WHITE);
	DrawText("Go left with A", XPOS, 120, FONTSIZE1, WHITE);
	DrawText("Go right with D", XPOS, 150, FONTSIZE1, WHITE);
	DrawText("Rotate to the left with Q", XPOS, 180, FONTSIZE1, WHITE);
	DrawText("Rotate to the right with E", XPOS, 210, FONTSIZE1, WHITE);
}

/// @brief Shows what keys are being pressed
void View::drawDinamic()
{
	if (IsKeyDown(KEY_Q))
	{
		DrawText("Q", 350, YPOS1, FONTSIZE2, GOLD);
	}
	else
	{
		DrawText("Q", 350, YPOS1, FONTSIZE2, WHITE);
	}

	if (IsKeyDown(KEY_W))
	{
		DrawText("W", 370, YPOS1, FONTSIZE2, GOLD);
	}
	else
	{
		DrawText("W", 370, YPOS1, FONTSIZE2, WHITE);
	}

	if (IsKeyDown(KEY_E))
	{
		DrawText("E", 390, YPOS1, FONTSIZE2, GOLD);
	}
	else
	{
		DrawText("E", 390, YPOS1, FONTSIZE2, WHITE);
	}

	if (IsKeyDown(KEY_A))
	{
		DrawText("A", 350, YPOS2, FONTSIZE2, GOLD);
	}
	else
	{
		DrawText("A", 350, YPOS2, FONTSIZE2, WHITE);
	}

	if (IsKeyDown(KEY_S))
	{
		DrawText("S", 370, YPOS2, FONTSIZE2, GOLD);
	}
	else
	{
		DrawText("S", 370, YPOS2, FONTSIZE2, WHITE);
	}

	if (IsKeyDown(KEY_D))
	{
		DrawText("D", 390, YPOS2, FONTSIZE2, GOLD);
	}
	else
	{
		DrawText("D", 390, YPOS2, FONTSIZE2, WHITE);
	}
}
