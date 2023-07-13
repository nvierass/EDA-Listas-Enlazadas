#ifndef funciones_h
#define funciones_h

//Declaracion de estructuras
typedef struct estado{
	int fila;
	int columna;
}estado;

typedef struct nodo {
	estado actual;
	estado anterior;
	struct nodo* siguiente;
}nodo;

typedef struct datosCola{
	struct nodo* cabeza;
	int fin;
}cola;

//Cabezeras de funciones

//Colas
cola crearCola();
nodo *crearNodo(estado actual,estado anterior);
cola queue(cola colaActual,estado actual,estado anterior);
nodo* buscar(cola actual,estado est);
cola dequeue(cola actual);
void anular(cola actual);
nodo* buscarSiguiente(cola actual);
estado buscarAnterior(cola actual,estado est);
void mostrarCola(cola actual);

//Transiciones
int moverArriba(char** laberinto,int filas,estado actual,estado* siguiente);
int moverAbajo(char** laberinto,int filas,estado actual,estado* siguiente);
int moverDerecha(char** laberinto,int columnas,estado actual,estado* siguiente);
int moverIzquierda(char** laberinto,int columnas,estado actual,estado* siguiente);

//Algoritmo
int comprobarEstado(cola estados,estado est);
int compararEstados(estado a,estado b);
cola abrirEstado(cola estadosAbiertos,estado nuevoEstado,estado estadoActual);
char** recorrerLaberinto(char** laberinto,int filas,int columnas,char inicio,char objetivo);
int verificarTransicion(estado actual,estado anterior);
void armarCamino(char** laberinto,int filas,int columnas,char objetivo,cola estadosCerrados,estado inicial,estado final);

//Otras funciones
char** crearLaberinto(int* f,int* c);
void liberarLaberinto(char** laberinto,int filas);
void printLaberinto(char** laberinto,int filas,int columnas,char objetivo);
void printError(char objetivo);
void printTransiciones(int* transiciones,int estadosRecorridos);

#endif