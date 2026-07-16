/***************************************************************************//**
  @file     teclado.c
  @brief    Recibe lo ingresado por el usuario con el teclado y devuelve la cantidad de generaciones o si se termina el juego o si hubo error
  @author   Grupo 5
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdio.h>
#include "teclado.h"                        //Header del módulo actual

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define	ENTER       10	                    //Constante con el valor ascii del enter
#define	ASCII       48                      //Constante con el valor de la diferencia entre los ascii y los números


/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
 
 
/*FUNCIÓN TECLADO*/ 
int teclado(void)                                              																			                        
{
    int	c=getchar();                                    //Variable que toma los valores de ASCII, 
    int	ent=0;                                          //Variable que toma el valor del número entero ingresado en el teclado

    if	((c<'0'||c>'9')&&(c!=QUIT)&&(c!=ENTER))	        //Si el dígito ingresado no es número o la letra q o enter, entonces hay error 
    {	
        while	(c != ENTER)
        {
            ent=ERROR ;	                                //Se le asigna un valor negativo (que no podría haber sido ingresado por el usuario)
            c=getchar();	
		}		
	}
    else if	((c>='0'&&c<='9'))                          //Si se ingresó un número, entonces se transforma de ascii a entero 
	{
        while	((c!= ENTER)&&(c>='0'&&c<='9'))         //Toma los caracteres hasta encontrar un enter o un carácter inválido
        {
            ent*=10;                                    //Transformación a ascii
            ent+=c-ASCII;		
            c=getchar();                                //Siguiente carácter 				
        }
        while	(c!=ENTER)                              //Si hubo en la cadena de caracteres un carácter inválido, hay error
        {
            ent=ERROR;                                  //Se le asigna un valor negativo (que no podría haber sido ingresado por el usuario)
            c=getchar ();					
        }	
    }
    else if	(c==QUIT)                                   //Si se ingresó la letra q, el juego termina
    {
        ent=QUIT_YES;                                   //Se le asigna un valor negativo (que no podría haber sido ingresado por el usuario),
                                                        //para que el main interprete que termina el juego 	
    }
    else                                                //Si se ingresó solamente enter, entonces avanza una generación
    {
        ent=1;	
    }	
    return ent;                                         //Devuelve el valor de la generación o error
}
        


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/








