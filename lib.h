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
void cargarHerramientaArch();
void buscarHerramientaArch(int idBuscado);
void listarHerramientasArch();
void resetArchivo(char *file_name);
void gestionar_jornada();
void print_sub_menu_usuarios();

//Funcion de login
int login();

//Funciones auxiliares
void configurar_jornada(const char *horaInicioJornada, const char *horaFinJornada);
void error_msj_apertura_archivo();
void crear_binario(char *nombre_binario);
int longitud_de_entero(int entero);
int num_items_reg();
int existeId(int idInput, char *FILE_NAME);
int existe_dni(int idInput, char *FILE_NAME);
int existe_id_prestamo(int idInput, char *FILE_NAME);
void imprimirHerramienta(FILE * archivo);
void modificar_stock(int id);
void eliminar_herramienta(int id);
void registrarPrestamo(int herramientaID);
int generarNuevoIDPrestamo();
void imprimirPrestamo(int id_prestamo,int herramientaID);
void historial_prestamos_jornada();
char* obtenerNombreHerramienta(int herramientaID);
int archivo_vacio(char *nombre_archivo);
void crear_binario(char *nombre_binario);
void cargar_usuario();
void eliminar_usuario();
int buscar_operario(int dni);
void imprimir_usuarios(int tipo_usuario);
void devolver_prestamo_id(int id_prestamo)
void gestionar_jornada()

//Funciones de tiempo
void obtenerHoraActual(char *hora);
void obtenerFechaActual(char *fecha);

//Funciones de UI
void mensaje_exito(const char* mensaje);
void mensaje_info(const char* mensaje);
void mensaje_advertencia(const char* mensaje);
void mensaje_peligro(const char* mensaje);
void mostrar_mensaje_intermitente(const char *mensaje, int duracion);

#endif // LIB_H_INCLUDED
