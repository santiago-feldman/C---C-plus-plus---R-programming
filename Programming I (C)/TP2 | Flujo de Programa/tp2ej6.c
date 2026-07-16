#include <stdio.h>

#define NO_PRIMO 0      
#define PRIMO 1       

int main (void)

{ 
    int num = 18;       // Número a analizar, si es primo o no 
	int check;          // Indica si el número es primo o no
	int a;              // Funciona como divisor
	if (num>1)          // Chequea si el número es natural
	{                                  		
		for (a = num-1; a>1 ; --a) // Ciclo que divide al número 
		{        				 
			if ( num%a )           // Si el resto es distinto de 0, no se ha encontrado un divisor del número todavía
			{				
				check = PRIMO;     
			}				
			else                   // Si el resto es 0, se ha encontrado un divisor del número distinto de 1 y sí mismo 
			{				
				check = NO_PRIMO;	
				a = 0; 		       // Sale del ciclo, pues ya se sabe que no es primo
			}
		}	
		switch (check)  // Verifica si es primo o no e imprime la respuesta correcta
		{                               
			case NO_PRIMO: 				
				printf ("%d No es primo\n", num); 
				break;		
			default:
				printf ("%d Es primo\n", num);
				break;	
		}
	}			
	
	else if (num == 1)  // Verifica si el número es igual a 1
    {
		printf ("%d No es primo\n", num);   // El número uno no es primo porque tiene sólo un divisor
    }
	else 
    {
		printf ("%d No es natural\n", num); // Avisa si el número a comparar no es natural
	}
	
return 0;
}
