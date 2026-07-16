/***************************************************************************//**
  @file     cell.h
  @brief    
  @author   Grupo 5 
 ******************************************************************************/

#ifndef _CELL_H_
#define _CELL_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include  "size.h"      //Header con la información del mundo


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define	MUERTA  32		//Constante que indica que la célula está muerta	
#define	VIVA    42		//Constante que indica que la célula está viva

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/



/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/




/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
 * @brief   Función que recibe el mundo actual del juego y pasa a la siguiente generación 
 * @param   Recibe un puntero al comiezo del mundo actual del juego 
 * @return Devuelve el valor de la generación o un aviso de error 
*/
void set_cell_state(int	mat[][ANCHO]);	


/*******************************************************************************
 ******************************************************************************/

#endif // _CELL_H_
