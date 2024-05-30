#include <stdio.h>
#include <stdlib.h>
#include "lib.h"
#define MAX_ITEMS 50
#define MAX_CHAR 20
#define MAX_STOCK 100

herramienta obj;

void printMenu()
{
    int op,salir,i,id,longitud,copiaId[MAX_ITEMS];
    longitud=MAX_ITEMS;
    salir=1;
    i=0;
    do
    {
        printf("Bienvenido usuario! Elige tu operacion (SOLO OPCIONES VALIDAS) \n");
        printf("\n 0) Cerrar \n");
        printf("\n 1) Agregar herramienta \n");
        printf("\n 2) Listar inventario \n");
        printf("\n 3) Lista de todas las herramientas \n");
        fflush(stdin);
        scanf("%d",&op);
        system("cls");

        //si el usuario ingresa 0, nos salteamos la ejecución a iterar para pasar a comprobar la condición del
        //do while
        if(op==0)
        {
            salir=0;
            break;
        }
        else
        {
            switch(op)
            {
            case 1:
                leerHerramientas(i);
                salir=1;
                break;

            case 2:
                printf("Ingrese el identificador de la herramienta \n");
                fflush(stdin);
                scanf("%d",&id);
                listarHerramienta(id);
                break;

            case 3:
                listadoHerramientas();

                break;

            }
        }
        copiarVector(obj.id,copiaId,longitud);
        ordenarId(copiaId,longitud);
        i++;
    }
    while(op<1 || op>3 || salir==1);


}

//este vector copia el contenido "desordenado" que tiene obj.id[] para poder con dicha copia procesarlo en ordenarId(). proceso que puede servir mas adelante
void copiarVector(int vectorLeido[MAX_ITEMS],int vectorCopiado[MAX_ITEMS], int longitud)
{
    int i;
    for(i=0; i<longitud; i++)
    {
        vectorCopiado[i]=vectorLeido[i];
    }
}

//pasamos como parámetro la posición iterada en la que se encuentra el usuario al momento de realizar la operación
herramienta leerHerramientas(int iteracion)
{
    printf("Ingrese el identificador de la herramienta \n");
    fflush(stdin);
    scanf("%d",&obj.id[iteracion]);
    printf("Ingrese el nombre de la herramienta \n");
    fflush(stdin);
    gets(obj.nombre[iteracion]);
    printf("Ingrese el stock disponible \n");
    fflush(stdin);
    scanf("%d",&obj.stock[iteracion]);

}

//pasamos como parámetro el contenido del id que el usuario desea encontrar en nuestro array de datos estructurados
herramienta listarHerramienta(int id_buscado)
{
    int contador;
    contador=0;
    //si id_buscado es diferente que obj.id[contador], incrementamos el contador hasta como límite la longitud máxima de la lista
    while(id_buscado!=obj.id[contador] && contador<MAX_ITEMS)contador++;
    //si el contador se detiene antes de completar la lista quiere decir que encontramos la coincidencia, por ende procedemos a imprimir los datos
    if(contador<MAX_ITEMS)
    {
        printf("ID HERRAMIENTA: %d \n",obj.id[contador]);
        printf("NOMBRE HERRAMIENTA: %s \n",obj.nombre[contador]);
        printf("STOCK DISPONIBLE: %d \n",obj.stock[contador]);

    }
}


herramienta listadoHerramientas()
{
    int i;
    i=0;
    //imprimimos todas aquellas herramientas que no se encuentren vacías. (vacías estarían si su id fuese 0, restricción necesaria)
    while(i<MAX_ITEMS && obj.id[i]!=0)
    {
            printf("\n ID DE HERRAMIENTA: %d \n",obj.id[i]);
            printf("\n NOMBRE DE HERRAMIENTA: %s \n",obj.nombre[i]);
            printf("STOCK DISPONIBLE: %d \n",obj.stock[i]);
            i++;
    }
}

//procedimiento de ordenamiendo del vector identificador por método de inserción
void ordenarId(int id[], int longitud)
{
    int i, clave, j;

    for(i=1; i<longitud; i++)
    {
        clave=id[i];
        j=i-1;

        while(j>=0 && id[j]>clave)
        {
            id[j+1]=id[j];
            j-=1;
        }
        id[j+1]=clave;
    }
}




