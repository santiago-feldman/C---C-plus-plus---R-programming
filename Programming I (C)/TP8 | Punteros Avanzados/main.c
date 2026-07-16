/***************************************************************************//**
  @file     +main.c+
  @brief    +Módulo principal que inicializa los operadores y funciones y
            se comunica con el usuario dependiendo de la situación+
  @author   +Grupo 5+
 ******************************************************************************/
 
/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include <stdio.h> 
#include "info.h"               //Header que contiene la información de los arreglos de operadores y funciones
#include "teclado.h"            //Header correspondiente al módulo teclado
#include "math.h"               //Header correspondiente al módulo math

 
 /*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

static void load_operations (void); 
static void add_operation (char oper, double (*operation) (double, double, int*), int indice);
static void introduction (void);


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

int main(void)
{
    double num1, num2;                          //Primer número y segundo número
    char operator;                              //Operador del término
    double *p_num1= &num1, *p_num2 = &num2;     //Punteros a los números 
    char *p_oper= &operator;                    //Puntero al operador del término
    int error=0;                                //'Flag' de error (al principio está desactivado)
    int *p_error = &error;                      //Puntero al 'flag' de error
    double result;                              //Resultado de las operaciones 
    int i;                                      //Índice para recorrer los arreglos de funciones y operadores
    int quit = 0;                               //'Flag' de quit (al principio está desactivado)
    int *p_quit = &quit;                        //Puntero al 'flag' de quit
    
    
    load_operations();                                  //Se incializan los arreglos de funciones y operadores
    introduction();
    teclado (p_num1, p_num2, p_oper,p_error,p_quit);    //Se obtienen los números ingresados por el usuario 
    
    
    while (quit==0)                                     //Mientras que no se haya tocado la letra 'q',
                                                        //sigue corriendo el programa
    {
       for (i=0; i<MAX_OPERATORS;i++)                   //Dependiendo del operador ingresado
       {
            if (operator == operators[i])               //Se llama a la función que le corresponde 
            {
                  result =  actions[i](num1,num2,p_error);
            }
        }
       switch (error)                                   //Se analiza si hubo error
       {
            case 1:                                     //Si se activó una vez, hubo un error de sintaxis 
                printf("Sintax error\n");               //Se le informa al usuario
                break;
            case 2:                                     //Si se activó dos veces, hubo error matemático
                printf("Math error\n");                 //Se le informa al usuario
                break;
            default:                                    //Si no se activó, no hubo error
                printf("%f\n", result);                 //Se imprime el resultado de la operación
                break;
       }
     error = 0;                                         //Se vuelve a desactivar el 'flag' error
     teclado (p_num1, p_num2, p_oper,p_error,p_quit);   //Se obtienen los siguientes números ingresados por el usuario  
   }
 
   return 0;   
}

/*                      FUNCIÓN LOAD_OPERATIOS:
    Guarda la cantidad de operadores que se requieren con sus respectivas funciones */
static void load_operations (void)                
{
    unsigned int i = 0;
    add_operation ('+', suma,i++);          //Se cargan todas las operaciones queridas
    add_operation ('-', resta,i++);
    add_operation ('*', mult,i++);
    add_operation ('/', div,i++);
    add_operation ('^', pot,i++);
}
/*                      FUNCIÓN ADD_OPERATION:
    Guarda el operador y la función que recibe en los arreglos*/
static void add_operation (char oper, double (*operation) (double, double,int*), int indice)  //Se guarda una operación
{
        operators[indice] = oper;            //Para el índice correspondiente a cada operación
        actions[indice] = *operation;        //Se guarda la función que le corresponde 
}

/*                      FUNCIÓN INTRODUCTION:
    Introducción al programa, le informa al usuario lo que la calculadora puede realizar o no */
static void introduction (void)
{
    printf("Bienvenido! Esta calculadora solamente realiza operaciones de suma, resta, multiplicación, división y potencia con exponentes enteros\n");
    printf ("Porfavor ingresar la operación que quiera realizar, sólo se puede hacer una operación por vez\n");
    printf("Para salir en cualquier momento del programa, presionar la letra 'q'\n");
    
}
