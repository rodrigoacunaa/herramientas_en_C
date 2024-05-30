#include <stdio.h>
#include <stdlib.h>
#define MAX_ITEMS 50
#define MAX_CHAR 20
#include "lib.h"
herramienta obj;
void printMenu(){
    int op,salir,i,id;
    salir=1;
    i=0;
    do{
        printf("Bienvenido usuario! Elige tu operacion (SOLO OPCIONES VALIDAS)\n");
        printf("1) Agregar herramienta \n");
        printf("2) Listar inventario \n");
        printf("3) Lista de todas las herramientas \n");
        fflush(stdin);
        scanf("%d",&op);
        system("cls");
        if(op==0){
            salir=0;
            break;
        }else{
            switch(op){
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
        i++;
    }while(op<1 || op>3 || salir==1);


}


herramienta leerHerramientas(int iteracion){
        printf("Ingrese el identificador de la herramienta \n");
        fflush(stdin); scanf("%d",&obj.id[iteracion]);
        printf("Ingrese el nombre de la herramienta \n");
        fflush(stdin); gets(obj.nombre[iteracion]);
        printf("Ingrese el stock disponible \n");
        fflush(stdin); scanf("%d",&obj.stock[iteracion]);

}

herramienta listarHerramienta(int id_buscado){
        int contador;
        contador=0;
        while(id_buscado!=obj.id[contador] && contador<MAX_ITEMS)contador++;
        if(contador<MAX_ITEMS){
            printf("ID HERRAMIENTA: %d \n",obj.id[contador]);
            printf("NOMBRE HERRAMIENTA: %s \n",obj.nombre[contador]);

        }
}

herramienta listadoHerramientas(){
        int i;
        i=0;
        while(i<MAX_ITEMS){
            printf("\n NOMBRE DE HERRAMIENTA N %d: %s \n",obj.id[i],obj.nombre[i]);
            printf("STOCK DISPONIBLE: %d \n",obj.stock[i]);
            i++;
        }
}




