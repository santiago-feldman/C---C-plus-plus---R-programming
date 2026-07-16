/***************************************************************************//**
  @file     cell.c
  @brief    Analiza el estado de las células en la generación actual como en las siguientes y avanza a la nueva generación
  @author   Grupo 5
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include <stdio.h>
#include "cell.h"                                  //Header del módulo actual 

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
 
/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
 
/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/
 
/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

static int state_cell_now (int mat[][ANCHO],int i, int j); 
static int state_cell_around (int mat[][ANCHO], int i, int j);
static void state_cell_nextgen (int Nueva_Mat[][ANCHO], int Estado_Celula, int Celulas_Vivas_Alrededor, int i, int j);
static void change_to_nextgen (int mat[][ANCHO], int Nueva_Mat[][ANCHO]);

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
 
/*FUNCIÓN QUE RECIBE EL MUNDO Y GENERA LA NUEVA GENERACIÓN*/
void set_cell_state(int	mat[][ANCHO])				                         
{
    int	Nueva_Mat[LARGO][ANCHO];                //En esta nueva matriz, se van colocando los nuevos estados de las células en la próxima generación
    int i;                                      //Índices para recorrer las células
    int j;
   	for (j=0;j< ANCHO;++j)                      //Se analizarán todas las columnas para 0 <= j <= ANCHO-1
    {
        for (i=0;i<LARGO;++i)					//Se analizarán todas las filas para 0 <= i <= LARGO-1
        {
            int	Estado_Celula=state_cell_now (mat,i,j);                                     //Se obtene el estado acual de la célula
            int Celulas_Vivas_Alrededor= state_cell_around(mat,i,j);                        //Se obtiene la cantidad de células vivas alrededor
            state_cell_nextgen (Nueva_Mat,Estado_Celula,Celulas_Vivas_Alrededor,i,j);       //Se analiza el estado en la nueva generación	                                      
        }
    }
    change_to_nextgen (mat, Nueva_Mat);        //Se cambia el mundo por la siguiente generación
}	


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

/*FUNCIÓN QUE  ANALIZA EL ESTADO DE LA CÉLULA EN LA GENERACIÓN ACTUAL*/
static int state_cell_now (int mat[][ANCHO], int i, int j)  
{     
    int	Estado_Celula=0;                         //Estado de la célula. Se inicializa en 0 (ni viva ni muerta)   
   								        

    if	(mat[i][j]==VIVA)                       //La célula está viva
    {
        Estado_Celula=VIVA;
    }
    else 
    {
        Estado_Celula=MUERTA;                   //La célula está muerta
	}

    return Estado_Celula;                       //Devuelve el estado de la célula
}	
			
/*FUNCIÓN QUE ANALIZA EL ESTADO DE LAS CÉLULAS ALREDEDOR*/
static int state_cell_around (int mat[][ANCHO],int i, int j)
{
    int	Celulas_Vivas_Alrededor=0;                      //Cantidad de células vivas alrededor. Se inicializa en 0
							    
    if	(j!=0)                                          //La célula analizada no está en el borde izquierdo
    {
        if	(mat[i][j-1]==VIVA)                         //La célula a la izquierda está viva
        {
            Celulas_Vivas_Alrededor+=1;
        }
        if	((i != 0)&&(mat[i-1][j-1]==VIVA))           //La célula analizada no está en el borde izquierdo ni en el borde superior,
                                                        //y la célula del extremo superior izquierdo está viva
        {
            Celulas_Vivas_Alrededor+=1;
        }
        if	((i!=(LARGO-1)&&(mat[i+1][j-1]==VIVA)))	    //La célula analizada no está en el borde izquierdo ni en el borde inferior, 
                                                        //y la célula del extremo inferior izquierdo está viva
        {
            Celulas_Vivas_Alrededor+=1;
        }

    }
				
    if	(j!=ANCHO-1)                                    //La célula analizada no está en el borde derecho
    {
        if	(mat[i][j+1]==VIVA)                         //La célula a la derecha está viva
        {
            Celulas_Vivas_Alrededor+=1;
        }
        if	((i != 0)&&(mat[i-1][j+1]==VIVA))           //La célula analizada no está en el borde derecho ni en el borde superior,
                                                        //y la célula del extremo superior derecho está viva
        {
            Celulas_Vivas_Alrededor+=1;
        }
        if	((i != LARGO-1)&&(mat[i+1][j+1]==VIVA))     //La célula analizada no está en el borde derecho ni en el borde inferior,
                                                        //y la célula del extremo inferior derecho está viva
        {
            Celulas_Vivas_Alrededor+=1;
        }
   }
	
    if	((i!=0)&&mat[i-1][j]==VIVA)	                    //La célula analizada no está en el borde superior y la célula de arriba está viva
    {
        Celulas_Vivas_Alrededor+=1;
    }

    if	((i != LARGO-1)&&mat[i+1][j]==VIVA)             //La célula analizada no está en el borde inferior y la célula de abajo está viva
    {
        Celulas_Vivas_Alrededor += 1;
    }


    return Celulas_Vivas_Alrededor;
}			



/*FUNCIÓN QUE ANALIZA EL ESTADO DE LA CÉLULA EN LA PRÓXIMA GENERACIÓN*/		
static void state_cell_nextgen (int Nueva_Mat[][ANCHO], int Estado_Celula, int Celulas_Vivas_Alrededor,int i, int j)
{

    if	(Celulas_Vivas_Alrededor>3)                     
                                                        
    {
        Nueva_Mat[i][j]=MUERTA;                         //La célula tiene más de tres vecinos vivos; 
                                                        //Entonces, muere en la próxima generación
    }
    else if	(Estado_Celula==VIVA)
    {
        if	((Celulas_Vivas_Alrededor==2)||(Celulas_Vivas_Alrededor==3))
        {
            Nueva_Mat[i][j]=VIVA;                       //La célula viva tiene exactamente 2 o 3 vecinos; 
                                                        //Entonces, vive en la próxima generación
        }	
        else
        {
            Nueva_Mat[i][j]=MUERTA;                     //La célula viva tiene menos de 2 vecinos; 
                                                        //Entonces, muere en la próxima generación
        }
    }
    else if	(Celulas_Vivas_Alrededor==3)                                                               
    {
        Nueva_Mat[i][j]=VIVA;                           //La célula muerta tiene 3 vecinos; 
                                                        //Entonces, vive en la próxima generación
    }
    else                                        
    {
        Nueva_Mat[i][j]=MUERTA;                         //La célula muerta tiene menos de 3 vecinos; 
                                                        //Entonces, seguirá muerta en la próxima generación
    }
    Celulas_Vivas_Alrededor=0;                          
} 
			  
/*FUNCIÓN QUE PASA LA PRÓXIMA GENERACIÓN AL MUNDO ORIGINAL*/
static void change_to_nextgen (int mat[][ANCHO], int Nueva_Mat[][ANCHO])
{
    int i;                                              //Índices para recorrer las células
    int j;	
    for	(j=0;j<ANCHO;++j)
    {
        for	(i=0;i< LARGO;++i)
        {
            mat[i][j]=Nueva_Mat[i][j];                  //Todas las células del mundo actual pasan al estado de la siguiente generación
        }
    }
}			
            
			

			
			
    
  
			


