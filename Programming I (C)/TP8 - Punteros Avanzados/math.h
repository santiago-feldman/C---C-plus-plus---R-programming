/***************************************************************************//**
  @file     +math.h+
  @brief    +Header del archivo con la operaciones matemáticas+
  @author   +Grupo 5+
 ******************************************************************************/

#ifndef MATH_H
#define MATH_H



/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
 * @brief SUMA: función que suma dos números
 * @param num1 número base
 * @param num2 número que se le sumará al número base
 * @return devuelve la suma de los números
*/
double suma(double num1, double num2, int *p_error);

/**
 * @brief RESTA: función que resta dos números
 * @param num1 número base
 * @param num2 número que se le restará al número base
 * @return devuelve la resta de los números
*/
double resta(double num1, double num2,int *p_error);

/**
 * @brief MULT: función que multiplica dos números
 * @param num1 número base
 * @param num2 número que multiplicará al número base
 * @return devuelve el producto de los números
*/
double mult(double num1, double num2,int *p_error);

/**
 * @brief DIV: función que divide dos números
 * @param num1 numerador
 * @param num2 denominador
 * @return devuelve la división entre los números
*/
double div(double num1, double num2,int *p_error);

/**
 * @brief POT: función que calcula potencias
 * @param num1 base
 * @param num2 exponente
 * @return devuelve la base elevada al exponente
*/
double pot(double num1, double num2,int *p_error);

/*******************************************************************************
 ******************************************************************************/

#endif // MATH_H
