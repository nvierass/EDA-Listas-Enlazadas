#ifndef funciones_c
#define funciones_c

#include "funciones.h"

//Operaciones de Colas
cola crearCola() {
	cola nueva;
	nueva.cabeza = NULL;
	nueva.fin = 0;
	return nueva;
}
nodo *crearNodo(estado actual,estado anterior) {
	nodo* nuevo = (nodo*)malloc(sizeof(nodo));
	if(!nuevo) {
		return NULL;
	}
	nuevo -> actual= actual;
	nuevo -> anterior = anterior;
	nuevo -> siguiente = NULL;
	return nuevo;
}
cola queue(cola colaActual,estado actual,estado anterior) {
	nodo* nuevo = crearNodo(actual,anterior);
	nodo* indice = NULL;
	if(!nuevo) {
		return colaActual;
	}
	nuevo -> siguiente = colaActual.cabeza;
	colaActual.cabeza = nuevo;
	colaActual.fin++;
	return colaActual;
}
nodo* buscar(cola actual,estado est) {
	nodo *indice = actual.cabeza;
	while(indice) {
		if(indice -> actual.fila == est.fila && indice -> actual.columna == est.columna) {
			return indice;
		}
		indice = indice -> siguiente;
	}
	return NULL;
}
cola dequeue(cola actual) {
	nodo *indice = actual.cabeza;
	nodo *auxiliar = NULL;
	int i;
	for(i=0;i<actual.fin-2;i++){
		indice=indice -> siguiente;
	}
	auxiliar = indice -> siguiente;
	indice -> siguiente = NULL;
	free(auxiliar);
	auxiliar=NULL;
	actual.fin--;
	return actual;
	}
void anular(cola actual) {
	while(actual.fin > 0) {
		actual=dequeue(actual);
	}
}
nodo* buscarSiguiente(cola actual){
	nodo* indice=actual.cabeza;
	int i;
	for(i=0;i<actual.fin-1;i++){
		indice = indice -> siguiente;
	}
	return indice;
}
estado buscarAnterior(cola actual,estado est){
	nodo* aux=buscar(actual,est);
	estado buscado = aux->anterior;
	nodo* indice=actual.cabeza;
	while (indice){
		if(compararEstados(buscado,indice->actual)){
			return indice -> actual;
		}
		indice=indice->siguiente;
	}
}
void mostrarCola(cola actual){
	nodo* indice = actual.cabeza;
	int i=0;
	while (indice){
		printf("En la posicion %d se encuentra el estado %d,%d que viene desde %d,%d\n",i,indice->actual.fila,indice->actual.columna,indice->anterior.fila,indice->anterior.columna);
		indice=indice->siguiente;
		i++;
	}
}

//Transciciones
int moverArriba(char** laberinto,int filas,estado actual,estado* siguiente){
	//Se verifica si nos encontramos en la primera fila del laberinto
	if(actual.fila==0){
		//Se analiza si la posicion al final de la columna permite mover arriba
		if( laberinto[filas-1][actual.columna]!='*' ){
			siguiente->fila=filas-1;
			siguiente->columna=actual.columna;
			return 1;
		}
		return 0;
	}
	else if( (actual.fila>0) && (actual.fila<=filas-1)){
		if( laberinto[actual.fila-1][actual.columna]!='*' ){
			siguiente->fila=actual.fila-1;
			siguiente->columna=actual.columna;
			return 1;
		}
		else{
			return 0;
		}
	}
	return 0;
}
int moverAbajo(char** laberinto,int filas,estado actual,estado* siguiente){
	//Se verifica si nos encontramos en la ultima fila del laberinto
	if(actual.fila==filas-1){
		//Se analiza si la posicion al comienzo de la columna permite moverse abajo
		if( laberinto[0][actual.columna]!='*' ){
			siguiente->fila=0;
			siguiente->columna=actual.columna;
			return 1;
		}
	}
	else if( (actual.fila>=0) && (actual.fila<filas-1)){
		if( laberinto[actual.fila+1][actual.columna]!='*' ){
			siguiente->fila=actual.fila+1;
			siguiente->columna=actual.columna;
			return 1;
		}
		else{
			return 0;
		}
	}
	return 0;
}
int moverDerecha(char** laberinto,int columnas,estado actual,estado* siguiente){
	//Se verifica si estamos en la columna final
	if(actual.columna==(columnas-1)){
		//Se analiza si la posicion al comienzo de la fila permite moverse hacia la derecha
		if( laberinto[actual.fila][0]!='*'){
			siguiente->fila=actual.fila;
			siguiente->columna=0;
			return 1;
		}
		return 0;
	}
	else if( (actual.columna>=0) && (actual.columna<columnas-1) ){
		if( laberinto[actual.fila][actual.columna+1]!='*' ){
			siguiente->fila=actual.fila;
			siguiente->columna=actual.columna+1;
			return 1;
		}
		else{
			return 0;
		}
	}
	return 0;
}
int moverIzquierda(char** laberinto,int columnas,estado actual,estado* siguiente){
	//Se verifica si estamos en la columna inicial
	if(actual.columna==0){
		//Se analiza si la posicion al final de la fila permite moverse hacia la izquierda
		if( laberinto[actual.fila][columnas-1]!='*'){
			siguiente->fila=actual.fila;
			siguiente->columna=columnas-1;
			return 1;
		}
		return 0;
	}
	else if( (actual.columna>0) && (actual.columna<=columnas-1) ){
		if( laberinto[actual.fila][actual.columna-1]!='*' ){
			siguiente->fila=actual.fila;
			siguiente->columna=actual.columna-1;
			return 1;
		}
		else{
			return 0;
		}
	}
	return 0;
}

//Algoritmo
int comprobarEstado(cola estados,estado est){
	nodo* indice=buscar(estados,est);
	if(indice){
		return 1;
	}
	return 0;
}
int compararEstados(estado a,estado b){
	if(a.fila==b.fila && a.columna==b.columna){
		return 1;
	}
	return 0;
}
cola abrirEstado(cola estadosAbiertos,estado nuevoEstado,estado estadoActual){
	return queue(estadosAbiertos,nuevoEstado,estadoActual);
}
char** recorrerLaberinto(char** laberinto,int filas,int columnas,char inicio,char objetivo){
	int i,j;
	cola estadosAbiertos=crearCola();
	cola estadosCerrados=crearCola();

	estado siguiente;
	estado actual;
	estado anterior;
	anterior.fila=-1;
	anterior.columna=-1;

	estado inicial;
	estado final;
	//Recorrer el laberinto para encontrar el estado inicial y el final.
	for(i=0;i<filas;i++){
		for(j=0;j<columnas;j++){
			if(laberinto[i][j]==inicio){
				inicial.fila=i;
				inicial.columna=j;
			}
			else if(laberinto[i][j]==objetivo){
				final.fila=i;
				final.columna=j;
			}
		}
	}

	//Se abre el estado inicial
	abrirEstado(estadosAbiertos,inicial,anterior);

	actual.fila=inicial.fila;
	actual.columna=inicial.columna;
	while(compararEstados(actual,final)==0){
		estadosCerrados=queue(estadosCerrados,actual,anterior);
		printf("El estado actual es %d,%d\n",actual.fila,actual.columna);
		if (moverArriba(laberinto,filas,actual,&siguiente)==1){
			if(comprobarEstado(estadosCerrados,siguiente)==0 && comprobarEstado(estadosAbiertos,siguiente)==0 ){
				estadosAbiertos=abrirEstado(estadosAbiertos,siguiente,actual);
				printf("Se ha abierto el estado %d,%d proveninente de %d,%d moviendose arriba\n",siguiente.fila,siguiente.columna,actual.fila,actual.columna);
			}
		}
		if(moverDerecha(laberinto,columnas,actual,&siguiente)==1){
			if(comprobarEstado(estadosCerrados,siguiente)==0 && comprobarEstado(estadosAbiertos,siguiente)==0 ){
				estadosAbiertos=abrirEstado(estadosAbiertos,siguiente,actual);
				printf("Se ha abierto el estado %d,%d proveninente de %d,%d moviendose a la derecha\n",siguiente.fila,siguiente.columna,actual.fila,actual.columna);
			}
		}
		if (moverAbajo(laberinto,filas,actual,&siguiente)==1){
			if(comprobarEstado(estadosCerrados,siguiente)==0 && comprobarEstado(estadosAbiertos,siguiente)==0 ){
				estadosAbiertos=abrirEstado(estadosAbiertos,siguiente,actual);
				printf("Se ha abierto el estado %d,%d proveninente de %d,%d moviendose abajo\n",siguiente.fila,siguiente.columna,actual.fila,actual.columna);
			}
		}
		if(moverIzquierda(laberinto,columnas,actual,&siguiente)==1){
			if(comprobarEstado(estadosCerrados,siguiente)==0 && comprobarEstado(estadosAbiertos,siguiente)==0 ){
				estadosAbiertos=abrirEstado(estadosAbiertos,siguiente,actual);
				printf("Se ha abierto el estado %d,%d proveninente de %d,%d moviendose a la izquierda\n",siguiente.fila,siguiente.columna,actual.fila,actual.columna);
			}
		}
		if(estadosAbiertos.fin==0){
			printError(objetivo);
			return NULL;
		}
		nodo* siguienteNodo=buscarSiguiente(estadosAbiertos);
		anterior=siguienteNodo->anterior;
		siguiente=siguienteNodo->actual;
		estadosAbiertos=dequeue(estadosAbiertos);
		actual.fila=siguiente.fila;
		actual.columna=siguiente.columna;
	}
	estadosCerrados=queue(estadosCerrados,actual,anterior);
	armarCamino(laberinto,filas,columnas,objetivo,estadosCerrados,inicial,final);
	anular(estadosCerrados);
	anular(estadosAbiertos);
	return laberinto;
}
int verificarTransicion(estado actual,estado anterior){
	if(actual.fila==anterior.fila){
		if((actual.columna-anterior.columna)==1){
			return 2;
		}
		if((actual.columna-anterior.columna)==-1){
			return 4;
		}
		if((actual.columna-anterior.columna)==actual.columna){
			return 4;
		}
		if((actual.columna-anterior.columna)==-anterior.columna){
			return 2;
		}
	}
	if(actual.columna==anterior.columna){
		if((actual.fila-anterior.fila)==1){
			return 3;
		}
		if((actual.fila-anterior.fila)==-1){
			return 1;
		}
		if((actual.fila-anterior.fila)==actual.fila){
			return 1;
		}
		if((actual.fila-anterior.fila)==-anterior.fila){
			return 3;
		}
	}
}
void armarCamino(char** laberinto,int filas,int columnas,char objetivo,cola estadosCerrados,estado inicial,estado final){
	estado actual=final;
	estado anterior=buscarAnterior(estadosCerrados,final);
	int* transiciones=(int*)malloc(estadosCerrados.fin*sizeof(int));
	int estadosRecorridos=0;
	int transicionRealizada;
	while(compararEstados(anterior,inicial)==0){
		transicionRealizada=verificarTransicion(actual,anterior);
		transiciones[estadosRecorridos]=transicionRealizada;
		estadosRecorridos++;
		laberinto[anterior.fila][anterior.columna]='X';
		actual=anterior;
		anterior=buscarAnterior(estadosCerrados,actual);
	}
	transicionRealizada=verificarTransicion(actual,anterior);
	transiciones[estadosRecorridos]=transicionRealizada;
	estadosRecorridos++;
	printLaberinto(laberinto,filas,columnas,objetivo);
	printTransiciones(transiciones,estadosRecorridos);
	free(transiciones);
}

//Otras funciones
char** crearLaberinto(int* f,int* c){
	//Se abre el archivo y se leen las dimensiones del laberinto.
	FILE* archivoEntrada = fopen("Entrada.in","r");
	if(!archivoEntrada){
		printError('A');
		return NULL;
	}
	int filas,columnas;
	fscanf(archivoEntrada,"%d",&filas);
	fscanf(archivoEntrada,"%d",&columnas);
	*f=filas;
	*c=columnas;

	//Asignacion de memoria para la matriz de carateres.

	char** laberinto = (char**)malloc(filas*sizeof(char*));
	int i,j;
	for(i=0;i<filas;i++){
		laberinto[i]=(char*)malloc(columnas*sizeof(char));
	}
	fgetc(archivoEntrada);//Para eliminar el salto de linea inicial
	//Una vez creada la matriz, se recorre caracter a caracter el texto del archivo de entrada, y se almacena en la matriz.
	for(i=0;i<filas;i++){
		for(j=0;j<columnas;j++){
			laberinto[i][j]=fgetc(archivoEntrada);
		}
		char caracter=fgetc(archivoEntrada);//Para eliminar los saltos de linea al final de cada una.
	}
	fclose(archivoEntrada);
	return laberinto;
}
void liberarLaberinto(char** laberinto,int filas){
	int i;
	for(i=0;i<filas;i++){
		free(laberinto[i]);
	}
	free(laberinto);
}
void printLaberinto(char** laberinto,int filas,int columnas,char objetivo){
	int i,j;
	if (objetivo=='K'){
		FILE* archivoSalida=fopen("Salida.out","w");
		for(i=0;i<filas;i++){
			for(j=0;j<columnas;j++){
				fprintf(archivoSalida,"%c",laberinto[i][j]);
			}
			fprintf(archivoSalida,"\n");
		}
		fprintf(archivoSalida,"\n");
		fclose(archivoSalida);
	}
	else if (objetivo=='S'){
		FILE* archivoSalida=fopen("Salida.out","a");
		for(i=0;i<filas;i++){
			for(j=0;j<columnas;j++){
				fprintf(archivoSalida,"%c",laberinto[i][j]);
			}
			fprintf(archivoSalida,"\n");
		}
		fprintf(archivoSalida,"\n");
		fclose(archivoSalida);
	}
}
void printError(char objetivo){
	FILE* archivoSalida;
	if (objetivo=='K'){
		archivoSalida=fopen("Salida.out","w");
		fprintf(archivoSalida,"No se ha encontrado solucion desde E hasta K\n\n");
	}
	else if(objetivo=='S'){
		archivoSalida=fopen("Salida.out","a");
		fprintf(archivoSalida,"No se ha encontrado solucion desde K hasta S\n");
	}
	fclose(archivoSalida);
	if(objetivo=='A'){
		archivoSalida=fopen("Salida.out","w");
		fprintf(archivoSalida,"No se ha encontrado un archivo de entrada valido\n\n");
	}
}
void printTransiciones(int* transiciones,int estadosRecorridos){
	FILE* archivoSalida=fopen("Salida.out","a");
	int i;
	for(i=estadosRecorridos-1;i>=0;i--){
		if(transiciones[i]==1){
			fprintf(archivoSalida,"Arriba\n");
		}
		if(transiciones[i]==2){
			fprintf(archivoSalida,"Derecha\n");
		}
		if(transiciones[i]==3){
			fprintf(archivoSalida,"Abajo\n");
		}
		if(transiciones[i]==4){
			fprintf(archivoSalida,"Izquierda\n");
		}
	}
	fprintf(archivoSalida,"\n");
	fclose(archivoSalida);
}

#endif
