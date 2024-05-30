#ifndef LIB_H_INCLUDED
#define LIB_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#define MAX_ITEMS 50
#define MAX_CHAR 20
typedef struct herramientas{
    int id,stock,estado;
    char [MAX_ITEMS][MAX_CHAR];
}herramienta;

herramientas leerHerramientas(int cantidad);
void printMenu();
#endif // LIB_H_INCLUDED
