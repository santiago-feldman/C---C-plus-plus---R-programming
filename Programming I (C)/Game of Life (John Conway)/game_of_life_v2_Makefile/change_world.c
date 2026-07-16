/***************************************************************************//**
  @file     +change_world.c+
  @brief    +Initializes and updates the world to the next generation+
  @author   +Santiago Feldman+
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "change_world.h"

/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/

char world[HEIGHT][WIDTH];

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void initialize_world(void)
{
    //Alive and dead cells pattern for initialization
    char pat[]={ALIVE,DEAD,ALIVE,DEAD,DEAD,ALIVE,ALIVE};   
    int size_pat = sizeof(pat)/sizeof(pat[0]);

    int i, j, k = 0;
    for (i = 0; i < HEIGHT; ++i)
    {
        for (j = 0; j < WIDTH; ++j)
        {
            world[i][j] = pat[k];
            k = (k == size_pat-1) ? 0 : k+1;
        }
    }
}

void update_world(void)
{
    char ln;                        // Living neighbors 
    char temp[HEIGHT][WIDTH];       // Temporary matrix for updating world
    int i, j;

    // Check all surrounding neighbor cells
    for (i = 0; i < HEIGHT; ++i)
    {
        for(j = 0; j < WIDTH; ++j)
        {
            ln = 0;                 // Reset counter

            if (i != 0)
            {
                if(world[i-1][j] == ALIVE) ++ln;           
                if ((j != 0) && (world[i-1][j-1] == ALIVE)) ++ln;
                if ((j != WIDTH-1) && (world[i-1][j+1] == ALIVE)) ++ln; 
            }

            if (i != HEIGHT-1)
            {
                if(world[i+1][j] == ALIVE) ++ln;           
                if ((j != 0) && (world[i+1][j-1] == ALIVE)) ++ln;
                if ((j != WIDTH-1) && (world[i+1][j+1] == ALIVE)) ++ln; 
            }

            if((j != 0) && (world[i][j-1] == ALIVE)) ++ln;
            if((j != WIDTH-1) && (world[i][j+1] == ALIVE)) ++ln;
        
            if(world[i][j] == DEAD)
                temp[i][j] = (ln == 3) ? ALIVE : DEAD;
            else
                temp[i][j] = ((ln == 2) || (ln == 3)) ? ALIVE : DEAD;
        }
    }

    // Update to next generation
    for (i = 0; i < HEIGHT; ++i)
    {
        for (j = 0; j < WIDTH; ++j)
        {
            world[i][j] = temp[i][j];
        }
    }
}