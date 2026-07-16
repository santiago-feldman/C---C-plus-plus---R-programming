/***************************************************************************//**
  @file     teclado.c
  @brief    Módulo que recibe lo ingresado por usuario
  @author   Grupo 5
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdio.h>
#include "teclado.h"    //Header del módulo


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define ENTER 10
#define LETTER(x) (((x)=='q')||((x)== 't') || ((x) == 's') || ((x)=='c'))   //Se determina si es una letra válida


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
/*FUNCIÓN TECLADO: Recibe lo ingresado por teclado y lo interpreta*/
char teclado (void)
{
    char c = getchar();                                         //Cáracter ingresado por teclado
    char digit;                                                 //Dígito que indica lo que se ingreso por teclado o error
    if (NUMBER(c) || LETTER(c))                                 //Si lo ingresado es un número válido o letra válida
    {
        digit = c;                                              //Se guarda ese carácter
        c = getchar();                                          //Toma el siguiente carácter
        while (c != ENTER)                                      //Si distinto a enter          
        {
            digit = ERROR;                                      //Entonces hubo un error
            c = getchar();                                      //Se recorre todos los carácteres ingresados para evitar complicaciones
        }
    }
    else                                                        //Si lo ingresado no es un número válido o letra válida
    {                                    
        while (c != ENTER)                                             
        {
            digit = ERROR;                                      //Hubo error
            c = getchar();                                      //Se recorre todos los carácteres ingresados para evitar complicaciones
        }
    }
    return digit;               
}










               





