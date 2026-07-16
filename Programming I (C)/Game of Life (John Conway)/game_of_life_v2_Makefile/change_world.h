/***************************************************************************//**
  @file     +change_world.h+
  @brief    +Initializes and updates the world to the next generation+
  @author   +Santiago Feldman+
 ******************************************************************************/

#ifndef _CHANGE_WORLD_H_
#define _CHANGE_WORLD_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "world_config.h"

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
 * @brief set up world, all cells initialized to DEAD or ALIVE 
*/
void initialize_world(void); 

/**
 * @brief updates the current world to the next generation 
*/
void update_world(void);

/*******************************************************************************
 ******************************************************************************/

#endif // _CHANGE_WORLD_H_
