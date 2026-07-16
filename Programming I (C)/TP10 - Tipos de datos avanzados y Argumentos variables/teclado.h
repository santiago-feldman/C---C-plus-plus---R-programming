
/***************************************************************************//**
  @file     teclado.h
  @brief    Header con los datos para utilizar el teclado
  @author   Grupo 5
 ******************************************************************************/

#ifndef TECLADO_H
#define TECLADO_H


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define ERROR 'E'                                                       //Valor del error
#define NUMBER(x) ((x)>= ('0')&&((x)<=('7')))                           //Se determina si es un número válido


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
/**
 * @brief TODO: Módulo que analiza lo ingresado por el usuario con el teclado
 * @return Devuelve un char que indica si hubo error, o en caso de que no hubiese, 
 *         el carácter válido ingresado
*******************************************************************************
 ******************************************************************************/
    char teclado (void); 
    
    
    
#endif /* TECLADO_H */

