#ifndef LIB_H_INCLUDED
#define LIB_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>
#include <math.h>
#define MAX_ITEMS 50
#define MAX_CHAR 20
#define MAX_STOCK 100
#define NOM_ARCHIVO "herramientas.dat"
#define PRESTAMOS "prestamos.dat"
#define PRESTAMOS_IDS "prestamos_ids.dat"
#define TEMPORIZADOR_DAT "temporizador.dat"

typedef struct herramientas{
    int id,stock,estado;
    char nombre[MAX_CHAR];
}herramienta;

typedef struct usuarios{
    int dni,tipo;
    char nombre[MAX_CHAR];
    char password[MAX_CHAR];
}usuario;

typedef struct prestamos{
    int prestamoID;             // ID �nico del pr�stamo
    int herramientaID;          // ID de la herramienta prestada
    int dni_operario;          // Dni del operario al que se le asignó la herramienta
    char fechaGeneracion[11];   // Fecha en que se genera el pr�stamo (dd-mm-yyyy)
    char horaPrestamo[6];       // Hora del pr�stamo (hh:mm)
    char horaDevolucion[6];     // Hora de devoluci�n (hh:mm), vac�a si no se ha devuelto
    char horaInicioJornada[6];  // Hora de inicio de la jornada laboral (hh:mm)
    char horaFinJornada[6];     // Hora de fin de la jornada laboral (hh:mm)
    int cantidad; //cantidad entregada
}prestamo;

///Funcion menu, de donde ramifica todo
void printMenu();

///Opciones del menu
void cargarHerramientaArch(); // Opción 1 del programa, sube una herramienta al archivo.
void buscarHerramientaArch(int idBuscado); // Opción 2 del programa, busca una herramienta según idBuscado.
void listarHerramientasArch(); // Opción 3 del programa, lista todas las herramientas del archivo.
void resetArchivo(char *file_name); //Opción 4 del programa, función que resetea el archivo elegido.
void gestionar_jornada(); // Opción 5 del programa, función para gestionar horario e imprimir tickets de préstamo.
void print_sub_menu_usuarios(); // Opción 6 del programa, sub menú para gestionar usuarios.

//Funcion de login
int login(); // Login para administradores u operarios.

//Funciones auxiliares
void configurar_jornada(const char *horaInicioJornada, const char *horaFinJornada); // Función para configurar el horario de la jornada.
void error_msj_apertura_archivo(); // Función generalizada para el error en abrir archivos.
void crear_binario(char *nombre_binario); // Función generalizada para crear un archivo binario.
int longitud_de_entero(int entero); // Función auxiliar para saber la longitud de un número entero.
int num_items_reg(); // Función para saber el número de objetos que hay en el registro.
int existeId(int idInput, char *FILE_NAME); // Función que devuelve un valor booleano según si el id existe en la tabla herramientas.
int existe_dni(int idInput, char *FILE_NAME); // Función que devuelve un valor booleano según si el dni existe en la tabla usuarios
int existe_id_prestamo(int idInput, char *FILE_NAME); // Función que devuelve un valor booleano según si existe el id en la tabla prestamos.
void imprimirHerramienta(FILE * archivo); // Función que imprime una herramienta.
void modificar_stock(int id); // Función que modifica el stock de una herramienta segun el id.
void eliminar_herramienta(int id); // Función que elimina una herramienta según el id.
void registrarPrestamo(int herramientaID); // Función que registra un préstamo según el id.
int generarNuevoIDPrestamo(); // Función que genera un nuevo ID para el préstamo basados en los id anteriores.
void imprimirPrestamo(int id_prestamo,int herramientaID); // Función que imprime el ticket de préstamo.
void historial_prestamos_jornada(); // Función que imprime el historial de préstamos hechos en la jornada
char* obtenerNombreHerramienta(int herramientaID); // Función que obtiene el nombre de una herramienta según el id.
int archivo_vacio(char *nombre_archivo); // Función que verifica si el archivo está vacío.
void crear_binario(char *nombre_binario); // Función que crea un archivo binario.
void cargar_usuario(); // Función que sube un usuario a la base de datos.
void eliminar_usuario(); // Función que elimina un usuario de la base de datos.
int buscar_operario(int dni); // Función que busca a los operarios según su documento de identidad.
void imprimir_usuarios(int tipo_usuario); // Función que imprime usuarios según su tipo.
void devolver_prestamo_id(int id_prestamo) // Función que devuelve una herramienta anteriormente prestada según el id.

//Funciones de tiempo
void obtenerHoraActual(char *hora); // Función para obtener la hora actual
void obtenerFechaActual(char *fecha); // Función para obtener la fecha actual

//Funciones de UI
void mensaje_exito(const char* mensaje); // Función que "colorea" un mensaje en verde
void mensaje_info(const char* mensaje); // Función que "colorea" un mensaje en azul
void mensaje_advertencia(const char* mensaje); // Función que "colorea" un mensaje en amarillo
void mensaje_peligro(const char* mensaje); // Función que "colorea" un mensaje en rojo
void mostrar_mensaje_intermitente(const char *mensaje, int duracion); // Función que muestra un mensaje de manera intermitente

#endif // LIB_H_INCLUDED
