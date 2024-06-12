#ifndef LIB_H_INCLUDED
#define LIB_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_CHAR 20
typedef struct herramientas{
    int id,stock,estado;
    char nombre[MAX_CHAR];
}herramienta;

herramienta leerHerramientas(int iteracion);
herramienta listarHerramienta(int contador);
herramienta listadoHerramientas();
herramienta prestarHerramienta(int indice);

int buscarId(int id_buscado);
int longitud_de_entero(int entero);
int num_items_reg();


void printMenu();
void cargarHerramientaArch();
void buscarHerramientaArch();
void imprimirHerramienta(FILE * archivo);

#endif // LIB_H_INCLUDED
