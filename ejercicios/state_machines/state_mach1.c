/****************************************************************
 *                                                              *
 * Archivo: state_mach1.c                                       *
 * Descripcion: Codigo Fuente para implementar el programa      *
 *      de maquina de estados.                                  *
 *                                                              *
 ****************************************************************/

/*************** ARCHIVOS DE INCLUSION ***************/ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tables.h"


/*************** VARIABLES GLOBALES ***************/ 
EVENT event;
int state;
char buf[BUFFER];

/*************** PROTOTIPOS DE FUNCION ***************/ 
void initialise(void);
void getevent(void);

int funcion1(void);
int funcion2(void);
int funcion3(void);
int funcion4(void);
int nul(void);


/*************** FUNCION PRINCIPAL ***************/ 
int main(int argc, char **argv) {
    int actx, auxx, outcome;

    initialise();
    
    while (1) {
        getevent();

        for ((actx = state_table[state].start);(action_table[actx].event != event.etype) && (actx < state_table[state].end);actx++);

        if (action_table[actx].action != NULL)
            outcome = (*(action_table[actx].action))();

        if(action_table[actx].moreacts == -1)
            state = action_table[actx].nextstate;
        else {
            // 0 + outcome = outcome
            auxx = action_table[actx].moreacts + outcome;
            while (auxx != -1) {
                outcome = (*(aux_table[auxx].action))();
                if (aux_table[auxx].moreacts == -1 ) {
                    state = aux_table[auxx].nextstate;
                    auxx = -1;
                }
                else
                    auxx = aux_table[auxx].moreacts + outcome;
            }
        }
        
    }
}

void initialise(void) {
    state = 0;
}


void getevent(void) {
    char *ptmp;
    ptmp = &buf[2];
    
#ifdef DEBUG
    printf("wait event \n");
#endif

    fgets(buf, 2, stdin);
    switch (buf[0]) {
        case 'A':
            event.etype = ENTRADA_A;
            break;

        case 'B':
            event.etype = ENTRADA_B;
            break;

        case 'C':
            event.etype=ENTRADA_C;
            strcpy(event.args,ptmp);

                                       // C:info_adicional
            #ifdef DEBUG
            printf("---> %s \n",event.args);
            #endif
                                
            break;

        case 'a':
            event.etype = ENTRADA_a;
            break;

        case 'b':
            event.etype = ENTRADA_b;
            break;

        case 'c':
            event.etype = ENTRADA_c;
            break;

        default:
            event.etype = -1;
            break;
                    
    }
}
 

/* FUNCIONES DE IMPLEMENTACION */

int nul(void) {
}

int msg_A() {
    printf("En estado A\n");
}

int msg_B() {
    printf("En estado B\n");
}

int msg_C() {
    printf("En estado C\n");
}

int msg_sal_A() {
    printf("Saliendo del estado A\n");
}

int msg_sal_B() {
    printf("Saliendo del estado B\n");
}

int msg_sal_C() {
    printf("Saliendo del estado C\n");
}
