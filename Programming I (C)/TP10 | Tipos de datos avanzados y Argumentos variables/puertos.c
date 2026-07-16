/***************************************************************************//**
  @file     puertos.c
  @brief    Módulo que contiene las funciones que modifican los puertos
  @author   Grupo 5
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include "puertos.h"            //Header del módulo

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define ERROR 99     
#define MASK1 65280         //Máscara para obtener los 8 bits más significativos
#define MASK2 255           //Máscara para obtener los 8 bits menos significativos

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

typedef struct port8            //Estructura de un puerto de 8 bits
{
        uint8_t bit0 : 1;
        uint8_t bit1 : 1;
        uint8_t bit2 : 1;
        uint8_t bit3 : 1;
        uint8_t bit4 : 1;
        uint8_t bit5 : 1;
        uint8_t bit6 : 1;
        uint8_t bit7 : 1;
} port8_t;

typedef struct port16          //Estructura de un puerto de 16 bits
{
        port8_t puertoA;
        port8_t puertoB;
} port16_t;



/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

static unsigned  int dec2bin( unsigned int num);    
static void asignacion (char puerto, port8_t puertoaux);
static port8_t portselect (char *p_puerto, int *p_bit);



/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

static port8_t puertoA = {0,0,0,0,0,0,0,0};             //Se crea el puerto A
static port8_t puertoB = {1,0,1,0,1,1,0,1};             //Se crea el puerto B
static port16_t puertoD;                                //Se crea el puerto D


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/


/*FUNCIÓN BITSET: Prende el bit indicado del puerto indicado*/
void bitSet(char puerto, int bit)
{   
    
    int *p_bit = &bit;                                      //Puntero al bit
    char *p_puerto = &puerto;                               //Puntero al puerto
    port8_t puertoaux = portselect (p_puerto, p_bit);       //Se define el puerto
    
    switch (bit)
    {
            case 0:
                    puertoaux.bit0 = 1;
                    break;
            case 1:
                    puertoaux.bit1 = 1;
                    break;
            case 2:
                    puertoaux.bit2 = 1;
                    break;
            case 3:
                    puertoaux.bit3 = 1;
                    break;                      //Se enciende el bit indicado
            case 4:
                    puertoaux.bit4 = 1;
                    break;
            case 5:
                    puertoaux.bit5 = 1;
                    break;
            case 6:
                    puertoaux.bit6 = 1;
                    break;
            case 7:
                    puertoaux.bit7 = 1;
                    break;
            default:							//Si el bit no es válido, no se cambia nada
                    break;
    }

        asignacion (puerto, puertoaux);         //Se actualizan los puertos

}



/*FUNCIÓN BITCLR: Apaga el bit indicado del puerto indicado*/
void bitClr(char puerto, int bit)
{
   
    int *p_bit = &bit;                                  //Puntero al bit
    char *p_puerto = &puerto;                           //Puntero al puerto
    port8_t puertoaux = portselect (p_puerto, p_bit);   //Se define el puerto
    switch (bit)
    {
            case 0:
                puertoaux.bit0 = 0;
                break;
            case 1:
                puertoaux.bit1 = 0;
                break;
            case 2:
                puertoaux.bit2 = 0;
                break;
            case 3:
                puertoaux.bit3 = 0;
                break;                  //Se apaga el bit indicado
            case 4:
                puertoaux.bit4 = 0;
                break;
            case 5:
                puertoaux.bit5 = 0;
                break;
            case 6:
                puertoaux.bit6 = 0;
                break;
            case 7:
                puertoaux.bit7 = 0;
                break;
            default:					//Si el bit no es válido, no se cambia nada
                break;
    }
    asignacion (puerto, puertoaux);     //Se actualizan los puertos
   
}



/*FUNCIÓN BITGET: Devuelve el estado del bit indicado del puerto indicado*/
int bitGet(char puerto, int bit)
{

    int *p_bit = &bit;                                      //Puntero al bit
    char *p_puerto = &puerto;                               //Puntero al puerto
    port8_t puertoaux = portselect (p_puerto, p_bit);       //Se define el puerto
    switch (bit)
    {
        case 0:
            return puertoaux.bit0;
            break;
        case 1:
            return puertoaux.bit1;
            break;
        case 2:
            return puertoaux.bit2;
            break;
        case 3:
            return puertoaux.bit3;
            break;                                          //Se devuelve el bit indicado
        case 4:
            return puertoaux.bit4;
            break;
        case 5:
            return puertoaux.bit5;
            break;
        case 6:
            return puertoaux.bit6;
            break;
        case 7:
            return puertoaux.bit7;
            break;
        default:
            return ERROR;									//Si el bit no es válido, devuelve error
            break;		
    }

}



/*FUNCIÓN BITTOGGLE: Cambia el estado del bit indicado del puerto indicado*/
void bitToggle(char puerto, int bit)
{
    int *p_bit = &bit;                                      //Puntero al bit
    char *p_puerto = &puerto;                               //Puntero al puerto
    port8_t puertoaux = portselect (p_puerto, p_bit);       //Se define el puerto
    switch (bit)                                        
    {
        case 0:
            puertoaux.bit0 =! puertoaux.bit0;
            break;
        case 1:
            puertoaux.bit1 =! puertoaux.bit1;
            break;
        case 2:
            puertoaux.bit2 =! puertoaux.bit2;
            break;
        case 3:
            puertoaux.bit3 =! puertoaux.bit3;           //Se cambia el estado del bit
            break;					
        case 4:
            puertoaux.bit4 =! puertoaux.bit4;
            break;
        case 5:
            puertoaux.bit5 =! puertoaux.bit5;
            break;
        case 6:
            puertoaux.bit6 =! puertoaux.bit6;
            break;
        case 7:
            puertoaux.bit7 =! puertoaux.bit7;
            break;
        default:                                            //Si el bit no es válido, no se cambia nada 
            break;
    }
    asignacion (puerto, puertoaux);                          //Se actualizan los puertos
   
}



/*FUNCIÓN MASKON: Enciende los bits indicados por la máscara en el puerto indicado*/

void maskOn(char puerto,  unsigned int mask)
{
    unsigned  int maskbin2= dec2bin(mask&MASK2);            //Bits menos significativos de la máscara en binario
    unsigned  int maskbin1= dec2bin((mask&MASK1)>>8);       //Bits más significativos de la máscara  en binario
    int maskmat[16];                                        //Arreglo donde se guardara la mascara binaria
    int j;                                                  //Índice que indica el tamaño del puerto a modificar
    int i;                                                  //Índice para recorrer la máscara
    port8_t puertoaux;                                      //Puerto de 8 bits auxiliar
    for(i=0; i<8; i++)                                     
    {
            maskmat[i] = (maskbin2%10);                      //Guarda cada bit de la máscara por separado
            maskbin2/= 10;
    }
    for(i=8; i<16; i++)                                     
    {
            maskmat[i] = (maskbin1%10);                      //Guarda cada bit de la máscara por separado
            maskbin1 /= 10;
    }
    i = 0;
    if (puerto == 'A')                                      //Si el puerto es A
    {
        j = 1;                                              //El puerto es de 8 bits
        puertoaux = puertoA;                                //Se toma los valores del puerto A
    }
    else if (puerto == 'B')                                 //Si el puerto es B
    {
        j=1;                                                //El puerto es de 8 bits
        puertoaux = puertoB;                                //Se toma los valores del puerto B
    }
    else if (puerto == 'D')                                 //Si el puerto es D
    {
        j=0 ;                                               //El puerto es de 16 bits
        puertoaux = puertoB;                                //Se toma los valores del puerto del menos significativo
    }
    while (j<2)
    {

        puertoaux.bit0 = puertoaux.bit0||maskmat[i];
        ++i;
        puertoaux.bit1 = puertoaux.bit1||maskmat[i];
        ++i;
        puertoaux.bit2 = puertoaux.bit2||maskmat[i];
        ++i;
        puertoaux.bit3 = puertoaux.bit3||maskmat[i];      //Se encienden los bits indicados
        ++i;
        puertoaux.bit4 = puertoaux.bit4||maskmat[i];
        ++i;
        puertoaux.bit5 = puertoaux.bit5||maskmat[i];
        ++i;
        puertoaux.bit6 = puertoaux.bit6||maskmat[i];
        ++i;
        puertoaux.bit7 = puertoaux.bit7||maskmat[i];
        ++i;
        if (puerto == 'D')                                  //Si el puerto es D
        {
            puerto = 'B';
            asignacion(puerto,puertoaux);                   //Se actualiza B
            puertoaux = puertoA;                            //Se toma los valores del puerto más significativo
            puerto = 'A';
             
        }
        j++;
    }
    asignacion (puerto, puertoaux);

}


/*FUNCIÓN MASKOFF: Apaga los bits indicados por la máscara en el puerto indicado*/
void maskOff(char puerto, unsigned int mask)
{
    unsigned  int maskbin2= dec2bin(mask&MASK2);            //Bits menos significativos de la máscara en binario
    unsigned  int maskbin1= dec2bin((mask&MASK1)>>8);       //Bits más significativos de la máscara  en binario
    int maskmat[16];                                        //Arreglo donde se guardara la mascara binaria
    int j;                                                  //Índice que indica el tamaño del puerto a modificar
    int i;                                                  //Índice para recorrer la máscara
    port8_t puertoaux;                                      //Puerto de 8 bits auxiliar
    for(i=0; i<8; i++)                                     
    {
            maskmat[i] = !(maskbin2%10);                    //Guarda cada bit de la máscara por separado
            maskbin2/= 10;
    }
    for(i=8; i<16; i++)                                     
    {
            maskmat[i] = !(maskbin1%10);                    //Guarda cada bit de la máscara por separado
            maskbin1 /= 10;
    }
    i = 0;
    if (puerto == 'A')                                      //Si el puerto es A
    {
        j = 1;                                              //El puerto es de 8 bits
        puertoaux = puertoA;                                //Se toma los valores del puerto A
    }
    else if (puerto == 'B')                                 //Si el puerto es B
    {
        j=1;                                                //El puerto es de 8 bits
        puertoaux = puertoB;                                //Se toma los valores del puerto B
    }
    else if (puerto == 'D')                                 //Si el puerto es D
    {
        j=0 ;                                               //El puerto es de 16 bits
        puertoaux = puertoB;                                //Se toma los valores del puerto del menos significativo
    }
    while (j<2)
    {

        puertoaux.bit0 = puertoaux.bit0&&maskmat[i];
        ++i;
        puertoaux.bit1 = puertoaux.bit1&&maskmat[i];
        ++i;
        puertoaux.bit2 = puertoaux.bit2&&maskmat[i];
        ++i;
        puertoaux.bit3 = puertoaux.bit3&&maskmat[i];      //Se apagan los bits indicados
        ++i;
        puertoaux.bit4 = puertoaux.bit4&&maskmat[i];
        ++i;
        puertoaux.bit5 = puertoaux.bit5&&maskmat[i];
        ++i;
        puertoaux.bit6 = puertoaux.bit6&&maskmat[i];
        ++i;
        puertoaux.bit7 = puertoaux.bit7&&maskmat[i];
        ++i;
        if (puerto == 'D')                                  //Si el puerto es D
        {
            puerto = 'B';                                   //Se actualiza B
            asignacion (puerto, puertoaux);
            puertoaux = puertoA;                            //Se toman los valores del puerto más significativo 
            puerto = 'A';
        }
        j++;
     }
    asignacion (puerto, puertoaux);                         //Se actualizan los puertos

}



/*FUNCIÓN MASKTOGGLE: Cambia el estado de los bits indicados por la máscara en el puerto indicado*/
void maskToggle(char puerto, unsigned int mask)
{

    unsigned  int maskbin2= dec2bin(mask&MASK2);            //Bits menos significativos de la máscara en binario
    unsigned  int maskbin1= dec2bin((mask&MASK1)>>8);       //Bits más significativos de la máscara  en binario
    int maskmat[16];                                        //Arreglo donde se guardara la mascara binaria
    int j;                                                  //Índice que indica el tamaño del puerto a modificar
    int i;                                                  //Índice para recorrer la máscara
    port8_t puertoaux;                                      //Puerto de 8 bits auxiliar
    for(i=0; i<8; i++)                                     
    {
            maskmat[i] = (maskbin2%10);                     //Guarda cada bit de la máscara por separado
            maskbin2/= 10;
    }
    for(i=8; i<16; i++)                                     
    {
            maskmat[i] = (maskbin1%10);                     //Guarda cada bit de la máscara por separado
            maskbin1 /= 10;
    }
    i = 0;
    if (puerto == 'A')                                      //Si el puerto es A
    {
        j = 1;                                              //El puerto es de 8 bits
        puertoaux = puertoA;                                //Se toma los valores del puerto A
    }
    else if (puerto == 'B')                                 //Si el puerto es B
    {
        j=1;                                                //El puerto es de 8 bits
        puertoaux = puertoB;                                //Se toma los valores del puerto B
    }
    else if (puerto == 'D')                                 //Si el puerto es D
    {
        j=0 ;                                               //El puerto es de 16 bits
        puertoaux = puertoB;                                //Se toma los valores del puerto del menos significativo
    }
    while (j<2)                                 
    {

        puertoaux.bit0 = puertoaux.bit0^maskmat[i];
        ++i;
        puertoaux.bit1 = puertoaux.bit1^maskmat[i];
        ++i;
        puertoaux.bit2 = puertoaux.bit2^maskmat[i];
        ++i;
        puertoaux.bit3 = puertoaux.bit3^maskmat[i];        //Cambia el estado de los bits indicados 
        ++i;
        puertoaux.bit4 = puertoaux.bit4^maskmat[i];
        ++i;
        puertoaux.bit5 = puertoaux.bit5^maskmat[i];
        ++i;
        puertoaux.bit6 = puertoaux.bit6^maskmat[i];
        ++i;
        puertoaux.bit7 = puertoaux.bit7^maskmat[i];
        ++i;
        if (puerto == 'D')                                   //Si el puerto es D
        {
            puerto = 'B';
            asignacion(puerto,puertoaux);                    //Se actualiza B
            puertoaux = puertoA;                             //Se pasa al puerto más significativo
            puerto = 'A';
        }
        j++;
    }
    asignacion (puerto, puertoaux);                          //Se actualizan los valores de los puertos
}



/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/


/*FUNCIÓN DEC2BIN: Pasa un número natural o 0 en decimal a binario*/
unsigned  int dec2bin(unsigned int num)
{
    if(num==0)                                  //Caso base
    {
            return 0;               
    }
    else
    {
            return (10*dec2bin(num/2)+num%2);   //Caso recursivo
    }
}



/*FUNCIÓN ASIGNACION: Actualiza el estado de los puertos*/
static void asignacion (char puerto, port8_t puertoaux)
{
    if (puerto == 'A')                  //Se modifica el puerto A si hubo cambios
    { 
        puertoA = puertoaux;        
    }
    else if (puerto == 'B')             //Se modifica el puerto B si hubo cambios
    {
        puertoB= puertoaux;
    }


    puertoD.puertoA = puertoA;          //Se actualiza el puerto D
    puertoD.puertoB = puertoB;
}   



/*FUNCIÓN PORTSELECT: Determina el puerto a modificar*/
static port8_t portselect (char *p_puerto, int *p_bit)
{
    port8_t puertoaux;
    if (*p_puerto == 'A')                           //Si se indico el puerto A
    { 
        puertoaux = puertoA;                        //Se toma los valores del puerto A
    }
    else if (*p_puerto == 'B')                      //Si se indico el puerto B
    {
        puertoaux= puertoB;                         //Se toma los valores del puerto B
    }
    else if (*p_puerto == 'D')                      //Si se indico el puerto D
    {
        if ((*p_bit > 7)&&(*p_bit < 16))            //Si el bit es válido y se encuentra en el byte más significativo
        {
            puertoaux= puertoA;                     //Entonces se toma los valores del puerto A
            *p_bit -= 8;                            //Se corrige el valor del bit 
            *p_puerto = 'A';                        //Se corrige el puerto
        }
        else if ((*p_bit <= 7) && (*p_bit >= 0))    //Si el bit es válido y se encuentra en el byte menos significativo
        {
            puertoaux = puertoB;                    //Entonces se toma los valroes del puerto B
            *p_puerto = 'B';                        //Se corrige el puerto
        }
    }
    return puertoaux;                               //Se devuelve el puertoaux 
}

