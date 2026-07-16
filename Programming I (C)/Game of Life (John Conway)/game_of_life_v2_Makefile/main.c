/***************************************************************************//**
  @file     +main.c+
  @brief    +Finite & preset world implementation of Conway´s Game of Life+
  @author   +Santiago Feldman+
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include <stdio.h>
#include "change_world.h"
#include "output.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define QUIT    'q'	 

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

int main(void)
{

    printf("Welcome to Conway's Game of Life!\n"
            "Rules:\n"
            "\t* Enter the number of generations you would like to advance\n"
            "\t* Press enter to advance only one generation\n"
            "\t* Press q to quit\n"
            "Current state of the world:\n");
        
    initialize_world();
    output_world();

    int num_gen = 0;
    char invalid_flag = 0;
    char c = 0;

    while(c != QUIT)
    {
        c = getchar();

        if(c == QUIT)
        {
            num_gen = 0;
            printf("Thank you for playing!\n");
        }
        else if (c == '\n')
        {
            num_gen = 1;
        }
        else if(c >= '0' && c <= '9')
        {
            do
            {
                num_gen = num_gen * 10 + (c - '0');
                c = getchar();
            }
            while (c >= '0' && c <= '9');

            if(c != '\n')
            {
                printf("Invalid expression. Please try again:\n");
                num_gen = 0;
                invalid_flag = 1;
            }
        }
        else
        {
            printf("Invalid character. Please try again:\n");
            invalid_flag = 1;
        }

        while (num_gen != 0)
        {
            update_world();
            --num_gen;
        }

        if(invalid_flag == 0)
            output_world();
        else
        {
            while ((c = getchar()) != '\n' && c != EOF);    // Empty the getchar() buffer
            invalid_flag = 0;
        }
    }

    return 0;
}