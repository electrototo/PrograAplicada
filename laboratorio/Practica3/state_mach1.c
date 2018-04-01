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
#include <signal.h>
#include <time.h>

#include "tables.h"

#define clear() system("clear")

/*************** VARIABLES GLOBALES ***************/
EVENT event;
int state;
char buf[BUFFER];

/*************** PROTOTIPOS DE FUNCION ***************/
void initialise(void);
void getevent(void);
int nul(void);

int c_nip(void);
int mensaje_init(void);
int mensaje_I(void);
int mensaje_R(void);
int Imp_saldo(void);
int mensaje_mov(void);
int mensaje_C(void);
int mensaje_prin(void);
int mul_100_I(void);
int mul_100_R(void);
int m_filt(void);
int m_todo(void);
int check_P(void);
int error_nip(void);
int error_mul_100_I(void);
int agr_I(void);
int error_mul_100_R(void);
int agr_R(void);
int error_C(void);
int agr_C(void);

void cont();
void mensaje_trabajo();

void config();
void quit(int);

void stripln(char *);

char *now_time();

FILE *open_file(char *name, char *mode);

/*************** FUNCION PRINCIPAL ***************/
int main(int argc, char **argv) {
    int actx, auxx, outcome;

    if (argc == 2 && strcmp("-c", argv[1]) == 0) {
        config();

        return 0;
    }
    else if (argc >= 2) {
        printf("%s\n\n", argv[0]);
        printf("Opciones disponibles:\n");
        printf("\t-c  Entra al modo de configuracion de cuentas\n");
        printf("\t-h  Imprime este mensaje de ayuda\n");

        return 0;
    }

    initialise();
    signal(SIGINT, quit);

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
                if (aux_table[auxx].moreacts == -1){
                    state = aux_table[auxx].nextstate;
                    auxx = -1;
                }
                else
                    auxx = aux_table[auxx].moreacts + outcome;

            }
        }
    }
}

// linked lists
node_t *create_new_node(user_t data, node_t *next, node_t *prev) {
    node_t *new_node = (node_t *) malloc(sizeof(node_t));

    if (new_node == NULL) {
        printf("malloc error\n");

        exit(0);
    }

    new_node->next = next;
    new_node->prev = prev;
    new_node->payload = data;

    return new_node;
}

node_t *insert_data(user_t data, llist_t *llist) {
    node_t *new_node = create_new_node(data, llist->head, NULL);

    if (llist->tail == NULL)
        llist->tail = new_node;

    if (llist->head != NULL)
        llist->head->prev = new_node;

    llist->head = new_node;

    return new_node;
}

user_t *find_user(char *account, llist_t *llist) {
    node_t *cursor;

    cursor = llist->head;
    while (cursor != NULL && strcmp(account, cursor->payload.account) != 0)
        cursor = cursor->next;

    if (cursor != NULL)
        return &cursor->payload;

    else
        return NULL;
}

void load_users() {
    long fl;
    user_t actual;

    char name[100], account[20], nip[100];

    FILE *users_db = open_file("user_database.txt", "r");

    fseek(users_db, 0, SEEK_END);
    fl = ftell(users_db);
    fseek(users_db, 0, SEEK_SET);

    while (ftell(users_db) < fl) {
        fscanf(users_db, "%s\n", name);
        fscanf(users_db, "%s\n", account);
        fscanf(users_db, "%s\n", nip);
        fscanf(users_db, "%ld\n", &actual.balance);

        actual.name = strdup(name);
        actual.account = strdup(account);
        actual.nip = strdup(nip);

        insert_data(actual, &users);

        printf("User: %s loaded\n", name);
    }

    fclose(users_db);
}

void initialise(void) {
    state = 0;

    users.head = NULL;
    users.tail = NULL;

    mensaje_trabajo();
    mensaje_init();

    load_users();
}

void getevent(void) {
    char *ptmp;
    ptmp = &buf[2];

    fgets(buf, BUFFER + 1, stdin);
    stripln(buf);

    switch (buf[0]) {
        case 'T':
            event.etype = 0;
            strcpy(event.args, ptmp);

            break;

        case 'I':
            event.etype = 2;
            break;

        case 'R':
            event.etype = 3;
            break;

        case 'S':
            event.etype = 4;
            break;

        case 'M':
            event.etype = 5;
            break;

        case 'C':
            event.etype = 6;
            break;

        case 'F':
            event.etype = 8;
            break;

        case '1':
            event.etype = 10;
            break;

        case '2':
            event.etype = 11;
            break;

        case '3':
            event.etype = 12;
            break;

        case '4':
            event.etype = 13;
            break;

        case '5':
            event.etype = 14;
            break;

        case 'O':
            event.etype = 15;
            break;

        case 'D':
            event.etype = 17;
            break;

        case 'A':
            event.etype = 18;
            break;

        case 'P':
            event.etype = 20;
            break;

        
        default:
            event.etype =-1;
            break;
    }
}

/* FUNCIONES DE IMPLEMENTACION */
void quit(int dummy) {
    exit(0);
}

void stripln(char *str) {
    int offset = strlen(str);
    str[offset - 1] = 0;
}

char *now_time() {
    time_t now;
    struct tm *info;

    char *buffer = (char *) malloc(sizeof(char) * 100);

    time(&now);
    info = localtime(&now);

    strftime(buffer, 99, "%c", info);

    return buffer;
}

FILE *open_file(char *name, char *mode) {
    FILE *fp;

    fp = fopen(name, mode);

    if (fp == NULL) {
        printf("Error al abrir el archivo %s\n", name);
        quit(0);
    }

    return fp;
}

void create_account(char *name, char *account, char *nip, long balance) {
    char tr_name[200], *datetime;

    sprintf(tr_name, "%s_transactions.txt", name);

    FILE *users_db = open_file("user_database.txt", "a+");
    FILE *transactions_db = open_file(tr_name, "w");

    fprintf(users_db, "%s\n", name);
    fprintf(users_db, "%s\n", account);
    fprintf(users_db, "%s\n", nip);
    fprintf(users_db, "%ld\n", balance);

    datetime = now_time();
    fprintf(transactions_db, "[%s] Ingreso de $%ld mxn\n", datetime, balance);
    free(datetime);

    fclose(users_db);
    fclose(transactions_db);
}

void config() {
    char name[100], account[20], nip[100];
    long balance = -1;

    mensaje_trabajo();
    clear();

    printf("Nombre del cuentahbitante:  ");
    fgets(name, 99, stdin);
    stripln(name);

    printf("Numero de cuenta:           ");
    fgets(account, 19, stdin);
    stripln(account);

    while (balance < 0) {
    printf("Saldo actual (>= 0):        ");
        scanf("%ld", &balance);
        getchar();
    }

    printf("Nip:                        ");
    fgets(nip, 99, stdin);
    stripln(nip);

    create_account(name, account, nip, balance);
}

void cont() {
    printf("\n\nPresione enter para continuar...");
    getchar();
}

void mensaje_trabajo() {
    clear();

    printf("Disenado y programado por Cristobal Liendo Infante\n\n");
    printf("Este programa busca simular el funcionamiento de un cajero autoatico\n");
    printf("a traves de maquinas de estado finitos, con la opcion -c para poder\n");
    printf("registrar a los cuentahabitantes\n");

    cont();
}

int c_nip(void) {
    node_t *cursor = users.head;
    char nip[100];

    while (cursor != NULL && strcmp(event.args, cursor->payload.account) != 0)
        cursor = cursor->next;

    if (cursor != NULL) {
        printf("Ingresa el nip: ");
        fgets(nip, 99, stdin);
        stripln(nip);

        if (strcmp(cursor->payload.nip, nip) == 0) {
            user = cursor->payload;

            return 0;
        }
    }

    return 1;
}

int mensaje_init(void) {
    clear();

    printf("Cajeros Cristobalianos S.A. de C.V.\n\n");
    printf("Para usar el cajero es necesario seguir el siguiente paso:\n");
    printf("Ingrese la tarjeta al cajero ingresando T seguido de dos puntos\n");
    printf("y el numero de su tarjeta. Ejemplo: T:1234567898765432\n\n>");
}

int mensaje_I(void) {
    printf("function mensaje_I\n");
}

int mensaje_R(void) {
    printf("function mensaje_R\n");
}

int Imp_saldo(void) {
    printf("function Imp_saldo\n");
}

int mensaje_mov(void) {
    printf("function mensaje_mov\n");
}

int mensaje_C(void) {
    printf("function mensaje_C\n");
}

int mensaje_prin(void) {
    clear();
    printf("function mensaje_prin\n");
}

int mul_100_I(void) {
    printf("function mul_100_I\n");
}

int mul_100_R(void) {
    printf("function mul_100_R\n");
}

int m_filt(void) {
    printf("function m_filt\n");
}

int m_todo(void) {
    printf("function m_todo\n");
}

int check_P(void) {
    printf("function check_P\n");
}

int error_nip(void) {
    printf("function error_nip\n");
    printf("\n\tEl numero de tarjeta y/o el nip son incorrectos\n");
}

int error_mul_100_I(void) {
    printf("function error_mul_100_I\n");
}

int agr_I(void) {
    printf("function agr_I\n");
}

int error_mul_100_R(void) {
    printf("function error_mul_100_R\n");
}

int agr_R(void) {
    printf("function agr_R\n");
}

int error_C(void) {
    printf("function error_C\n");
}

int agr_C(void) {
    printf("function agr_C\n");
}

int nul(void) {
}
