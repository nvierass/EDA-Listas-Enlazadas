#include <stdio.h>
#include <stdlib.h>
#include "funciones.c"
#include "funciones.h"

int main(){
	printf("\n\n\n******************************************\n");
	printf("****Comienzo de ejecucion del programa****\n");
	printf("******************************************\n\n\n");
	int filas,columnas;
	char** laberinto=crearLaberinto(&filas,&columnas);
	if(!laberinto){
		printf("\n\nError en lectura de archivo\n\n");
		getchar();
		return -1;
	}
	if(!recorrerLaberinto(laberinto,filas,columnas,'E','K')){
		printf("\n\n No se ha encontrado K \n\n");
	}
	printf("\n\nSe ha encontrado un camino desde E hasta K\n\n");
	liberarLaberinto(laberinto,filas);
	laberinto=crearLaberinto(&filas,&columnas);
	if(!recorrerLaberinto(laberinto,filas,columnas,'K','S')){
		printf("\n\nNo se ha encontrado S\n\n");
	}
	printf("\n\nSe ha encontrado un camino desde K hasta S\n\n");
	printf("\n\n\n******************************************\n");
	printf("************+Fin del programa*************\n");
	printf("******************************************\n\n\n");
	getchar();
	return 0;
}
