
/***************************************************************************//**
  @file     main.c
  @brief    Módulo principal: interactúa con el usuario presentando el juego y avisando de errores
  @author   Grupo 5
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include    <stdio.h>                   
#include    "teclado.h"                 //Header del módulo teclado
#include    "imprime.h"                 //Header del módulo imprime
#include    "cell.h"                    //Header del módulo cell

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define     MAX     19  //Máximo de columnas 	
#if (ANCHO>MAX)         //Si se sobrepaso del máximo, hubo error de rango
#define ERROR_RANGO	
#endif

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

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

int	main(void)
{
	
    #ifdef ERROR_RANGO                                      //Si se activo el error de rango
        printf("Valores de largo y/o ancho demasiado grandes\n");   //entonces se informa al usuario y termina el programa
    #else 
        int	i=0;                                                //Índice de filas
        int	j=0;                                                //Índice de columnas
        int	generacion;                                         //Cantidad de generaciones
        int	k;                                                  //Índice elementos del patrón
        int	mundo[LARGO][ANCHO]={0};                            //Definición de la matriz
        int contador_de_celulas= LARGO*ANCHO;                   //Cantidad de células en el mundo
        int	arr[]={VIVA,MUERTA,VIVA,MUERTA,MUERTA,VIVA,VIVA};   //Patrón de vivas y muertas
	
        /* INTRODUCCIÓN DEL JUEGO AL USUARIO*/
        printf	("Bienvenido al Juego de la Vida\n");
        printf	("Ingrese el número de generaciones a avanzar, si presiona 'enter' solamente avanzará una generación\n");
        printf	("Si desea terminar el programa presione la tecla 'q'\n");
        printf	("\nAquí está su mundo incial\n");
		
		                                                                                                                                           

        /* SE DEFINE EL MUNDO INICIAL */
        while (contador_de_celulas >0)                      //Mientras que no se hayan reemplazado todas las células
        {
            for (k=0; k<(sizeof(arr)/sizeof(int)); ++k)     //Toma los elementos del patrón
            {
				
                if (contador_de_celulas > 0)                //Si no se reemplazaron todas las células
                {	
                    if (j<ANCHO)                            //Y si el índice de columnas no apunta fuera del mundo
                    {
                        mundo[i][j] = arr[k];               //Asigna los elementos del patrón al mundo
                        j++;                                //Pasa a la siguiente columna
                        --contador_de_celulas;              //Disminuye el contador de células reemplazadas
                    }
                    else                                    //Si el índice de columas apuna fuera del mundo
                    {
                        j=0;                                //Se vuelve a la primera columa
                        ++i;                                //Se pasa a la siguiente fila
                        --k;                                //Se disminuye el índice para evitar que se saltee un elemento
                   }

                }	
            }
        }	

        imprime	(mundo);                                                    //Se imprime el estado inicial del mundo					
		
        /* SE DETERMINA LAS GENERACIONES A AVANZAR */  	
        printf	("¿Cuantas generaciones desea avanzar?\n");                 //Se pregunta al usuario la cantidad de generaciones a avanzar
        printf	("Si desea terminar el programa presione la tecla 'q'\n");  //Se informa al usuario como terminar el programa 
        generacion=teclado ();                                              //Se obtiene el número ingresado por el teclado
																	
        while	(generacion!=QUIT_YES)                                      //Mientras que no se haya tocado 'q' no finaliza el programa 
        {
            if	(generacion==ERROR)                                         //Si hubo un carácter inválido termina el programa 
            {
                printf("Error, carácter inválido\nIntente Nuevamente\n");   //Se informa que hubo un error y cual fue 					
                generacion=teclado ();                                      //El usuario debe volver a indicar la generaciones por teclado
            }
            else 										
            {
                while	(generacion!=(QUIT_YES))                            //Mientras que no se haya tocado 'q' no finaliza el programa
                {
                    if	(generacion!=ERROR)                                 //Si no hubo caracteres inválidos, se avanza las generaciones ingresadas
                    {  
                        while	((generacion>0))                            //Ciclo que determina el estado de la nuevas generaciones
                                                                                                
                        {
                            set_cell_state(mundo);                          //Función que define la nueva generación
                            --generacion;                                   //Se disminuye el contador de cantidad de veces ingresadas
                        }
                        imprime(mundo);	                                    //Se imprime el estado de la matriz de la generación ingresada
                        printf("¿Cuantas generaciones desea avanzar?\n");   //Se vuelve a preguntar al usuario la cantidad de generaciones a avanzar
                        printf("Si desea terminar el programa presione la tecla 'q'\n");	
                                                                            //Se informa al usuario como terminar el programa 
                        generacion=teclado ();                              //Se obtiene el número ingresado por teclado y 
                                                                            //se repite el ciclo hasta que haya error o se toque 'q'
                    }
                    else                                                    //Si hubo caracteres inválidos, se avanza las generaciones ingresadas 
                    {
                        printf("Error, carácter inválido\nIntente Nuevamente\n");   //Se informa que hubo un error y cual fue 							
                        generacion=teclado ();                              //El usuario debe volver a indicar la generaciones por teclado
                    }
                }
            }
        }
    #endif 
    return	0;                                                              //Si se toco la tecla 'q' finaliza el programa 
}










