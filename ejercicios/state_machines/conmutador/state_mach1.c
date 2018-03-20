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
#include <time.h>
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
int main(int argc, char **argv) {
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

node_t *create_node(char *data, node_t *next, node_t *prev) {
    node_t *new_node = (node_t *) malloc(sizeof(node_t));

    if (new_node == NULL)
        exit(0);

    new_node->number = strdup(data);
    new_node->next = next;
    new_node->prev = prev;

    return new_node;
}

node_t *insert_data(char *data, llist_t *llist) {
    node_t *new_node = create_node(data, llist->head, NULL);

    if (llist->tail == NULL)
        llist->tail = new_node;

    if (llist->head != NULL)
        llist->head->prev = new_node;

    llist->head = new_node;

    return new_node;
}

void find_delete(char *number, llist_t *llist) {
    node_t *cursor = llist->head;

    while (cursor != NULL && strcmp(cursor->number, number) != 0)
        cursor = cursor->next;

    if (cursor != NULL) {
        if (cursor->prev != NULL)
            cursor->prev->next = cursor->next;
        else
            llist->head = cursor->next;

        if (cursor->next != NULL)
            cursor->next->prev = cursor->prev;
        else
            llist->tail = cursor->prev;

        free(cursor->number);
        free(cursor);
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

    long size, current = 0;

    state = 0;
    fp = open_file("numbers.db", "rt");

    llist.head = NULL;
    llist.tail = NULL;

    fseek(fp, 0, SEEK_END);
    size = ftell(fp);

    while (current != size && acnums < MAX_NUMS) {
        fscanf(fp, "%s\n", buffer);
        insert_data(buffer, &llist);

        current = ftell(fp);
    }

    fclose(fp);

    srand(time(NULL));
}

void save_numbers() {
    FILE *fp;
    node_t *cursor = llist.head;

    fp = open_file("numbers.db", "wt");

    while (cursor != NULL) {
        fprintf(fp, "%s\n", cursor->number);
        cursor = cursor->next;
    }

    fclose(fp);
}

int search_number(char *number, llist_t *llist) {
    int found = 0;
    node_t *cursor = llist->head;

    while (cursor != NULL && !found) {
        if (strcmp(number, cursor->number) == 0)
            found = 1;

        cursor = cursor->next;
    }

    return found;
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
            strcpy(event.args, ptmp);
            strtok(event.args, "\n");

            break;

        case 'U':
            event.etype = 11;
            strcpy(event.args, ptmp);
            strtok(event.args, "\n");

            break;

        default:
            event.etype = -1;
            break;
    }
}


/* FUNCIONES DE IMPLEMENTACION */
int msg_dial(void) {
    printf("Presiona H seguido de dos puntos y el numero a marcar\n");
}

int msg_config(void) {
    printf("Opciones:\n");
    printf("\tB: bloquear numero\n");
    printf("\tD: desbloquear numero\n");
}

int bloqueado(void) {
    int found = search_number(event.args, &llist);

    if (found)
        return 0;
    else
        return 1;
}

int msg_bloq(void) {
    printf("Presione P seguido de dos puntos y el numero a bloquear\n");
}

int msg_ubloq(void) {
    printf("Presione U seguido de dos puntos y el numero a desbloquear\n");
}

int existe_a(void) {
    int found = search_number(event.args, &llist);

    printf("Se ingreso: %s\n", event.args);

    if (found)
        return 5;
    else
        return 4;
}

int existe_b(void) {
    int found = search_number(event.args, &llist);

    printf("Se ingreso: %s\n", event.args);

    if (found)
        return 7;
    else
        return 6;
}

int msg_num_bloq(void) {
    printf("El numero ingresado se encuentra bloqueado\n");
}

int ocupado(void) {
    int status = rand() % 2;

    if (status)
        return 2;
    else
        return 3;
}

int msg_busy(void) {
    printf("pip pip pip... el numero se encuentra ocupado piiiiiip\n");
}

int contesta(void) {
    int status = rand() % 2;

    if (status)
        return 8;
    else
        return 9;
}

int msg_save(void) {
    insert_data(event.args, &llist);
    printf("Se guardo exitosamente el numero %s\n", event.args);
    save_numbers();
}

int msg_exist(void) {
    printf("No accion tomada\n");
}

int desbloqueo(void) {
    printf("El numero se desbloqueo con exito\n");

    find_delete(event.args, &llist);
    save_numbers();
}

int msg_no_answer(void) {
    printf("pip pip pip.. el numero no conesta piiiiip\n");
}

int info(void) {
    printf("el numero contesto\n");
}

int nul(void) {
}
