#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lib.h"
#define MAX_ITEMS 50
#define MAX_CHAR 20
#define MAX_STOCK 100
#define NOM_ARCHIVO "herramientas.dat"

herramienta obj;

void printMenu()
{
    int op,salir,i,id,idBuscado;
    salir=1;
    i=0;
    do
    {
        printf("Bienvenido usuario! Elige tu operacion (SOLO OPCIONES VALIDAS) \n");
        printf("\n 0) Cerrar \n");
        printf("\n 1) Agregar herramienta \n");
        printf("\n 2) Buscar herramienta \n");
        printf("\n 3) Lista de todas las herramientas \n");
        printf("\n 4) Prestar herramienta \n");
        printf("\n 5) Resetear (Vaciamiento) lista \n");
        fflush(stdin);
        scanf("%d",&op);
        system("cls");

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
                cargarHerramientaArch();
                printf("\n");
                system("pause");
                salir=1;
                break;

            case 2:
                do
                {
                    printf("Ingrese el identificador de la herramienta (SOLO SE ADMITEN ENTEROS POSITIVOS DE 4 DIGITOS)\n");
                    fflush(stdin);
                    scanf("%d",&idBuscado);
                }
                while(idBuscado<0 || longitud_de_entero(idBuscado)!=4);
                buscarHerramientaArch(idBuscado);
                system("pause");
                break;

            case 3:
                listarHerramientasArch();
                system("pause");
                break;

            case 4:
                idBuscado=0;
                printf("Ingrese el identificador de la herramienta \n");
                fflush(stdin);
                scanf("%d",&idBuscado);
                if(existeId(idBuscado)==1)
                {
//                    printf("ID BUSCADO: %d",idBuscado);
                    //reutilizamos el procedimiento de la op 2 para mostrarle al usuario el formato de la herramienta
                    //buscarHerramientaArch(idBuscado);
                    prestarHerramientaArch(idBuscado);
                }
                break;

            case 5:
                resetArchivo();
                break;

            }
        }
        i++;
    }
    while(op<1 || op>3 || salir==1);


}

int longitud_de_entero(int entero)
{
    if(entero==0)
    {
        return 1;
    }
    return floor(log10(entero))+1;
}

void cargarHerramientaArch()
{
    int idInput;
    do
    {
        printf("Ingrese el identificador de la herramienta (SOLO SE ADMITEN ENTEROS POSITIVOS DE 4 DIGITOS)\n");
        fflush(stdin);
        scanf("%d",&idInput);
    }
    while(idInput<0 || longitud_de_entero(idInput)!=4);
    system("cls");

    if(existeId(idInput)==0)//si el id no está registrado, procedemos
    {
        FILE * archivo;
        archivo=fopen(NOM_ARCHIVO,"ab");
        if(archivo!=NULL)
        {
            obj.id = idInput;//usamos obj.id para guardar el idInput

            printf("Ingrese el nombre de herramienta \n");
            fflush(stdin);
            gets(obj.nombre);

            printf("Ingrese el stock disponible \n");
            fflush(stdin);
            scanf("%d",&obj.stock);

            fwrite(&obj.id, sizeof(obj.id), 1, archivo);
            fwrite(&obj.nombre, sizeof(obj.nombre), 1, archivo);
            fwrite(&obj.stock, sizeof(obj.stock), 1, archivo);

            if(fclose(archivo)==0)
            {
                printf("Archivo correctamente guardado \n");
                return;
            }
            else
            {
                printf("No se pudo guardar el archivo \n");
            }
        }
    }
    else
    {
        printf("ID ya registrado \n");
    }




}

void listarHerramientasArch()
{
    FILE * archivo = fopen(NOM_ARCHIVO,"rb");
    if(archivo!=NULL)
    {
        //mientras el puntero tenga que leer..
        while(!feof(archivo))
        {
            printf("\n");
            imprimirHerramienta(archivo);
        }
        fclose(archivo);
    }
    else
    {
        printf("No se pudo abrir el archivo \n");
    }
}

void buscarHerramientaArch(int idBuscado)
{
    FILE *archivo = fopen(NOM_ARCHIVO, "rb");
    if(archivo!=NULL)
    {
        while (!feof(archivo))//mientras el puntero tenga para leer..
        {

            if(fread(&obj.id, sizeof(obj.id), 1, archivo)==1)
            {
                if (obj.id == idBuscado)//coincide?
                {
                    printf("ID: %d\n", obj.id);//imprimimos el id leido que coincide

                    if(fread(&obj.nombre,sizeof(obj.nombre),1,archivo)==1)
                    {
                        printf("Nombre: %s\n", obj.nombre);
                    }

                    if(fread(&obj.stock,sizeof(obj.stock),1,archivo)==1)
                    {
                        printf("Stock: %d\n", obj.stock);
                    }

                    fclose(archivo);
                    return;

                }
            }

        }
        printf("Herramienta no encontrada \n");
        fclose(archivo);
    }
}


int num_items_reg()
{
    FILE *archivo = fopen(NOM_ARCHIVO, "rb");
    int n_actual;
    n_actual=0;

    while (fread(&obj.id, sizeof(obj.id), 1, archivo)==1)n_actual++;
    return n_actual;


}


int existeId(idInput)
{
    FILE * archivo = fopen(NOM_ARCHIVO,"rb");
    if(archivo!=NULL)
    {
        while (!feof(archivo)) //mientras el puntero tenga para leer..
        {
            if(fread(&obj.id, sizeof(obj.id), 1, archivo)==1)
            {
                if (obj.id==idInput)
                {
                    fclose(archivo);
                    return 1;//ID encontrado
                }
            }
        }
        fclose(archivo);
    }
    return 0;//ID no encontrado

}

void imprimirHerramienta(FILE * archivo)
{

    if(fread(&obj.id,sizeof(obj.id),1,archivo)==1)
    {
        printf("ID: %d\n", obj.id);
    }

    if(fread(&obj.nombre,sizeof(obj.nombre),1,archivo)==1)
    {
        printf("Nombre: %s\n", obj.nombre);
    }

    if(fread(&obj.stock,sizeof(obj.stock),1,archivo)==1)
    {
        printf("Stock: %d\n", obj.stock);
    }
}

void prestarHerramientaArch(int idBuscado)
{
    int cantidadSol,cantidadDisponible;

    FILE *archivo = fopen(NOM_ARCHIVO, "rb+");//modo lectura/escritura binaria "rb+"
    if(archivo!=NULL)
    {
        do
        {

            if(fread(&obj.id, sizeof(obj.id), 1, archivo)==1)
            {
                if (obj.id == idBuscado)//coincide?
                {
                    printf("ID: %d\n", obj.id);//imprimimos el id leido que coincide

                    if(fread(&obj.nombre,sizeof(obj.nombre),1,archivo)==1)
                    {
                        printf("Nombre: %s\n", obj.nombre);
                    }

                    if(fread(&obj.stock,sizeof(obj.stock),1,archivo)==1)
                    {
                        cantidadDisponible=obj.stock;
                        printf("Stock: %d\n", obj.stock);
                    }

                    //fclose(archivo);
                    //return;

                    if(cantidadDisponible==0)
                    {
                        printf("Herramienta sin stock \n");
                    }
                    else
                    {
                        do
                        {
                            printf("\n Ingrese la cantidad a prestar (debe ser <= a la cantidad disponible) \n");
                            fflush(stdin);
                            scanf("%d",&cantidadSol);
                        }
                        while(cantidadDisponible<cantidadSol);

                        //actualizamos la cantidad disponible, es decir, se reduce el stock
                        obj.stock-=cantidadSol;

                        fseek(archivo, -sizeof(obj.stock), SEEK_CUR);
                        //fseek se usa para mover el puntero del archivo hacia atras
                        //con el comando SEEK_CUR, por el tamaño de la estructura obj, de manera
                        //que el siguiente fwrite sobrescriba el registro actual con la actualización
                        fwrite(&obj.stock, sizeof(obj.stock), 1, archivo);

                        //notificamos actualización exitosa
                        printf("Prestamo realizado con exito.\n");
                        printf("Nuevo stock de %s: %d\n", obj.nombre, obj.stock);

                        //cerramos el archivo y finalizamos la función.
                        fclose(archivo);
                        return;

                    }
                }
                else
                {
                    fseek(archivo,sizeof(obj.id),SEEK_CUR);
                }
            }

        }
        while((!(feof(archivo))));
        printf("Herramienta no encontrada \n");
        fclose(archivo);

    }
    else
    {
        printf("No se pudo abrir el archivo \n");
        return;
    }

}

void resetArchivo()
{
    FILE *archivo = fopen(NOM_ARCHIVO, "wb");
    if (archivo != NULL)
    {
        fclose(archivo);
        printf("El archivo ha sido reseteado exitosamente.\n");
    }
    else
    {
        printf("Error al intentar resetear el archivo.\n");
    }
}


