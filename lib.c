#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include "lib.h"
#define MAX_ITEMS 50
#define MAX_CHAR 20
#define MAX_STOCK 100
#define NOM_ARCHIVO "herramientas.dat"
#define PRESTAMOS "prestamos.dat"
#define PRESTAMOS_IDS "prestamos_ids.dat"
#define TEMPORIZADOR_DAT "temporizador.dat"

herramienta obj;
char horaInicioJornada[6];
char horaFinJornada[6];

void printMenu()
{
    int op,salir,i,id,idBuscado;
    char nombre_archivo[20];
    char nombre_archivo2[20];
    salir=1;
    i=0;

    do
    {
        printf("Elige tu operacion (SOLO OPCIONES VALIDAS) \n");
        printf("\n 0) Cerrar \n");
        printf("\n 1) Agregar herramienta \n");
        printf("\n 2) Buscar herramienta \n");
        printf("\n 3) Lista de todas las herramientas \n");
        printf("\n 4) Resetear (Vaciamiento) lista \n");
        printf("\n 5) Historial de prestamos de la jornada \n");
        printf("\n 6) Historial de prestamos semanal \n");
        printf("\n 7) Gestionar usuarios \n");
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
                system("cls");
                break;

            case 4:
                        do{
                        printf("Que tabla desea vaciar? (SOLO OPCIONES VALIDAS)\n");
                        printf("1) TABLA DE INVENTARIO\n");
                        printf("2) TABLA DE PRESTAMOS\n");
                        fflush(stdin);
                        scanf("%d",&op);
                        if(op==1 || op==2){
                            switch (op)
                            {
                            case 1:
                                    strcpy(nombre_archivo,NOM_ARCHIVO);

                                break;

                            case 2:
                                    strcpy(nombre_archivo,PRESTAMOS);

                                    strcpy(nombre_archivo2,PRESTAMOS_IDS);
                                break;

                            default:
                                break;
                            }
                        }
                             }while(op<1 || op>2);
                             resetArchivo(nombre_archivo);
                             resetArchivo(nombre_archivo2);

                break;

            case 5:
                historial_prestamos_jornada();
                break;

            case 6:

                break;

            case 7:
                 print_sub_menu_usuarios();

                break;
            }
        }
        i++;
    }
    while(op<1 || op>5 || salir==1);
}

//funcion que sirve para diversas validaciones a lo largo del proyecto
//ingresas la variable entera por par�metro y b�sicamente te dice cuantos d�gitos tiene
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

    if(existeId(idInput,NOM_ARCHIVO)==0)//si el id no est� registrado, procedemos
    {
        herramienta obj;
        FILE * archivo;
        archivo=fopen(NOM_ARCHIVO,"ab");
        if(archivo!=NULL)
        {
            obj.id = idInput;//usamos obj.id para guardar el idInput

            //levantamos los dem�s datos solicitandolos por pantalla
            printf("Ingrese el nombre de herramienta \n");
            fflush(stdin);
            gets(obj.nombre);
            // Convertimos el nombre a may�sculas
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
                                //implementar procedimiento de modificaci�n de stock..
                                modificar_stock(idBuscado);
                                break;
                            case 2:
                                //implementamos procedimiento de eliminaci�n de la herramienta
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
int existeId(int idInput, char *FILE_NAME)
{
    FILE * archivo = fopen(FILE_NAME,"rb");
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

int existe_dni(int idInput, char *FILE_NAME)
{
    usuario user;
    FILE * archivo = fopen(FILE_NAME,"rb");
    if(archivo!=NULL)
    {
        while (!feof(archivo)) //mientras el puntero tenga para leer..
        {
            if(fread(&user, sizeof(user), 1, archivo)==1)
            {
                if (user.dni==idInput)
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



void resetArchivo(char *file_name)
{
    FILE *archivo = fopen(file_name, "wb");
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
    printf("\033[1;32m"); // \033 es el car�cter de escape, [1;32m es el c�digo ANSI para texto verde brillante
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
    FILE *inventario = fopen(NOM_ARCHIVO, "rb+");
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
                        do{
                            printf("DNI de operario solicitante (FORMATO ACEPTADO: DNI DE ALMENOS 8 ENTEROS)\n");
                            fflush(stdin);
                            scanf("%d",&p.dni_operario);
                        }while(longitud_de_entero(p.dni_operario)<8);

                        if(buscar_operario(p.dni_operario)==0){
                            printf("El operario con dni '%d' no existe, vuelva a intentar\n ",p.dni_operario);
                            mostrar_mensaje_intermitente("Volviendo..",1);
                            buscarHerramientaArch(herramientaID);
                        }else{
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
                                        //printf("ID PRESTAMO: %d\n",p.prestamoID);
                                        p.herramientaID = herramientaID;
                                        obtenerFechaActual(p.fechaGeneracion);
                                        obtenerHoraActual(p.horaPrestamo);
                                        strcpy(p.horaDevolucion, ""); // Vacio inicialmente
                                        strcpy(p.horaInicioJornada, horaInicioJornada);
                                        strcpy(p.horaFinJornada, horaFinJornada);
                                        p.cantidad=cantidad_input;
                                        fwrite(&p, sizeof(p), 1, Parchivo);
                                        obj.stock -= cantidad_input;
                                        fseek(inventario, -sizeof(obj), SEEK_CUR); // Mover puntero hacia atrás
                                        fwrite(&obj, sizeof(obj), 1, inventario); // Reescribir posición con datos actualizados
                                        mensaje_exito("Prestamo registrado con exito!\n");
                                        system("pause");
                                        id_P=p.prestamoID;
                                        fclose(Parchivo);
                                        fclose(inventario);
                                        //printf("ID_P: %d\n",id_P);
                                        imprimirPrestamo(id_P,herramientaID);
                                        break;


                                    }
                                    else
                                    {
                                        mostrar_mensaje_intermitente("La cantidad supera el stock disponible!",1);
                                        printf("Herramienta: %s \n",obj.nombre);
                                        printf("Cantidad disponible: %d \n",obj.stock);
                                        buscarHerramientaArch(herramientaID);

                                    }
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

// Funci�n para generar un nuevo ID de pr�stamo
int generarNuevoIDPrestamo()
{
    if(archivo_vacio(PRESTAMOS_IDS)==1){
        FILE * apuntador = fopen(PRESTAMOS_IDS,"rb+");
        static int id;
        if(apuntador){

        if(fread(&id,sizeof(id),1,apuntador)==0){
            id++;
        }else{
            id=1;
        }

    }else{
        mensaje_peligro("Error al abrir el archivo\n");
    }
    fclose(apuntador);
    return id;
    }else{
        printf("El archivo debe ser creado\n");
        crear_binario(PRESTAMOS_IDS);
    }
}

// Funci�n para obtener la fecha actual
void obtenerFechaActual(char *fecha) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    if (tm == NULL) {
        perror("Error obteniendo la hora local");
        strcpy(fecha, "00-00-0000");
    } else {
        sprintf(fecha, "%02d-%02d-%04d", tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);
    }
    //printf("Fecha obtenida: %s\n", fecha);  // Depuraci�n
}

// Funci�n para obtener la hora actual
void obtenerHoraActual(char *hora) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    if (tm == NULL) {
        perror("Error obteniendo la hora local");
        strcpy(hora, "00:00:00");
    } else {
        sprintf(hora, "%02d:%02d:%02d", tm->tm_hour, tm->tm_min, tm->tm_sec);
    }
    //printf("Hora obtenida: %s\n", hora);  // Depuraci�n
}

//Funci�n para configurar el horario de inicio y fin de la jornada laboral
void configurar_jornada(const char *horaInicioJornada, const char *horaFinJornada)
{
    int formatoCorrecto = 1;
    printf("Ingrese la hora de inicio de la jornada (hh:mm) (FORMATO 24 HS):\n");
    fflush(stdin);
    scanf("%s",horaInicioJornada);
    // Verificar que el formato de hora sea correcto
    if (strlen(horaInicioJornada) != 5 || horaInicioJornada[2] != ':') {
        printf("Formato de hora incorrecto. Debe ser hh:mm\n");
        formatoCorrecto = 0;
    } else {
        int hora = 0, minuto = 0;
        sscanf(horaInicioJornada, "%d:%d", &hora, &minuto);
        if (hora < 0 || hora > 23 || minuto < 0 || minuto > 59) {
            printf("Formato de hora incorrecto. La hora debe estar entre 00 y 23 y los minutos entre 00 y 59\n");
            formatoCorrecto = 0;
        }
    }

    if (formatoCorrecto) {
        printf("Ingrese la hora de fin de la jornada (hh:mm) (FORMATO 24 HS):\n");
        fflush(stdin);
        scanf("%s",horaFinJornada);
        // Verificar que el formato de hora sea correcto
        if (strlen(horaFinJornada) != 5 || horaFinJornada[2] != ':') {
            printf("Formato de hora incorrecto. Debe ser hh:mm\n");
            formatoCorrecto = 0;
        } else {
            int hora = 0, minuto = 0;
            sscanf(horaFinJornada, "%d:%d", &hora, &minuto);
            if (hora < 0 || hora > 23 || minuto < 0 || minuto > 59) {
                printf("Formato de hora incorrecto. La hora debe estar entre 00 y 23 y los minutos entre 00 y 59\n");
                formatoCorrecto = 0;
            }
        }
    }

    if (!formatoCorrecto) {
        // Si el formato de hora no es correcto, devolver 0
        return 0;
    }else{
        //si el formato es correcto

        //si el 'periodos_jornadas' no está vacío...
        if(archivo_vacio("periodos_jornadas.dat")==1){
                FILE *fp = fopen("periodos_jornadas.dat","ab+");
            if(fp){

            }else{
                error_msj_apertura_archivo();
            }
        }else{

        }

    }
}

void imprimirPrestamo(int id_prestamo,int herramientaID){
    prestamo p;
    herramienta obj;
    usuario user;
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
                                    //printf("Inicio jornada: %s\n",p.horaInicioJornada);
                                    //printf("Fin jornada: %s\n",p.horaFinJornada);

                                    if(strcmp(p.horaDevolucion,"")==0){
                                        printf("Hora de devolucion: ");
                                        mensaje_advertencia("PENDIENTE\n");
                                    }else{
                                        printf("Hora de devolucion: %s\n",p.horaDevolucion);
                                    }
                                    mensaje_info("-------------------------------\n");
                                    printf("\n");
                                    printf("Datos del operario solicitante:\n");
                                    mensaje_exito("-------------------------------\n");
                                    FILE *u = fopen("usuarios.dat","rb");
                                    if(u){
                                        while(!feof(u)){
                                            if(fread(&user,sizeof(user),1,u)==1){
                                                if(user.dni==p.dni_operario && user.tipo==2){
                                                    printf("DNI: '%d' \n",user.dni);
                                                    printf("NOMBRE: %s\n",user.nombre);
                                                }
                                            }

                                    }
                                    }else{
                                        printf("ERROR: %s\n",strerror(errno));
                                    }
                                    fclose(u);
                                    mensaje_exito("-------------------------------\n");

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

void historial_prestamos_jornada() {
    prestamo p;
    usuario user;
    FILE *Parchivo = fopen(PRESTAMOS, "rb");
    char fechaActual[11];
    obtenerFechaActual(fechaActual);

    if (Parchivo!= NULL) {
        mensaje_advertencia("Historial de prestamos de la jornada:\n");
        mensaje_info("--------------------------------------------\n");
        while (!feof(Parchivo)) {
            if (fread(&p, sizeof(p), 1, Parchivo) == 1) {
                if (strcmp(p.fechaGeneracion, fechaActual) == 0) {
                    // Imprimir información del préstamo
                    printf("Datos del prestamo '%d': \n", p.prestamoID);
                    mensaje_exito("---------------------------------\n");
                    printf("DNI OPERARIO: %d\n",p.dni_operario);
                    printf("Herramienta solicitada: %s\n", obtenerNombreHerramienta(p.herramientaID));
                    printf("Cantidad prestada: %d\n", p.cantidad);
                    printf("Fecha de prestamo: %s\n", p.fechaGeneracion);
                    printf("Hora de prestamo: %s\n", p.horaPrestamo);
                    //printf("Inicio jornada: %s\n", p.horaInicioJornada);
                    //printf("Fin jornada: %s\n", p.horaFinJornada);
                    if (strcmp(p.horaDevolucion, "") == 0) {
                        printf("Hora de devolucion: PENDIENTE\n");
                    } else {
                        printf("Hora de devolución: %s\n", p.horaDevolucion);
                    }
                    mensaje_exito("---------------------------------\n");
                    //imprimir información del solicitante
                    mensaje_advertencia("Operario solicitante\n");
                        mensaje_info("---------------\n");
                                    FILE *u = fopen("usuarios.dat","rb");
                                    if(u){
                                        while(!feof(u)){
                                        if(fread(&user,sizeof(user),1,u)==1){
                                            if(user.dni==p.dni_operario && user.tipo==2){
                                                printf("DNI: '%d' \n",p.dni_operario);
                                                printf("NOMBRE: %s\n",user.nombre);
                                            }
                                        }

                                    }
                                    }else{
                                        printf("ERROR: %s\n",strerror(errno));
                                    }
                                    fclose(u);
                        mensaje_info("---------------\n");
                        mensaje_advertencia("------------------------------------\n");
                }
            }
        }
        fclose(Parchivo);
        mensaje_info("--------------------------------------------\n");
    } else {
        error_msj_apertura_archivo();
    }
}

char* obtenerNombreHerramienta(int herramientaID) {
    FILE *Harchivo = fopen(NOM_ARCHIVO, "rb");
    herramienta h;
    char* nombreHerramienta = NULL;

    if (Harchivo!= NULL) {
        while (fread(&h, sizeof(h), 1, Harchivo) == 1) {
            if (h.id == herramientaID) {
                nombreHerramienta = strdup(h.nombre);
                break;
            }
        }
        fclose(Harchivo);
    } else {
        error_msj_apertura_archivo();
    }

    return nombreHerramienta;
}

int archivo_vacio(char *nombre_archivo)
{
    FILE *archivo = fopen(nombre_archivo, "rb");
    if (archivo == NULL)
    {
        perror("No se pudo abrir el archivo");
        return 1; // Consideramos vacío si no se puede abrir
    }

    fseek(archivo, 0, SEEK_END);
    long size = ftell(archivo);
    fclose(archivo);

    return size == 0; // Retorna 1 si el archivo está vacío, 0 si no lo está
}

void crear_binario(char *nombre_binario)
{
    FILE *archivo = fopen(nombre_binario, "ab");
    if(archivo == NULL)
    {
        printf("No se pudo crear el archivo\n");
    }
    else
    {
        printf("Se creo el archivo correctamente\n");
    }
    fclose(archivo);
}


void cargar_usuario() {
    usuario nuevo_usuario;

    // Pedir datos al usuario
    printf("Ingrese su DNI: ");
    scanf("%d", &nuevo_usuario.dni);

    if(existe_dni(nuevo_usuario.dni,"usuarios.dat")==0){
        printf("Ingrese su tipo de usuario (1)Administrador, (2)Operario: ");
        scanf("%d", &nuevo_usuario.tipo);

        printf("Ingrese su nombre: ");
        scanf("%49s", nuevo_usuario.nombre); 
        if(nuevo_usuario.tipo==1){
            printf("Ingrese su password: ");
            scanf("%49s", nuevo_usuario.password);
        }else{
            //si es operario no tiene clave
            strcpy(nuevo_usuario.password,"");
        }

         
            // Abrir archivo en modo append (añadir al final)
        FILE *fp = fopen("usuarios.dat", "ab");
        if (fp == NULL) {
            printf("Error al abrir el archivo\n");
            return;
        }

        // Escribir estructura en el archivo
        fwrite(&nuevo_usuario, sizeof(usuario), 1, fp);

        // Cerrar archivo
        fclose(fp);

        mensaje_exito("Usuario cargado exitosamente");
        printf("\n");
            sleep(2);
            system("cls");
            print_sub_menu_usuarios();
        }else{
            mensaje_peligro("Dni ya registrado, vuelva a intentar.\n");
            system("pause");
            system("cls");
            print_sub_menu_usuarios();

        }


}

void eliminar_usuario() {
    usuario usuario_a_eliminar;
    FILE *fp = fopen("usuarios.dat","rb");
    FILE *temp = fopen("temp_users.dat","wb");
    int dni, coincidencia_pwd, tipo, encontrado = 0;
    coincidencia_pwd=0;

    if (fp == NULL || temp == NULL) {
        error_msj_apertura_archivo();
        return;
    }

    printf("Ingrese el DNI del usuario a eliminar: ");
    scanf("%d", &dni);

    if(existe_dni(dni,"usuarios.dat")==1) {
        printf("Ingrese el tipo de usuario a eliminar (1)Administrador, (2)Operario: ");
        scanf("%d", &tipo);

        //si es administrador, solicitamos su clave para eliminarlo
        if (tipo == 1) {
            char password[MAX_CHAR];
            printf("Ingrese su password: \n");
            scanf("%s", password);
            while(!feof(fp)){
                if(fread(&usuario_a_eliminar,sizeof(usuario_a_eliminar),1,fp)==1){
                    if(strcmp(usuario_a_eliminar.password,password)==0 && usuario_a_eliminar.dni==dni){
                            while(!feof(fp))
                            {
                                if(fread(&usuario_a_eliminar,sizeof(usuario),1,fp)==1){
                                    if(usuario_a_eliminar.dni!=dni)
                                    {
                                        fwrite(&usuario_a_eliminar,sizeof(usuario),1,temp);
                                    }
                                }
                            }
                            encontrado=1;
                            coincidencia_pwd=1;

                    }
                }
            }
            if(!coincidencia_pwd){
                mensaje_peligro("Password incorrecto\n");
            }
            
        } else {
                //leemos el archivo 'original'
                while(!feof(fp))
                {
                    if(fread(&usuario_a_eliminar,sizeof(usuario),1,fp)==1){
                        if(usuario_a_eliminar.dni!=dni)
                        {
                            fwrite(&usuario_a_eliminar,sizeof(usuario),1,temp);
                        }
                    }
                }
                encontrado=1;
        }
    } else {
        printf("Usuario no encontrado\n");
    }

    fclose(fp);
    fclose(temp);

    if (encontrado) {
        remove("usuarios.dat");
        rename("temp_users.dat", "usuarios.dat");
        mensaje_exito("Usuario eliminado con exito!");
        printf("\n");
    }
}

void print_sub_menu_usuarios(){
    int op,tipo_elegido;
    do{
        printf("\n 0) Volver \n");
        printf("\n 1) Agregar usuario\n");
        printf("\n 2) Eliminar usuario \n");
        printf("\n 3) Listar operarios \n");
        fflush(stdin);
        scanf("%d",&op);
        system("cls");
        if(op!=0){
            switch (op)
            {
            case 1:
                cargar_usuario();
                break;
            case 2:
                eliminar_usuario();
                break;
            case 3:
            printf("Seleccione el tipo de usuario a listar: ( 1)Administrador , 2) Operario )\n");
            fflush(stdin);
            scanf("%d",&tipo_elegido);
            imprimir_usuarios(tipo_elegido);
                break;

            default:
                break;
            }
        }
    }while(op!=0);
}


int login() {
    int dni, tipo;
    char nombre[MAX_CHAR], password[MAX_CHAR];

    printf("BIENVENIDO AL SISTEMA DE GESTION DE HERRAMIENTAS\n");
    mensaje_advertencia("Para continuar inicie sesion como administrador\n");

    printf("Ingrese su DNI: ");
    scanf("%d", &dni);
    tipo=1; //administrador

    printf("Ingrese su nombre: ");
    scanf("%49s", nombre); // Leave space for null terminator

    printf("Ingrese su password: ");
    scanf("%49s", password); // Leave space for null terminator

    // Abrir archivo de usuarios en modo lectura
    FILE *fp = fopen("usuarios.dat", "rb");
    if (fp == NULL) {
        error_msj_apertura_archivo();
        return 0;
    }

    usuario usuario_logueado;
    int encontrado = 0;

    // Leer archivo de usuarios y buscar coincidencia
    while (fread(&usuario_logueado, sizeof(usuario), 1, fp) == 1) {
        if (usuario_logueado.dni == dni && usuario_logueado.tipo == tipo  && strcmp(usuario_logueado.password, password) == 0) {
            encontrado = 1;
            break;
        }
    }

    fclose(fp);

    if (encontrado) {
        mensaje_exito("Login exitoso!\n");
        if (tipo == 1) {
            // Iniciar sesión como administrador
            printf("Bienvenido, %s!\n",nombre);
            mostrar_mensaje_intermitente("Redirigiendo a vista de admin..\n",1);
            system("pause");
            system("cls");
            // Mostrar menú de administrador
            printMenu();
            return 1;
        }
    } else {
        mensaje_advertencia("Credenciales incorrectas. Intente nuevamente.\n");
        sleep(2);
        login();
    }
}

void mostrar_mensaje_intermitente(const char *mensaje, int duracion) {
    int i;
    for (i = 0; i < duracion; i++) {
        printf("%s\r", mensaje);
        fflush(stdout);
        usleep(1000000); // Retraso de 0.1 segundos
    }
    printf("\n");
}

int buscar_operario(int dni){
    usuario operario;
    FILE *op = fopen("usuarios.dat","rb");
    if(op){
        while(!feof(op)){
        if(fread(&operario,sizeof(operario),1,op)==1){

                if(operario.dni==dni){
                    fclose(op);
                    return 1; //operario existe
                }


        }
    }
    return 0; //operario no existe
    }else{
        printf("ERROR: %s\n",strerror(errno));    }
}

void imprimir_usuarios(int tipo_usuario){
    usuario user;
    FILE *fp = fopen("usuarios.dat","rb");
    if(fp){
        if(tipo_usuario==1){
            mensaje_advertencia("ADMINISTADORES\n");
        }else{
            mensaje_advertencia("OPERARIOS\n");
        }
        mensaje_info("----------------");
        printf("\n");
        while(!feof(fp)){
            if(fread(&user, sizeof(user),1,fp)==1){
                if(user.tipo==tipo_usuario){
                    mensaje_exito("---------------");
                    printf("\n");
                    printf("DNI: %d\n",user.dni);
                    printf("NOMBRE: %s\n",user.nombre);
                    mensaje_exito("---------------");
                    printf("\n");
                }
            }
        }
        mensaje_info("----------------");
    }
    fclose(fp);
}





void temporizador(char *hora_inicio, char *hora_fin) {
    FILE *fp;
    time_t inicio, fin, ahora;
    struct tm *tm_inicio, *tm_fin, *tm_ahora;
    int segundos_inicio, segundos_fin, segundos_ahora;
    char hora_actual[6];

    // Verificar formato de hora_inicio y hora_fin
    if (strlen(hora_inicio)!= 5 || strlen(hora_fin)!= 5 ||
        hora_inicio[2]!= ':' || hora_fin[2]!= ':') {
        printf("Error: formato de hora incorrecto. Debe ser hh:mm\n");
        return;
    }

    // Convertir hora_inicio y hora_fin a segundos desde la medianoche
    tm_inicio = malloc(sizeof(struct tm));
    tm_fin = malloc(sizeof(struct tm));
    sscanf(hora_inicio, "%d:%d", &tm_inicio->tm_hour, &tm_inicio->tm_min);
    sscanf(hora_fin, "%d:%d", &tm_fin->tm_hour, &tm_fin->tm_min);
    tm_inicio->tm_sec = 0;
    tm_fin->tm_sec = 0;
    inicio = mktime(tm_inicio);
    fin = mktime(tm_fin);
    segundos_inicio = (int) difftime(inicio, 0);
    segundos_fin = (int) difftime(fin, 0);

    // Abrir archivo temporizador.dat en modo append
    fp = fopen(TEMPORIZADOR_DAT, "ab+");
    if (fp == NULL) {
        printf("Error: no se pudo abrir el archivo temporizador.dat\n");
        return;
    }

    // Leer último valor guardado en el archivo
    fseek(fp, 0, SEEK_END);
    if (ftell(fp) > 0) {
        fseek(fp, 0, SEEK_SET);
        fread(&segundos_ahora, sizeof(int), 1, fp);
    } else {
        segundos_ahora = segundos_inicio;
    }

    // Ejecutar temporizador
    while (segundos_ahora < segundos_fin) {
        ahora = time(NULL);
        tm_ahora = localtime(&ahora);
        strftime(hora_actual, 6, "%H:%M", tm_ahora);
        printf("\r%s", hora_actual);
        fflush(stdout);
        segundos_ahora++;
        fwrite(&segundos_ahora, sizeof(int), 1, fp);
        sleep(1);
    }

    // Cerrar archivo
    fclose(fp);
    free(tm_inicio);
    free(tm_fin);
}



