/***************************************************************************//**
  @file     mi_printf.c
  @brief    Módulo que imprime strings en pantalla. Puede recibir parámteros
            numéricos (enteros) y caracteres
  @author   Grupo 5
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "ej4.h"  // Header del módulo 


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define DEC 10  // Constante para realizar operaciones con números en base 10
#define HEX 16  // Constante utilizada en las operaciones para pasar números de
                // base 10 a base 16
#define MAX 8   // Constante utilizada para definir el tamaño de un arreglo


/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

static void printd(int d);
static void printx(unsigned long int x);

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

/*FUNCIÓN MI_PRINTF: imprime en pantalla un string de caracteres. Pueden enviarse como parámetros 
enteros para expresar en base 10, naturales para ser expresados en formato hexadecimal o caracteres.*/
void mi_printf(char* p_str, ...)
{
    va_list args;
    va_start(args, p_str);
    while( *p_str != '\0')  					// Se imprimen los caracteres del string hasta que 
    {											// se encuentre el terminador
        if( *p_str != '%')						// Si no se ingresó el caracter "%", imprime el
        {										// caracter al que apunta el puntero al string
            putchar(*p_str);
        }
        else									// Se ingresó el caracter "%"
        {
            ++p_str;
            if(*p_str=='d')						// Se ingresó un entero signado a imprimir en decimal
            {
                int d = va_arg(args, int);
                printd(d);
            }
            else if(*p_str=='x')				// Se ingresó un entero no signado a imprimir en
            {									// hexadecimal
				int x = va_arg(args, unsigned long int);
				printx(x);
            }
            else if(*p_str=='c')				// Se ingresó un caracter a imprimirs
            {
                int c = va_arg(args, int);
				putchar(c);
            }
            else								// Si no se ingresó ni d, ni x, ni c después de "%",
            {									// se imprime el símbolo "%"
                putchar(*(--p_str));
            }
        }
		++p_str;								// Se analiza el próximo caracter en el string
    } 
    va_end(args);
}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

/*FUNCIÓN PRINTD: imprime un entero signado en pantalla, en formato decimal.*/
static void printd(int d)
{
    if(d==0)                                    // Si el entero es nulo, imprime 0
    {
        putchar('0');
    }

    if(d<0)										// Si el número es negativo, se coloca el signo menos
    {
        putchar('-');
        d=d*(-1);								// Se toma el módulo del número para imprimir sus cifras
    }	

    int d_invertido=0;
    int d_copy=d;
    int resto;
	while (d_copy != 0)                         // Este ciclo invierte las cifras del entero a imprimir
    {                                           // para facilitar la obtención de cifras individuales
        resto = d_copy % DEC;
        d_invertido = d_invertido * DEC + resto;
        d_copy /= DEC;
    }
    
    d_copy = d;
    int contador_de_cifras=0;
    while(d_copy != 0)                          // Este ciclo cuenta la cantidad de cifras que hay en
    {                                           // el entero. Es una cantidad útil para saber cuántas 
        ++contador_de_cifras;                   // de las útlimas cifras del entero son ceros
        d_copy /= DEC;
    }
    
    while( d_invertido != 0 )                   // Este ciclo imprime en pantalla las cifras del entero, 
    {                                           // desde la cifra de menor jerarquía distinta de cero 
        putchar(d_invertido % DEC + '0');        // hasta la cifra de mayor jerarquía
        d_invertido /= DEC;
        --contador_de_cifras;
    }

    while(contador_de_cifras != 0)				// Este ciclo imprime en pantalla los ceros al final
    {                                           // del número, si es que los hay
        putchar('0');
        --contador_de_cifras;
	}
}

/*FUNCIÓN PRINTX: imprime un entero no signado en pantalla, en formato hexadecimal.*/
static void printx(unsigned long int x)
{
    char arr[MAX];								// Arreglo en el que se colocan los caracteres en "hexa"
    int resto;
    int i=0;									// Índice para acceder al arreglo

    while((x != 0) && (i<MAX))					// Este ciclo se repite hasta obtener todos los 		
    {											// caracteres en "hexa" o hasta llenar el arreglo.
        resto= x%HEX;							// Tomo los caracteres en hexadecimal (obtengo primero 
        if(resto<10) arr[i]= resto + '0';		// el último; en la vuelta final obtengo el primer
        else if(resto==10) arr[i]='A';			// caracter) y los guardo en el arreglo con su formato
        else if(resto==11) arr[i]='B';			// ascii para luego imprimirlos en pantalla. El tamaño
        else if(resto==12) arr[i]='C';			// del arreglo equivale a la cantidad de caracteres en 
        else if(resto==13) arr[i]='D';			// hexadecimal que ocupa el máximo valor posible del
        else if(resto==14) arr[i]='E';			// tipo unsigned long (FFFF FFFF --> 8 caracteres).
        else arr[i]='F';
        ++i;
        x /= HEX;
    }

    while(i<MAX)								// Este ciclo llena de terminadores los elementos del
    {											// arreglo que no se utilizaron
        arr[i]='\0';
        ++i;
    }

	putchar('0');
	putchar('x');
    char *p_arr;
    for(p_arr=&arr[MAX-1]; p_arr>=arr; --p_arr)	// Se imprime en pantalla el número en hexadecimal
    {
        if(*p_arr != '\0') putchar(*p_arr);
    }
}
