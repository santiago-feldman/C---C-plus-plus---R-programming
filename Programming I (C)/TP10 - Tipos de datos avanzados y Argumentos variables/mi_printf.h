/***************************************************************************//**
  @file     mi_printf.h
  @brief    Header del archivo que contiene las funciones
            necesarias para imprimir en pantalla strings
  @author   Grupo 5
 ******************************************************************************/
#ifndef MI_PRINTF_H
#define MI_PRINTF_H

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
 * @brief TODO: Imprime en pantalla un string de caracteres. Pueden enviarse 
 *              como parámetros enteros para expresar en base 10, naturales 
 *              para ser expresados en formato hexadecimal o caracteres.
 * @param p_str puntero al primer elemento del string
 * @param ...	argumentos variables (pueden ser enteros, naturales o caracteres)
 * @return no devuelve
*/
    void mi_printf(char* p_str, ...);

/*******************************************************************************
 ******************************************************************************/

#endif // MI_PRINTF_H
