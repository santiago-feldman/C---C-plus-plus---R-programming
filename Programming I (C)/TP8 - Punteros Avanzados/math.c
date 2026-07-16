/***************************************************************************//**
  @file     +math.c+
  @brief    +Archivo que contiene las operaciones matemáticas de la calculadora+
  @author   +Grupo 5+
 ******************************************************************************/

/*******************************************************************************
 * HEADER FILES
 ******************************************************************************/
#include <stdio.h>
#include "info.h"       //Header que contiene la información de los arreglos de operadores y funciones
#include "math.h"       //Header de este  módulo

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/


/*FUNCIÓN SUMA*/
double suma(double num1, double num2,int *p_error)
{
    return num1+num2;
}

/*FUNCIÓN RESTA*/
double resta(double num1, double num2,int *p_error)
{
    return num1-num2;
}

/*FUNCIÓN MULTIPLICACIÓN*/
double mult(double num1, double num2,int *p_error)
{
	double rta = num1*num2;
	if (rta != 0)
	{
	    return rta;
	}
	else                        //Evita devolver -0
	{
	    return rta*rta;
	}
}

/*FUNCIÓN DIVISIÓN*/
double div(double num1, double num2,int *p_error)
{
    double rta;
    if(num2!=0)
    {
        rta=num1/num2;
    }
    else                                //Error matemático (se divide por 0)
    {
        *p_error = 2;                   //Se activa dos veces el 'flag' de error
    }
    
    if (rta != 0)
	{
	    return rta;
	}
	else
	{                                   //Evita devolver -0
	    return rta*rta;
	}
}

/*FUNCIÓN POTENCIA*/
double pot(double num1, double num2,int *p_error)
{
    double rta=1;

    if (((num2 - (int)num2) > 0) || ((num2 -(int)num2) <0))     //Error matemático (la potencia no es entera)
    {
         *p_error = 2;                                          //Se activa dos veces el 'flag' de error

    } 
    else 
    {
         if((num1!=0) || (num1==0 && (int)num2>0))          
         {
            int i;
            if((int)num2>=0)                                    //Cálculo de potencias positivas
            {
                for(i=0;i<(int)num2;++i)
                {
                    rta *= num1; 
                }	
            }
            else                                                //Cálculo de potencias negativas
            {
                int num2_natural= (-1)*(int)num2;
                for(i=0;i<num2_natural;++i)
                {
                    rta *= num1; 
                }	
                rta= 1/rta;
            }
        }
         else                                                   //Error matemático (0⁰)
        {
            *p_error=2;                                         //Se activa dos veces el 'flag' de error
        }
    }
    
    if (rta != 0)
	{
	    return rta;
	}                                                           //Evita devolver -0
	else
	{
	    return rta*rta;
	}
}

