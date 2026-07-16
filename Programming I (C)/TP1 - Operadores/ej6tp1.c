#include <stdio.h>

#define MASCARA16 66 // Se crea la mascara para los bits 1 y 6 
#define MASCARA25 36 // Se crea la mascara para los bits 2 y 5

int main (void)
{
    int porta = 62; // Se inicia la variable a comparar  
    
    printf ("%d\n", (porta & MASCARA16) == MASCARA16 || (porta & MASCARA25) == MASCARA25); // Se imprime 1 si los bits 1 y 6 y/o    los bits 2 y 5 de la variable porta contienen un 1. De lo contrario se imprime un 0 

return 0;
}
