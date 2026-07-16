#include <stdio.h>

int main (void)
{ 
	int m=15;                   // Filas
	int n=5;                    // Columnas
 	int a=1;                    // Primer numero de la matriz
 	int contf=m;                // Contador de filas 
 	int contc;	                // Contador de columnas
 	
 	if ( m <=0 || n<=0)         // Chequea si las columnas y filas son 0 o negativas
 	{
 		printf ("Error\n");     // En ese caso indica error 
 	}	
	else                        // Si las columnas y filas son positivas no hay error
	{
		while (contf > 0)  				// Chequea si ya se escribieron todas las filas 
		{
			
			for (contc=n; contc>0; --contc)		// Inicializa el contador de columnas, evalua si ya se escribieron todos los numeros de la fila y luego, decrementa en uno el contador
			{
				printf ("|%d|\t", a++);     // Imprime los numeros
			}
			
			printf ("\n");  // Hace un enter para que pase a la siguiente fila
			a = a-n+1;      // Corrige el valor del primer numero para cada fila 
            contf--;        // Decrementa en uno el contador de filas
        }
    }

return 0;
} 

