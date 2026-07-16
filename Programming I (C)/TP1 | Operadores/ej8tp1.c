#include <stdio.h>

int main (void)
{
    double num = 2277.4999999999999;                                                // Numero a evaluar 
    int a = num >= 0 ? (num - ((int) num) ? num+1 : num) : num;                     // Función techo 
    int b = num < 0 ?  ((num - (int)num) ? num-1 : num) : num;                      // Función piso
    int c = num < 0 ? ((num - ((int) num)) <= -.5 ? num-1 : num) : ((num - ((int) num)) >= .5 ? num+1 : num);  // Redondeo a un entero 
    int d = num;                                                                    // Función truncado  
    double z = (num * 100);                                                         // Creamos una variable para que sea mas prolijo hacer cuentas
    double e = (z > 0 ? ((z - (int) z) >= .5 ? (((int) (z + 1)) / 100.0) : (((int) z) / 100.0)) : ((z - (int) z) <= -.5 ? (((int) (z - 1)) / 100.0) : (((int) z) / 100.0)));                                                    // Redondeo de dos decimales

    printf ("a= %d\n", a);    // Imprime los resultados obtenidos 
    printf ("b= %d\n", b); 
    printf ("c= %d\n", c);
    printf ("d= %d\n", d);
    printf ("e= %f\n", e);

return 0;
}

// La precisión del codigo es de hasta 16 digitos. Funciona tanto para numeros postivos como negativos. 
