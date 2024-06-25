#ifndef LIB_H_INCLUDED
#define LIB_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#define MAX_CHAR 20
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

int buscarId(int id_buscado);
int longitud_de_entero(int entero);
int num_items_reg();
int generarNuevoIDPrestamo();
void configurar_jornada(const char *horaInicioJornada, const char *horaFinJornada);


void printMenu();
void cargarHerramientaArch();
void buscarHerramientaArch(int idBuscado);
void imprimirHerramienta(FILE * archivo);
void prestarHerramientaArch();
void resetArchivo(char *file_name);
void modificar_stock(int id);
void error_msj_apertura_archivo();
void mensaje_exito(const char* mensaje);
void mensaje_info(const char* mensaje);
void mensaje_advertencia(const char* mensaje);
void eliminar_herramienta(int id);
void registrarPrestamo(int herramientaID);
void obtenerFechaActual(char *fecha);
void obtenerHoraActual(char *hora);
void imprimirPrestamo(int id_prestamo,int herramientaID);
void crear_prestamos();
void historial_prestamos_jornada();
char* obtenerNombreHerramienta(int herramientaID);
int archivo_vacio(char *nombre_archivo);
void crear_binario(char *nombre_binario);
void cargar_usuario();
void print_sub_menu_usuarios();
int login();
int buscar_operario(int dni);

#endif // LIB_H_INCLUDED
