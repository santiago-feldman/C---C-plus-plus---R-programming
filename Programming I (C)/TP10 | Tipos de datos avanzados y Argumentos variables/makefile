tp10ej6: main.o teclado.o puertos.o
	gcc main.o teclado.o puertos.o -o tp10ej6 -g -Wall
main.o: main.c teclado.h puertos.h
	gcc main.c -c -Wall
teclado.o: teclado.c teclado.h
	gcc teclado.c -c -Wall
puertos.o: puertos.c puertos.h
	gcc puertos.c -c -Wall
