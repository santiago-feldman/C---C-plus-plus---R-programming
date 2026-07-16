#include <stdio.h>
#define MAX_LET         25                              //Máximo de letras
#define ENTER           10                              //Ascii del enter
#define MAYUS           32                              //Diferencia numérica entre las letras minúsculas con las mayúsculas en ascii
#define A               65                              //Ascii del A mayúscula
#define Z               90                              //Ascii del Z mayúscula
#define a               97                              //Ascii del a minúscula
#define z               122                             //Ascii del z minúscula
#define TACHADO         254                             //Ascii usado para tachar las letras 
#define SIN_ERROR       0                               //Valor de que no hubo error
#define ERROR_CARAC     1                               //Valor de error de carácter inválido
#define ERROR_LARGO     2                               //Valor de error de largo (se sobrepasa del máximo de letras)
#define ERROR_LYC       3                               //Valor de error de carácter inválido y de longitud



/* PROTOTIPOS */
void error_caracter (char letra, int *p_error);                                                  //Prototipo de la función error_caracter
void guarda (char letra, char *p_letra, int i, int *contador_letras, int *p_error);              //Prototipo de la función guarda
void imprime (char palabra[],int maximo);		                                                 //Prototipo de la función imprime 
void check_error (int error);                                                                    //Prototipo de la función check_error
int compara (char p1[], char p2[], int letras_palabra1, int letras_palabra2);                    //Prototipo de la función compara




/*FUNCIÓN PRINCIPAL*/

int main()
{
    char p1[MAX_LET], p2[MAX_LET];                  //Arreglos de las palabras
    char letra = 0;                                 //Variable que toma el ascii de cada letra
    int  error= SIN_ERROR;                          //Variable error
    int  *p_error = &error;                         //Puntero a la variable error 
    char *p_letra;                                  //Puntero a cada posición que guardará las letras
    int  letras_palabra1= 0, letras_palabra2= 0;    //Cantidad de letras en cada palabra
    int  *p_letras_palabra1 = &letras_palabra1;     //Puntero al contador de letras de la primera palabra
    int  *p_letras_palabra2 = &letras_palabra2;     //Puntero al contador de letras de la segunda palabra
    int  i=0;                                       //Índice de los arreglos
    int  letras_comparadas;                         //Cantidad de letras iguales entre la primera palabra y la segunda



    p_letra = p1;                                                           //El puntero de letra apunta al comienzo donde se guarda la primera palabra
    printf ("Ingrese la primera palabra:");                                 //Se pide al usuario ingresar la primera palabra
    
    guarda (letra, p_letra, i, p_letras_palabra1, p_error);                 //Se guarda la primera palabra
    
    p_letra = p2;                                                           //El puntero de letra apunta al comienzo donde se guarda la segunda palabra
    printf ("Ingrese la segunda palabra:");                                 //Se pide al usuario ingresar la segunda palabra
    
    guarda (letra, p_letra, i, p_letras_palabra2, p_error);                 //Se guarda la segunda palabra 
    
    
    letras_comparadas = compara (p1, p2, letras_palabra1, letras_palabra2); //Se compara las letras de la primera palabra con las de la segunda
    
    check_error (error);                                                    //Se chequea si hubo un error, cuál fue y le avisa al usuario
    
    if (error == SIN_ERROR)                                                 //Si no hubo error, entonces se informa el resultado de la comparación
    {
        if (letras_comparadas == letras_palabra2)                           //Si las letras comparas coinciden con la cantidad de letras de la segunda palabra
        {                                                                   //entonces, se puede formar la segunda palabra con letras de la primera 
            printf ("Es posible formar la segunda palabra con letras de la primera palabra\n"); //Se informa la usuario
        }
        else                                                                //Si las letras comparadas no coinciden con las letras de la segunda palabra
        {                                                                   //entocnes, no se puede formar la segunda palabra con letras de la primera
            printf ("No es posible formar la segunda palabra con letras de la primera palabra\n"); //Se informa al usuario
        }
    }

return 0;
}



/*FUNCIONES*/



/*                              GUARDA
    Guarda las letras en memoria en los arreglos creados en la función principal. 
    Esto permite poder acceder a la letras cuando se desee. 
*/

void guarda (char letra, char *p_letra, int i, int *contador_letras, int *p_error)
{
    letra = getchar();                                          //Se toma el primer carácter de la palabra
    error_caracter (letra, p_error);                            //Se chequea si el carácter es inválido
    while (letra != ENTER)                                      //Ciclo que termina cuando finalice la palabra (cuando se haya tocado enter)
    {
           if (*(contador_letras) < MAX_LET)                    //y la palabra no es más grande que el máximo
           {                                                            
            p_letra[i]  = letra;                                //Se guarda la letra en la posición donde comienza la palabra en memoria
            *(contador_letras) += 1;                            //Se incrementa en uno el contador de letras de la palabra
            ++i;                                                //Se apunta a la siguiente posición de memoria 
            letra = getchar();                                  //Se obtiene la siguiente carácter de la palabra
            error_caracter (letra, p_error);                    //Se chequea si el carácter es inválido
           }
           else                                                 //Si la palabra es más grande que el máximo 
           {  
                   while ( letra != ENTER)                      //Mientras que no haya terminado lo escrito 
                   {            
                       letra = getchar ();                      //Se obtiene el siguiente carácter
                       error_caracter (letra, p_error);         //Se chequea si el carácter es inválido
                   }
                   if ( *p_error == ERROR_CARAC)                //Si ya hubo un error de carácter inválido 
                       {
                            *p_error = ERROR_LYC ;              //Entonces, hubo dos errores (carácter inválido y largo)
                       }
                   else  if ( *p_error == SIN_ERROR)            //Si no hubo un error de carácter inválido
                       {
                            *p_error = ERROR_LARGO;             //Entonces, hubo solamente un error de largo
                       }
           }
    }
}



/*                      ERROR_CARACTER
        Se verifica si el carácter ingresado por teclado es inválido.
        Dependiendo de esto, se activa el flag de error o no.
        El programa considera inválido las vocales acentuadas y la letra ñ.
*/

void error_caracter (char letra, int *p_error)
{
    
        if ((( A <= letra) && (letra <= Z)) || ((a <= letra) && (letra <= z)))      
        {
                                                               //Si el carácter es una letra o enter entonces no "se activa" el flag de error
        }
        else if (letra == ENTER)                                                    
        {
            
        }
        else                                                   //Si el carácter no es una letra o enter entonces "se activa" el flag de error  
        {
            if (*p_error == ERROR_LARGO)                       //Si ya hubo un error de largo
            {
                *p_error = ERROR_LYC;                          //Entonces hubo dos errores (carácter inválido y largo)                       
            }
            else if (*p_error == SIN_ERROR)                    //Si no hubo un error de largo
            {
                *p_error = ERROR_CARAC;                        //Entonces, hubo solamente error de carácter inválido
            }
        }

}



/*                       CHECK_ERROR
        Si hubo un error, dependiendo de cual fue se le informa al usuario de esta situación.
*/

void check_error (int error)
{
      switch (error)                            
      {
      case (ERROR_CARAC):                                    //Caso donde solamente hubo un error de carácter
        printf ("Error: Carácter inválido\n");      
        break;
      case (ERROR_LARGO):                                    //Caso donde solamente hubo un error de largo
        printf ("Error: Se ingreso una palabra con más de  25 letras\n");                          
        break;
      case (ERROR_LYC):                                      //Caso donde sucedieron los dos errores (carácter inválido y largo)
        printf ("Error: Carácter inválido\nError: Se ingreso una palabra con más de  25 letras\n"); 
        break;
      default:                                               //Si no se activo el flag error, no informa nada 
        break;
     }
        
}
 


 /*                             COMPARA
        Compara cada letra de la segunda palabra con las de la primera.
        Devuelve la cantidad de letras iguales, que si coincide con
        la cantidad de letras de la segunda palabra, entoces se podrá
        formar la segunda palabra con letras de la primera.
        El programa considera las letras iguales sin importar si una
        alguna está en mayúscula o minúscula. 
 */

int compara (char p1[], char p2[], int letras_palabra1, int letras_palabra2)
{
   int contador_letras_iguales = 0;                         //Contador de letras iguales entre la segunda palabra y la primera
   int k;                                                   //Índice de letras de segunda palabra (del arreglo)
   int j;                                                   //Índice de letras de la primera palabra (del arreglo)
        for (k=0; k < letras_palabra2; ++k)                 //Ciclo para comparar con todas las letras de la segunda palabra
        {
                for (j=0; j < letras_palabra1; ++j)         //Ciclo para comparar con todas las letras de la primera palabra
                {
                    if ( (p1[j] == p2[k]) || (p1[j] == p2[k] - MAYUS) || (p1[j] == p2[k] + MAYUS) )                    
                                                            //Si la letra de la primera palabra es igual a la de la segunda 
                    {                                       //sin diferenciar mayúsculas con minúsculas
                        p1[j] = TACHADO;                    //Se "tacha" la letra de la primera palabra
                                                            //para que no se vuelva a comparar 
                        j = letras_palabra1;                //Se condicion el índice para salir del ciclo 
                        contador_letras_iguales += 1;       //Se incrementa en 1 el contador de letras iguales
                    }
                    
                }
        } 
    return contador_letras_iguales;                          //Se devuelve el contador de letras iguales 
}
         
