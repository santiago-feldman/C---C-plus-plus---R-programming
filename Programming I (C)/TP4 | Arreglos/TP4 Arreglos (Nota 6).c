#include	<stdio.h>

/* CONSTANTES */
#define	LARGO		4						//Filas
#define	ANCHO		4						//Columnas
#define	ENTER		10						//Constante con el valor ascii del enter
#define	PUNTO		250						//Constante con el valor ascii del punto
#define	ASCII		48						//Constante con el valor de la diferencia entre los ascii y los números
#define	QUIT		113						//Constante con el valor de la letra 'q'
#define	QUIT_YES	-113						//Constante que indica que termina el programa
#define	ERROR		-1						//Constante que indica que ocurrió un error
#define	MUERTA	32						//Constante que indica que la célula está muerta	
#define	VIVA		42						//Constante que indica que la célula está viva

/*PROTOTIPOS */
int	teclado	(void);						//Prototipo de la función teclado
void	set_cell_state	(int	mat[][ANCHO],int	largo);	//Prototipo de la función set_cell_state 
void	imprime	(int	mat[][ANCHO],int	largo);		//Prototipo de la función imprime 

/* FUNCION PRINCIPAL */

int	main()
{
	int	i=0;									//Índice de filas
	int	j=0;									//Índice de columnas
	int	generacion;								//Cantidad de generaciones
	int	k;									//Índice elementos del arreglo
	int	fil;									//Contador de filas 
	int	col;									//Contador de columnas  
	int	mundo[LARGO][ANCHO]={0};					//Definición de la matriz
	int	arr[]={VIVA,MUERTA,VIVA,MUERTA,MUERTA,VIVA,VIVA};	//Patrón de vivas y muertas 
	
	/* INTRODUCCIÓN DEL JUEGO AL USUARIO*/
	printf	("Bienvenido al Juego de la Vida\n");
	printf	("Ingrese el número de generaciones a avanzar, si presiona 'enter' solamente avanzará una generación\n");
	printf	("Si desea terminar el programa presione la tecla 'q'\n");
	printf	("\nAquí está su mundo incial\n");
	


	/* SE DEFINE EL MUNDO INICIAL */
	for	(fil=LARGO;fil >= 0;--fil)										//Se toma cada fila  del mundo hasta llegar a todas
	{		
			for	(col=ANCHO;col >= 0;--col)								//Se toma cada columna del mundo  hasta llegar a todas
			{
				for	(k=0;k<(sizeof(arr)/sizeof(int));++k)					//Ciclo que se realiza la cantidad de elementos del patrón 
				{
	
					mundo[i][j]=arr[k];								//Se manda los elementos del patrón a la matriz
					++j;											//Se pasa a la siguiente columna
				}
			}
		++i;														//Se pasa a la siguiente fila 
	}
	
	imprime	(mundo,LARGO);											//Se imprime el estado inicial del mundo					
	
	
	
	/* SE DETERMINA LAS GENERACIONES A AVANZAR */  	
	printf	("¿Cuantas generaciones desea avanzar?\n");						//Se pregunta al usuario la cantidad de generaciones a avanzar
	printf	("Si desea terminar el programa presione la tecla 'q'\n");				//Se informa al usuario como terminar el programa 
	generacion=teclado ();
																//Se obtiene el número ingresado por el teclado
	while	(generacion!=QUIT_YES)											//Mientras que no se haya tocado 'q' no finaliza el programa 
	{
		if	(generacion==ERROR)										//Si hubo un carácter inválido termina el programa 
		{
			
			printf("Error, carácter inválido\nIntente Nuevamente\n"); 				//Se informa que hubo un error y cual fue 
												
			generacion=teclado ();										//El usuario debe volver a indicar la generaciones por teclado
		}
		else 										
		{
			while	(generacion!=(QUIT_YES))								//Mientras que no se haya tocado 'q' no finaliza el programa
			{
				
				if	(generacion!=ERROR)								//Si no hubo caracteres inválidos, se avanza las generaciones ingresadas
				{  
					while	((generacion>0))								//Ciclo que determina el estado de la nueva generación la cantidad de veces ingresadas en el teclado
					{
						set_cell_state(mundo,LARGO);						//Función que define la nueva generación
						--generacion;								//Se disminuye el contador de cantidad de veces ingresadas
					}
					imprime(mundo, LARGO);								//Se imprime el estado de la matriz de la generación ingresada
					printf("¿Cuantas generaciones desea avanzar?\n");			//Se vuelve a preguntar al usuario la cantidad de generaciones a avanzar
					printf("Si desea terminar el programa presione la tecla 'q'\n");	//Se informa al usuario como terminar el programa 
					generacion=teclado ();								//Se obtiene el número ingresado por teclado y se repite el ciclo hasta que haya error o se toque 'q'
				}
				else 												//Si hubo caracteres inválidos, se avanza las generaciones ingresadas 
				{
					printf("Error, carácter inválido\nIntente Nuevamente\n"); 		//Se informa que hubo un error y cual fue 
												
					generacion=teclado ();								//El usuario debe volver a indicar la generaciones por teclado
				}
		
			
			}
		}
	
	}
	return	0;													//Si se toco la tecla 'q' finaliza el programa 
}


/*FUNCIONES*/
int	teclado	(void)												//Función teclado										
{
	int	c=getchar();												//Variable que toma los valores de ASCII, 
	int	ent=0;													//Variable que toma el valor del número entero ingresado en el teclado

	if	((c<'0'||c>'9')&&(c!=QUIT)&&(c!=ENTER))								//Si el dígito ingresado no es número o la letra q o enter, entonces hay error 
	{	
		while	(c != ENTER)
		{
		ent=ERROR ;													//Se le asigna un valor negativo (que no podría haber sido ingresado por el usuario)
		c=getchar();	
		}		
	}
	else	if	((c>='0'&&c<='9'))										//Si se ingresó un número, entonces se transforma de ascii a entero 
	{
		while	((c!= ENTER)&&(c>='0'&&c<='9'))								//Toma los caracteres hasta encontrar un enter o un carácter inválido
		{
				ent*=10;											//Transformación a ascii
				ent+=c-ASCII;		
				c=getchar();										//Siguiente carácter 			
				
		}
		while	(c!=ENTER)												//Si hubo en la cadena de caracteres un carácter inválido, hay error
		{
			
			ent=ERROR;												//Se le asigna un valor negativo (que no podría haber sido ingresado por el usuario)
			c=getchar ();					
		}
		
	}
	else	if	(c==QUIT)												//Si se ingresó la letra q, el juego termina
	{
		ent=QUIT_YES;												//Se le asigna un valor negativo (que no podría haber sido ingresado por el usuario),para que el main interprete que termina el juego 
		
	}
	else 															//Si se ingresó solamente enter, entonces avanza una generación
	{
		ent=1;
		
	}	
	return ent;														//Devuelve el valor de la generación o error
}



void	imprime	(int	mat[][ANCHO],int	largo)
{

	int	i;														//Índice de filas
	int	j;														//Índice de columnas
	for	(i=0;i<largo;++i)              									//Toma cada fila del mundo  hasta llegar a todas      
	{
		 for	(j=0;j<ANCHO;++j)											//Toma cada columna del mundo hasta llegar a todas
		 {
		     printf("|%c|\t",mat[i][j]); 									//Imprime cada elemento del mundo 
		  
		 }
		 putchar('\n');												//División entre cada fila 
	}

}


void	set_cell_state(int	mat[][ANCHO],int	largo)				//Le entran el mundo con su tamaño y devuelve la nueva generación en otra matriz (a la que le dan la deja intacta)
{
	int	Nueva_Mat[largo][ANCHO];							//En esta nueva matriz, se van colocando los nuevos estados de las células en la próxima generación
	int	Estado_Celula=0;									//Estado de la célula. Se inicializa en 0. 
	int	Celulas_Vivas_Alrededor=0;							//Cantidad de células vivas alrededor. Se inicializa en 0
	int	i;											//i y j son contadores para recorrer todas las células
	int	j;

	for	(j=0;j< ANCHO;++j)								//Se analizarán todas las columnas para 0 <= j <= ANCHO-1
	{
            for	(i=0;i<largo;++i)								//Se analizarán todas las filas para 0 <= i <= LARGO-1
		{
			/*SE ANALIZA EL ESTADO DE LA CÉLULA*/
			if	(mat[i][j]==VIVA)							//La célula está viva
			{
				Estado_Celula=VIVA;
			}
			else 
			{
				Estado_Celula=MUERTA;						//La célula está muerta
			}
            /*SE ANALIZA EL ESTADO DE LAS CÉLULAS ALREDEDOR*/
			if	(j!=0)								//La célula analizada no está en el borde izquierdo
			{
				if	(mat[i][j-1]==VIVA)					//La célula a la izquierda está viva
				{
					    Celulas_Vivas_Alrededor+=1;
				}
				if	((i != 0)&&(mat[i-1][j-1]==VIVA))			//La célula analizada no está en el borde izquierdo ni en el borde superior, y la célula del extremo superior izquierdo está viva
				{
					    Celulas_Vivas_Alrededor+=1;
				}
				if	((i!=(largo-1)&&(mat[i+1][j-1]==VIVA)))		//La célula analizada no está en el borde izquierdo ni en el borde inferior, y la célula del extremo inferior izquierdo está viva
				{
				    Celulas_Vivas_Alrededor+=1;
				}

			}
				
			if	(j!=ANCHO-1)							//La célula analizada no está en el borde derecho
			{
				if	(mat[i][j+1]==VIVA)					//La célula a la derecha está viva
				{
					    Celulas_Vivas_Alrededor+=1;
				}
				if	((i != 0)&&(mat[i-1][j+1]==VIVA))			//La célula analizada no está en el borde derecho ni en el borde superior, y la célula del extremo superior derecho está viva
				{
					    Celulas_Vivas_Alrededor+=1;
				}
				if	((i != largo-1)&&(mat[i+1][j+1]==VIVA))		//La célula analizada no está en el borde derecho ni en el borde inferior, y la célula del extremo inferior derecho está viva
				{
				    Celulas_Vivas_Alrededor+=1;
				}
			}
	
			if	((i!=0)&&mat[i-1][j]==VIVA)					//La célula analizada no está en el borde superior y la célula de arriba está viva
			{
				Celulas_Vivas_Alrededor+=1;
			}

			if	((i != largo-1)&&mat[i+1][j]==VIVA)				//La célula analizada no está en el borde inferior y la célula de abajo está viva
			{
				Celulas_Vivas_Alrededor += 1;
			}

			/*SE ANALIZA EL ESTADO DE LA CÉLULA EN LA PRÓXIMA GENERACIÓN*/
			if	(Celulas_Vivas_Alrededor>3)					//La célula tiene más de tres vecinos vivos; entonces, muere en la próxima generación
			{
				Nueva_Mat[i][j]=MUERTA;
			}
			else if	(Estado_Celula==VIVA)
			{
				if	((Celulas_Vivas_Alrededor==2)||(Celulas_Vivas_Alrededor==3))
				{
				    Nueva_Mat[i][j]=VIVA;					//La célula viva tiene exactamente 2 o 3 vecinos; entonces, vive en la próxima generación
				}	
				else
				{
				    Nueva_Mat[i][j]=MUERTA;					//La célula viva tiene menos de 2 vecinos; entonces, muere en la próxima generación
				}
			}
			else if	(Celulas_Vivas_Alrededor==3)      			//La célula muerta tiene 3 vecinos; entonces, vive en la próxima generación
			{
				Nueva_Mat[i][j]=VIVA;
			}
			else                                        
			{
				Nueva_Mat[i][j]=MUERTA;						//La célula muerta tiene menos de 3 vecinos; entonces, seguirá muerta en la próxima generación

			}
			Celulas_Vivas_Alrededor=0;

		} 
			  
	}
    
    /*SE PASA LA PRÓXIMA GENERACIÓN AL MUNDO ORIGINAL*/
	for	(j=0;j<ANCHO;++j)
	{
		for	(i=0;i< largo;++i)
		{
			mat[i][j]=Nueva_Mat[i][j];
		}
	}		

}
