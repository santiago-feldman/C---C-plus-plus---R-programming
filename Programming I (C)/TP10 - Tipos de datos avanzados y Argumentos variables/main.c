/***************************************************************************//**
  @file     main.c
  @brief    Módulo principal que interactúa con el usuario y llama a las funciones 
            correspondientes para modificar el puerto A *
  @author   Grupo 5
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include "puertos.h"        
#include "teclado.h"


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define PUERTO 'A'              //Puerto 
#define MASKALL 255             //Máscara de todos los bits
#define ASCII 48                



/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/


int main (void)
{
    int i;                                      //Índice para recorrer los bits del puerto
    printf("PUERTO A: ");
    for (i=7; i >=0; i--)       
    {
       
        printf("%d", bitGet(PUERTO,i));         //Se imprime todo el puerto
    }
    printf("\n");
    char digit = teclado();                     //Se toma lo ingresado por teclado
    while (digit != 'q')                        //Mientras que no se haya presionado la letra 'q'
    {
        if (NUMBER(digit))                      //Si lo ingresado es un número
        {
            digit -= ASCII;                     //Se transforma el ascii a entero
            
            bitSet(PUERTO, digit);              //Se prende el bit que indica el número
            printf("PUERTO A: ");
            for (i=7; i >=0; i--)       
            {
                
                printf("%d", bitGet(PUERTO,i)); //Se imprime todo el puerto
               
            }   
           
        }
        else if (digit == ERROR)                          //Si hubo error
        {
            printf ("Se ingresó un carácter inválido");   //Le avisa al usuario
            
        }
        else        //Si se ingreso una letra válida
        {
            switch (digit)      
            {
                case 't':                           //Si la letra fue 't'
                    maskToggle (PUERTO,MASKALL);    //Se cambia el estado de todos los bits
                    
                    break;
                case 'c':                           //Si la letra fue 'c'
                    maskOff (PUERTO, MASKALL);      //Se apagan todos los bits
                    break;
                case 's':                           //Si la letra fue 's'
                    maskOn (PUERTO, MASKALL);       //Se prenden todos los bits
                    break;
                default:
                    break;       
            }
            printf("PUERTO A: ");
            for (i=7; i >=0; i--)
            {
                
                printf("%d", bitGet(PUERTO,i));     //Se imprime todo el puerto
                
            }   
        }
         printf("\n");
                                      
        digit = teclado();                          //Se toma lo que ingresa el usuario a continuación
    }
    
   return 0; 
    
}
    
    
    

