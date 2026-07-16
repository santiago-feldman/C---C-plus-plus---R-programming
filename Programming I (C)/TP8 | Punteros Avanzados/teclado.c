/***************************************************************************//**
  @file     +teclado.c+
  @brief    +Módulo que se encarga de recibir y analizar lo ingresado por teclado
            por el usuario +
  @author   +Grupo 5+
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdio.h>      
#include "info.h"           //Header que contiene la información de los arreglos de operadores y funciones
#include "teclado.h"        //Header de este  módulo 

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define ENTER 10
#define PUNTO 46
#define ASCII 48
#define ZERO  48
#define NINE  57
#define YES_NUMBER(x) (((x)>=ZERO) && ((x)<=NINE))          //Verifica si el carácter representa un número
#define NOT_ENTER(x)   ((x) != ENTER)                       //Verifica si el carácter no es enter


/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

static double get_number (char *p_oper, int *p_error, int* p_quit, unsigned int count_of_num);
static void error (int c, int *p_error);
static double sign_check (double ent,double decimals, int sign);
static void last_char_check (char *p_oper, int c, int *p_error, unsigned int count_of_num);
static int not_operator (int c);
/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

/*                      FUNCIÓN TECLADO:
    Se encarga de llamar a la función para obtener los números ingresados*/
    
void teclado(double *p_num1,double *p_num2, char  *p_oper, int *p_error, int *p_quit)											    				
{
    unsigned int count_of_num = 0;                                          
	*p_num1 = get_number(p_oper,p_error,p_quit,count_of_num);               //Obtiene el primer número y el operador  
	count_of_num =1;              
	 if (((*p_error) != 1 ) && ( (*p_quit) != 1))                //Si no se ingresó la letra 'q' ni hubo un error
	 {
	    *p_num2 = get_number(p_oper,p_error,p_quit,count_of_num);           //Se obtiene el segundo número
	 }
	
}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

/*                      FUNCIÓN GET_NUMBER:
    Se pasa los ascii ingresados a números y guarda el operador ingresado*/
    
static double get_number (char *p_oper, int *p_error, int *p_quit, unsigned int count_of_num)
{

    int c  = getchar();                     //Caracteres ingresados por teclado 
    int sign=0;                             //'Flag' de signo del número
    double ent=0.;                          //Parte entera del número
    double decimals=0.;                     //Decimales del número
    double num=1.;                          //Número completo (se inicializa en uno para evitar complicaciones con los errores)                               
    double count_decimals=1;                //Contador de decimales     
          
    if (c == 'q')                           //Si se presionó la letra 'q'
    {
        c=getchar();                        //Se toma el próximo carácter
        if (NOT_ENTER(c))                   //Si el carácter no es enter, hay error de sintaxis
        {
            error (c,p_error);
            c=ENTER;                        //Para evitar complicaciones se le asigna a c el valor de enter
        }
        else                                //Si el carácter es un enter
        {
            *p_quit=1;                      //Se activa el 'flag' quit
        }
    }
   
    if (c == '-')                           //Si el número es negativo
    {	
        sign =1;                            //Se activa el 'flag' de signo		
        c = getchar ();                     //Se pasa al comienzo del número 
        if (!(NOT_ENTER(c)))                //Si el siguiente carácter es un enter
        {
            error(c,p_error);                 //Hubo erro de sintaxis
        }
    } 
	    
    if (!(YES_NUMBER(c))&&(c!='-'))         //Si el dígito ingresado no es número o el signo menos hubo un error de sintaxis
    {	
        error(c,p_error);                                      
    }		
    else 
    {
        while  (NOT_ENTER(c) && (not_operator(c)))									
        //Toma los caracteres hasta encontrar un enter o un operador
        {
            if (c != PUNTO)                         //Toma los caracteres que forman parte del entero del número (es decir antes del punto)
            {
                if (YES_NUMBER(c))                  //Si son números los ingresados, no hubo error y se prosigue con la tranformación a ascii
                {
                    ent *= 10;                      //Transformación a ascii
                    ent += c - ASCII;
                    c = getchar ();	
                }
                else                                //Si hay un carácter inválido, hubo error de sintaxis
                {
                   error(c,p_error);
                   c=ENTER;                         //Se iguala el carácter a enter para salir del ciclo
                }			    
            }
            else                                    // Si se ingresó un punto, se toma los caracteres que forman la parte decimal 
            {
                c = getchar();                      //Se pasa al primer número de la parte decimal 
                while (NOT_ENTER(c) && (not_operator(c)))
                {
                    if (YES_NUMBER(c))              //Si son números los ingresados, no hubo error y se prosigue con la transformación a ascii
                    {
                        count_decimals *= 10.0;	    //Se multiplica conta por 10 para así saber la cantidad de decimales ingresados 
                        decimals *=10.0;            //Transformación a ascii
                        decimals += c-ASCII;
                        c=getchar();
                    }
                    else                            //Si  hay un carácter inválido, hubo error de sintaxis
                    {
                        error(c,p_error);
                        c=ENTER;                    //Se iguala el carácter a enter para salir del ciclo
                    }						    
                }
                
                decimals /= (count_decimals);       //Se obtienen los decimales (antes estaban como un número entero y por eso se los divide con conta)
            }
        }
        
       last_char_check (p_oper, c, p_error, count_of_num); //Se analiza el último carácter 
    }
    
    if (*p_error != 1)                              //Si no hubo error, entonce se consigue el número completo
    {
        num = sign_check(ent,decimals,sign);
    }
    return num;                                     //Se devuelve el número ingresado
}

/*                      FUNCIÓN ERROR:
    Se activa el 'flag' error una vez para indicar error de sintaxis */

static void error (int c, int *p_error)
{
    if (NOT_ENTER(c))                       //Si el carácter no es enter
    {
        while  (NOT_ENTER(c))				
        {
            *p_error = 1;					//Se activa el 'flag' de error
            c = getchar ();					//Se "recorre" todo los carácteres que le siguen al carácter inválido para evitar complicaciones
        }
    }
    else                                    //Si el carácter es enter, no hay más carácteres que le siguen
    {
        *p_error =1;                        //Se activa el 'flag' de error
    }
}

/*                      FUNCIÓN LAST_CHAR_CHECK:
    Se analiza cuál fue el último carácter de lo ingresado 
    y dependiendo de si es el segundo número o no, activa el flag error*/
static void last_char_check (char *p_oper, int c, int *p_error, unsigned int count_of_num)
{
    if ((!(not_operator(c))) && (count_of_num ==0)) //Si el último cáracter fue un operador y es el primer número
    {
        *p_oper = (char)c;                      //Se guarda el operador
    }
    else if ((!(NOT_ENTER(c))) && (count_of_num ==0)) //Si el útlimo cáracter fue un enter y es el primer número
    {
           *p_error=1;                          //Hubo error de sintaxis 
    }
    else if ((!(not_operator(c)))&& (count_of_num ==1)) //Si el último cáracter fue un operador y es el segundo número
    {
       error (c,p_error);                       //Hubo error de sintaxis      
    }

}

/*                      FUNCIÓN SING_CHECK:
    Recibe la parte entera y decimal de un número y lo convierte 
    dependiendo de su signo */
static double sign_check (double ent,double decimals, int sign)
{
    double num;
    if (sign != 1)                          //Si el número es positivo
    { 
        num = ent + decimals;               //Se suma la parte entera con la parte decimal y se obtiene el número completo positivo 
    }
    else                                    //Si el número es negativo
    {
        num = ent + decimals;               //Se suma la parte entera con la parte decimal y se obtiene el módulo del número 
        num *= (-1);                        // y se lo multiplica por -1 y se obtiene el número completo negativo 
    }
    return num;
}

/*                      FUNCIÓN NOT_OPERATOR:
   Analiza si el carácter recibido es un operador que se encuentra en el arreglo */
static int not_operator (int c)            
{
    int i;                              //Índice para recorrer el arreglo
    int truth=1;                        //Variable que indica si es verdadero o no 
    for (i=0; i<MAX_OPERATORS; ++i)
    {
        if (c == operators[i])          //Si el carácter es alguno de los operandos
        {
            truth=0;                    //Entonces, no es un operador y el argumento es falso
        }
        
    }
    return truth;

}

	
	

