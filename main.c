#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>
#include <math.h>
#include "lib.h"
#define MAX_ITEMS 50
#define MAX_CHAR 20
#define MAX_STOCK 100

int main()
{
    const char hora_inicio_jornada[6],hora_fin_jornada[6];
        if(login()==1){
            configurar_jornada(&hora_inicio_jornada,&hora_fin_jornada);
            //startTimer(hora_inicio_jornada, hora_fin_jornada);
            printMenu();
        }
        
    

    
    





    // }

}
