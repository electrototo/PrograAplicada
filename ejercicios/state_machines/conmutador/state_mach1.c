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
int nul(void);

int msg_dial(void);
int msg_config(void);
int bloqueado(void);
int msg_bloq(void);
int msg_ubloq(void);
int existe_a(void);
int existe_b(void);
int msg_num_bloq(void);
int ocupado(void);
int msg_busy(void);
int contesta(void);
int msg_save(void);
int msg_exist(void);
int msg_exist(void);
int desbloqueo(void);
int msg_no_answer(void);
int info(void);



/*************** FUNCION PRINCIPAL ***************/
int main(int argc, char **argv)
{
    int actx, auxx, outcome;

    initialise();

    while (1) {    /* loop infinito para la MFE */
        getevent();

        for ((actx = state_table[state].start);(action_table[actx].event != event.etype) && (actx < state_table[state].end);actx++);

        outcome = (*(action_table[actx].action))();
            if(action_table[actx].moreacts == -1)
                state = action_table[actx].nextstate;
            else {
                auxx = action_table[actx].moreacts + outcome;
                while (auxx != -1){
                    outcome = (*(aux_table[auxx].action))();
                    if (aux_table[auxx].moreacts == -1 ){
                        state = aux_table[auxx].nextstate;
                        auxx = -1;
                    }
                    else
                        auxx = aux_table[auxx].moreacts + outcome;

                }
        }

    }
}

FILE *open_file(char *name, char *attr) {
    FILE *fp;

    fp = fopen(name, attr);

    if (fp == NULL)
        fp = fopen(name, "wt");

    return fp;
}

void initialise(void) {
    FILE *fp;
    char buffer[24];

    state = 0;
    fp = open_file("numbers.db", "rt");

    while (!feof(fp) && acnums < MAX_NUMS) {
        fscanf(fp, "%s\n", buffer);
        numbers[acnums++] = strdup(buffer);
    }

    fclose(fp);
}

void getevent(void) {
    char *ptmp;
    ptmp = &buf[2];

    fgets(buf, BUFFER + 1, stdin);
    switch (buf[0]) {
        case 'M':
            event.etype = 0;
            break;

        case 'C':
            event.etype = 1;
            break;

        case 'H':
            event.etype = 3;
            break;

        case 'B':
            event.etype = 5;
            break;

        case 'D':
            event.etype = 6;
            break;

        case 'R':
            event.etype = 7;
            break;

        case 'P':
            event.etype = 9;
            break;

        case 'U':
            event.etype = 11;
            break;

        default:
            event.etype =-1;
            break;
    }
}


/* FUNCIONES DE IMPLEMENTACION */
int msg_dial(void) {
}

int msg_config(void) {
}

int bloqueado(void) {
}

int msg_bloq(void) {
}

int msg_ubloq(void) {
}

int existe_a(void) {
}

int existe_b(void) {
}

int msg_num_bloq(void) {
}

int ocupado(void) {
}

int msg_busy(void) {
}

int contesta(void) {
}

int msg_save(void) {
}

int msg_exist(void) {
}

int desbloqueo(void) {
}

int msg_no_answer(void) {
}

int info(void) {
}

int nul(void) {
}
