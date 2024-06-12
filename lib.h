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

int buscarId(int id_buscado);
int longitud_de_entero(int entero);
int num_items_reg();


void printMenu();
void cargarHerramientaArch();
void buscarHerramientaArch(int idBuscado);
void imprimirHerramienta(FILE * archivo);
void prestarHerramientaArch();
void resetArchivo();

#endif // LIB_H_INCLUDED
