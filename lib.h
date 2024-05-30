#ifndef LIB_H_INCLUDED
#define LIB_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#define MAX_ITEMS 50
#define MAX_CHAR 20
#define MAX_STOCK 100
typedef struct herramientas{
    int id[MAX_ITEMS],stock[MAX_STOCK],estado;
    char nombre[MAX_ITEMS][MAX_CHAR];
}herramienta;

herramienta leerHerramientas(int iteracion);
herramienta listarHerramienta(int id_buscado);
herramienta listadoHerramientas();

void printMenu();
#endif // LIB_H_INCLUDED
