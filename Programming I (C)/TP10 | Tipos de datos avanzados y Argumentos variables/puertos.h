/***************************************************************************//**
  @file     puertos.h
  @brief    +Descripcion del archivo+
  @author   +Nombre del autor (ej: Salvador Allende)+
 ******************************************************************************/

#ifndef _PUERTOS_H_
#define _PUERTOS_H_

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
 * @brief TODO: Prende el bit indicado del puerto indicado
 * @param puerto Carácter que indica el puerto
 * @param bit Número de bit
 * @return no devuelve
*/
    void bitSet(char puerto, int bit);


/**
 * @brief TODO: Apaga el bit indicado del puerto indicado
 * @param puerto Carácter que indica el puerto
 * @param bit Número de bit
 * @return no devuelve
*/
    void bitClr(char puerto, int bit);


/**
 * @brief TODO: Accede al bit indicado del puerto indicado
 * @param puerto Carácter que indica el puerto
 * @param bit Número de bit
 * @return Devuelve el bit pedido
*/
    int bitGet(char puerto, int bit);


/**
 * @brief TODO: Cambia  el estado del bit indicado del puerto indicado
 * @param puerto Carácter que indica el puerto
 * @param bit Número de bit
 * @return no devuelve
*/ 
    void  bitToggle(char puerto, int bit);


/**
 * @brief TODO: Enciende los bits indicados por la máscara en el puerto indicado
 * @param puerto Carácter que indica el puerto
 * @param mask  Máscara a utilizar
 * @return no devuelve
*/ 
    void maskOn(char puerto, unsigned int mask);


/**
 * @brief TODO: Apaga los bits indicados por la máscara en el puerto indicado
 * @param puerto Carácter que indica el puerto
 * @param mask  Máscara a utilizar
 * @return no devuelve
*/ 
    void maskOff(char puerto, unsigned int mask);


/**
 * @brief TODO: Cambia el estado de  los bits indicados por la máscara en el puerto indicado
 * @param puerto Carácter que indica el puerto
 * @param mask  Máscara a utilizar
 * @return no devuelve
*/ 
    void maskToggle(char puerto, unsigned int mask);


/*******************************************************************************
 ******************************************************************************/

#endif // _PUERTOS_H_