#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include "lib.h"
#define MAX_ITEMS 50
#define MAX_CHAR 20
#define MAX_STOCK 100
#define NOM_ARCHIVO "herramientas.dat"
#define PRESTAMOS "prestamos.dat"

herramienta obj;
char horaInicioJornada[6];
char horaFinJornada[6];

void printMenu()
{
    int op,salir,i,id,idBuscado;
    salir=1;
    i=0;
    printf("---------------------\n Bienvenido Usuario! \n---------------------\n");

    while(strcmp(horaInicioJornada,"")==0 || strcmp(horaFinJornada,"")==0){
        configurar_jornada(horaInicioJornada,horaFinJornada);
    }
    printf("INICIO JORNADA: %s\n",horaInicioJornada);
    printf("FIN JORNADA: %s\n",horaFinJornada);
    do
    {
        printf("Elige tu operacion (SOLO OPCIONES VALIDAS) \n");
        printf("\n 0) Cerrar \n");
        printf("\n 1) Agregar herramienta \n");
        printf("\n 2) Buscar herramienta \n");
        printf("\n 3) Lista de todas las herramientas \n");
        printf("\n 4) Resetear (Vaciamiento) lista \n");
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
                break;

            case 3:
                listarHerramientasArch();
                system("pause");
                break;

            case 4:
                resetArchivo();
                break;
            }
        }
        i++;
    }
    while(op<1 || op>5 || salir==1);


}

//funcion que sirve para diversas validaciones a lo largo del proyecto
//ingresas la variable entera por parámetro y básicamente te dice cuantos dígitos tiene
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
    //char nombre_input[MAX_CHAR];
    do
    {
        printf("Ingrese el identificador de la herramienta (SOLO SE ADMITEN ENTEROS POSITIVOS DE 4 DIGITOS)\n");
        fflush(stdin);
        scanf("%d",&idInput);
    }
    while(idInput<0 || longitud_de_entero(idInput)!=4);
    //validamos que el formato de id sea respetado forzosamente por el usuario
    system("cls");

    if(existeId(idInput)==0)//si el id no está registrado, procedemos
    {
        herramienta obj;
        FILE * archivo;
        archivo=fopen(NOM_ARCHIVO,"ab");
        if(archivo!=NULL)
        {
            obj.id = idInput;//usamos obj.id para guardar el idInput

            //levantamos los demás datos solicitandolos por pantalla
            printf("Ingrese el nombre de herramienta \n");
            fflush(stdin);
            gets(obj.nombre);
            // Convertimos el nombre a mayúsculas
            for (int i = 0; obj.nombre[i]; i++)
            {
                obj.nombre[i] = toupper(obj.nombre[i]);
            }


            printf("Ingrese el stock disponible \n");
            fflush(stdin);
            scanf("%d",&obj.stock);

            fwrite(&obj, sizeof(obj), 1, archivo);

            if(fclose(archivo)==0)
            {
                mensaje_exito("Archivo correctamente guardado!");
                printf("\n");
                return;
            }
            else
            {
                printf("No se pudo guardar el archivo \n");
            }
        }
        else
        {
            error_msj_apertura_archivo();
        }
    }
    else
    {
        mensaje_advertencia("ID ya registrado");
        printf("\n");
    }




}

void listarHerramientasArch()
{
    FILE * archivo = fopen(NOM_ARCHIVO,"rb");
    if(archivo!=NULL)
    {
        //mientras el puntero tenga que leer..
        mensaje_info("HERRAMIENTAS ALMACENADAS");
        printf("\n");
        mensaje_info("-------------------");
        while(!feof(archivo))
        {
            printf("\n");
            imprimirHerramienta(archivo);
        }
        fclose(archivo);
        mensaje_info("-------------------");
        printf("\n");
    }
    else
    {
        error_msj_apertura_archivo();
    }
}

void buscarHerramientaArch(int idBuscado)
{
    int opc;
    FILE *archivo = fopen(NOM_ARCHIVO, "rb");
    if(archivo!=NULL)
    {
        while (!feof(archivo))//mientras el puntero tenga para leer..
        {

            if(fread(&obj, sizeof(obj), 1, archivo)==1)
            {
                if (obj.id == idBuscado)//coincide?
                {
                    //imprimimos datos del id coincidente
                    mensaje_exito("------------------------------------------");
                    printf("\n");
                    printf("ID: %d\n", obj.id);
                    printf("Nombre: %s\n", obj.nombre);
                    if(obj.stock>=0)
                    {
                        printf("Stock: %d\n", obj.stock);
                    }
                    else
                    {
                        mensaje_advertencia("Sin stock");
                        printf("\n");
                    }
                    printf("\n");
                    mensaje_exito("------------------------------------------");
                    printf("\n");
                    fclose(archivo);


                    //damos opciones al usuario para operar con esa herramienta encontrada..
                    do
                    {
                        printf("\n");
                        mensaje_advertencia("Operaciones disponibles:");
                        printf("\n");
                        printf("0) Volver \n");
                        printf("1) Actualizar stock \n");
                        mensaje_peligro("2) Eliminar herramienta \n");
                        printf("3) Prestar \n");
                        fflush(stdin);
                        scanf("%d",&opc);
                        system("cls");
                        if(opc!=0)
                        {
                            switch(opc)
                            {
                            case 1:
                                //implementar procedimiento de modificación de stock..
                                modificar_stock(idBuscado);
                                break;
                            case 2:
                                //implementamos procedimiento de eliminación de la herramienta
                                eliminar_herramienta(idBuscado);
                                break;
                            case 3:
                                //procedimiento prestamo de herramienta
                                registrarPrestamo(idBuscado);
                                break;
                            }
                        }

                    }
                    while(opc!=0);

                    return;

                }
            }

        }
        mensaje_peligro("--------------------------");
        printf("\n");
        mensaje_peligro("Herramienta no encontrada.");
        printf("\n");
        mensaje_peligro("--------------------------");
        printf("\n");
        fclose(archivo);
    }
    else
    {
        error_msj_apertura_archivo();
    }
}

//devuelve la cantidad de registros en la tabla herramientas
int num_items_reg()
{
    FILE *archivo = fopen(NOM_ARCHIVO, "rb");
    int n_actual;
    n_actual=0;

    while (fread(&obj.id, sizeof(obj.id), 1, archivo)==1)n_actual++;
    return n_actual;
}


//busca un id en la tabla herramientas, devuelve 1 si lo encuentra, devuelve 0 si no.
int existeId(idInput)
{
    FILE * archivo = fopen(NOM_ARCHIVO,"rb");
    if(archivo!=NULL)
    {
        while (!feof(archivo)) //mientras el puntero tenga para leer..
        {
            if(fread(&obj, sizeof(obj), 1, archivo)==1)
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
    else
    {
        error_msj_apertura_archivo();
    }
    return 0;//ID no encontrado

}

void imprimirHerramienta(FILE * archivo)
{
    if(fread(&obj,sizeof(obj),1,archivo)==1)
    {
        printf("ID: %d\n", obj.id);
        printf("Nombre: %s\n", obj.nombre);
        if(obj.stock>=0)
        {
            printf("Stock: %d\n", obj.stock);
        }
        else
        {
            mensaje_advertencia("Sin stock");
            printf("\n");
        }
    }
}



void resetArchivo()
{
    FILE *archivo = fopen(NOM_ARCHIVO, "wb");
    if (archivo != NULL)
    {
        fclose(archivo);
        mensaje_exito("El archivo ha sido reseteado exitosamente!");
        printf("\n");
    }
    else
    {
        mensaje_advertencia("Error al intentar resetear el archivo.");
        printf("\n");
    }
}

void modificar_stock(int id)
{
    FILE * archivo = fopen(NOM_ARCHIVO,"rb+");
    int nstk;
    if(archivo)
    {
        while(!feof(archivo))
        {
            if(fread(&obj,sizeof(obj),1,archivo)==1)
            {
                if(obj.id==id)
                {
                    //encontramos la herramienta a modificar stock
                    if(obj.stock>=0)
                    {
                        printf("Stock actual: %d\n",obj.stock);
                    }
                    else
                    {
                        mensaje_advertencia("Stock actual: Sin stock\n");
                    }

                    do
                    {
                        printf("Ingrese el nuevo stock (SOLO VALORES VALIDOS)\n");
                        fflush(stdin);
                        scanf("%d",&nstk);
                    }
                    while(nstk<0);
                    //pisamos el antiguo valor de obj.stock con el nuevo stock ingresado por el usuario
                    obj.stock=nstk;
                    fseek(archivo, -sizeof(obj), SEEK_CUR);
                    fwrite(&obj, sizeof(obj), 1, archivo);
                    fclose(archivo);
                    mensaje_exito("Stock modificado con exito!\n");
                    break;
                }
            }

        }

    }
    else
    {
        error_msj_apertura_archivo();
    }

}

void error_msj_apertura_archivo()
{
    //para los casos en donde if(archivo) resulte falso, notificamos que hubo un error y mostramos el tipo de error detectado por la terminal
    printf("\033[1;31m"); // Rojo brillante
    printf("Error al abrir el archivo. ERROR: '%s' \n",strerror(errno));
    printf("\033[0m"); // Restablecer color

}

void eliminar_herramienta(int id)
{
    herramienta herr;
    FILE *archivo = fopen(NOM_ARCHIVO, "rb");
    FILE *temp = fopen("temp.dat", "wb");
    int encontrado;
    char decision;
    if (!archivo || !temp)
    {
        error_msj_apertura_archivo();
        return;
    }

    //inicialmente asumimos que no se encontraron items a eliminar
    encontrado=0;
    // Mostrar advertencia en rojo
    printf("\033[1;31m"); // Cambiar a rojo
    printf("Esta accion es irreversible. Esta seguro de que desea continuar? (S/N): \n");
    printf("\033[0m"); // Resetear color
    fflush(stdin);
    scanf(" %c",&decision);
    decision=toupper(decision);

    if(decision=='S')
    {
        //leemos el archivo 'original'
        while(fread(&herr,sizeof(herr),1,archivo)==1)
        {
            //mientras herr.id sea != del id consultado para eliminar, copiamos esa herramienta en temp.dat
            if(herr.id!=id)
            {
                fwrite(&herr,sizeof(herr),1,temp);
            }
            else
            {
                //en caso de que el herr.id coincida con el id por borrar..
                encontrado=1;
            }
        }
        fclose(archivo);
        fclose(temp);


        if(encontrado==1)
        {
            remove(NOM_ARCHIVO);
            rename("temp.dat", NOM_ARCHIVO);
            mensaje_exito("Herramienta eliminada con exito!");
            printf("\n");
        }
        else
        {
            remove("temp.dat");
            mensaje_peligro("Herramienta con ID %d no encontrada.", id);
            printf("\n");
        }
    }
    else if(decision=='N')
    {
        printf("Se cancelo la operacion. \n");
    }


}

void mensaje_exito(const char* mensaje)
{
    // Secuencia de escape para color verde
    printf("\033[1;32m"); // \033 es el carácter de escape, [1;32m es el código ANSI para texto verde brillante
    printf(mensaje);
    printf("\033[0m"); // Restablecer el color
}

void mensaje_info(const char* mensaje)
{
    printf("\033[1;34m"); // Azul brillante
    printf(mensaje);
    printf("\033[0m"); // Restablecer color
}
void mensaje_advertencia(const char* mensaje)
{
    printf("\033[1;33m"); // Amarillo brillante
    printf(mensaje);
    printf("\033[0m"); // Restablecer color
}

void mensaje_peligro(const char* mensaje)
{
    printf("\033[1;31m"); // Rojo brillante
    printf(mensaje);
    printf("\033[0m"); // Restablecer color
}

void registrarPrestamo(int herramientaID)
{
    prestamo p;
    herramienta obj;
    int cantidad_input,id_P;
    id_P=0;
    FILE *Parchivo = fopen(PRESTAMOS, "ab");
    FILE *inventario = fopen(NOM_ARCHIVO, "rb");
    if(Parchivo)
    {
        if(inventario!=NULL)
        {
            while (!feof(inventario))//mientras el puntero tenga para leer..
            {

                if(fread(&obj, sizeof(obj), 1, inventario)==1)
                {
                    if (obj.id == herramientaID)//coincide?
                    {
                        do
                        {
                            printf("Cantidad a prestar (SOLO VALORES VALIDOS): \n");
                            fflush(stdin);
                            scanf("%d",&cantidad_input);
                        }
                        while(cantidad_input<0);

                        if(obj.stock>=cantidad_input)
                        {
                            p.prestamoID = generarNuevoIDPrestamo();
                            p.herramientaID = herramientaID;
                            obtenerFechaActual(p.fechaGeneracion);
                            obtenerHoraActual(p.horaPrestamo);
                            strcpy(p.horaDevolucion, ""); // Vacío inicialmente
                            strcpy(p.horaInicioJornada, horaInicioJornada);
                            strcpy(p.horaFinJornada, horaFinJornada);
                            p.cantidad=cantidad_input;
                            fwrite(&p, sizeof(p), 1, Parchivo);
                            mensaje_exito("Prestamo registrado con exito!\n");
                            system("pause");
                            id_P=p.prestamoID;
                            fclose(Parchivo);

                            imprimirPrestamo(id_P,herramientaID);

                        }
                        else
                        {
                            mensaje_advertencia("La cantidad supera el stock disponible! \n");
                            printf("Herramienta: %s \n",obj.nombre);
                            printf("Cantidad disponible: %d \n",obj.stock);
                        }

                    }
                }
            }
        }

    }
    else
    {
        mensaje_peligro("Error al abrir el archivo de prestamos.\n");
    }



}

// Función para generar un nuevo ID de préstamo
int generarNuevoIDPrestamo()
{
    static int idActual = 0;
    return ++idActual;
}

// Función para obtener la fecha actual
void obtenerFechaActual(char *fecha) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    if (tm == NULL) {
        perror("Error obteniendo la hora local");
        strcpy(fecha, "00-00-0000");
    } else {
        sprintf(fecha, "%02d-%02d-%04d", tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);
    }
    //printf("Fecha obtenida: %s\n", fecha);  // Depuración
}

// Función para obtener la hora actual
void obtenerHoraActual(char *hora) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    if (tm == NULL) {
        perror("Error obteniendo la hora local");
        strcpy(hora, "00:00:00");
    } else {
        sprintf(hora, "%02d:%02d:%02d", tm->tm_hour, tm->tm_min, tm->tm_sec);
    }
    //printf("Hora obtenida: %s\n", hora);  // Depuración
}

//Función para configurar el horario de inicio y fin de la jornada laboral
void configurar_jornada(const char *horaInicioJornada, const char *horaFinJornada)
{
    printf("Ingrese la hora de inicio de la jornada (hh:mm) (FORMATO 24 HS):\n");
    fflush(stdin);
    scanf("%s",horaInicioJornada);
    printf("Ingrese la hora de fin de la jornada (hh:mm) (FORMATO 24 HS):\n");
    fflush(stdin);
    scanf("%s",horaFinJornada);
}

void imprimirPrestamo(int id_prestamo,int herramientaID){
    prestamo p;
    herramienta obj;
    FILE *Parchivo = fopen(PRESTAMOS,"rb");
    FILE *inventario = fopen(NOM_ARCHIVO,"rb");
    if(Parchivo!=NULL && inventario!=NULL){
        while(!feof(Parchivo)){
            if(fread(&p, sizeof(p), 1, Parchivo)==1){
                    if(p.prestamoID==id_prestamo){
                    while(!feof(inventario)){
                            if(fread(&obj,sizeof(obj),1,inventario)==1){
                                    if(obj.id==herramientaID){
                                    mensaje_info("-------------------------------\n");
                                    printf("ID PRESTAMO: %d\n",p.prestamoID);
                                    printf("Herramienta solicitada: %s\n",obj.nombre);
                                    printf("Cantidad prestada: %d\n",p.cantidad);
                                    printf("Fecha de prestamo: %s\n",p.fechaGeneracion);
                                    printf("Hora de prestamo: %s\n",p.horaPrestamo);
                                    printf("Inicio jornada: %s\n",p.horaInicioJornada);
                                    printf("Fin jornada: %s\n",p.horaFinJornada);

                                    if(strcmp(p.horaDevolucion,"")==0){
                                        printf("Hora de devolucion: ");
                                        mensaje_advertencia("PENDIENTE\n");
                                    }else{
                                        printf("Hora de devolucion: %s\n",p.horaDevolucion);
                                    }
                                    mensaje_info("-------------------------------\n");
                                }
                            }
                    }
                }
            }


        }
        fclose(Parchivo);
        fclose(inventario);
    }else{
            error_msj_apertura_archivo();
    }
}




