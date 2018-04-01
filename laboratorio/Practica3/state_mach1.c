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
#include <signal.h>

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
int imp_saldo(void);
int mensaje_mov(void);
int mensaje_C(void);
int mensaje_desp(void);
int mensaje_prin(void);
int mul_100_I(void);
int mul_100_R(void);
int m_filt(void);
int m_todo(void);
int mensaje_mov(void);
int check_P(void);
int mensaje_prin(void);
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

// linked lists
node_t *create_new_node(user_t *data, node_t *next, node_t *prev) {
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

node_t *insert_data(user_t *data, llist_t *llist) {
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
    while (cursor != NULL && strcmp(account, cursor->payload->account) != 0)
        cursor = cursor->next;

    if (cursor != NULL)
        return cursor->payload;

    else
        return NULL;
}

void load_users() {
    long fl;
    user_t *actual;

    char name[100], account[20], nip[100];

    FILE *users_db = open_file("user_database.txt", "r");

    fseek(users_db, 0, SEEK_END);
    fl = ftell(users_db);
    fseek(users_db, 0, SEEK_SET);

    while (ftell(users_db) < fl) {
        actual = (user_t *) malloc(sizeof(user_t));

        fscanf(users_db, "%s\n", name);
        fscanf(users_db, "%s\n", account);
        fscanf(users_db, "%s\n", nip);
        fscanf(users_db, "%ld\n", &actual->balance);

        actual->name = strdup(name);
        actual->account = strdup(account);
        actual->nip = strdup(nip);

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

        case 'E':
            event.etype = 7;
            break;

        case 'F':
            event.etype = 9;
            strcpy(event.args, ptmp);

            break;

        case '1':
            event.etype = 11;
            strcpy(event.args, "500");

            break;

        case '2':
            event.etype = 12;
            strcpy(event.args, "1000");

            break;

        case '3':
            event.etype = 13;
            strcpy(event.args, "2000");

            break;

        case '4':
            event.etype = 14;
            strcpy(event.args, "3000");

            break;

        case '5':
            event.etype = 15;
            strcpy(event.args, "4000");

            break;

        case 'O':
            event.etype = 16;
            strcpy(event.args, ptmp);

            break;

        case 'D':
            event.etype = 18;
            strcpy(event.args, ptmp);

            break;

        case 'A':
            event.etype = 19;
            break;

        case 'P':
            event.etype = 21;
            strcpy(event.args, ptmp);

            break;

        
        default:
            event.etype =-1;
            break;
    }
}


/* FUNCIONES DE IMPLEMENTACION */
int mensaje_desp(void) {
    clear();
    printf("Gracias por haber usado Cajeros Cristobalianos S.A. de C.V.\n");
    cont();
}

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

FILE *open_transactions(char *name) {
    char tr_name[200];
    FILE *transactions_db;

    sprintf(tr_name, "%s_transactions.txt", name);
    return open_file(tr_name, "a+");
}

void save_transaction(char *name, char *mode, long ammount) {
    char *datetime;
    FILE *transactions_db = open_transactions(name);

    datetime = now_time();

    fprintf(transactions_db, "[%s] %s de $%ld mxn\n", datetime, mode, ammount);

    free(datetime);
    fclose(transactions_db);
}

void save_users() {
    FILE *users_db = open_file("user_database.txt", "w");
    node_t *cursor = users.head;

    while (cursor != NULL) {
        fprintf(users_db, "%s\n", cursor->payload->name);
        fprintf(users_db, "%s\n", cursor->payload->account);
        fprintf(users_db, "%s\n", cursor->payload->nip);
        fprintf(users_db, "%ld\n", cursor->payload->balance);

        cursor = cursor->next;
    }

    fclose(users_db);
}

void create_account(char *name, char *account, char *nip, long balance) {
    FILE *users_db = open_file("user_database.txt", "a+");

    fprintf(users_db, "%s\n", name);
    fprintf(users_db, "%s\n", account);
    fprintf(users_db, "%s\n", nip);
    fprintf(users_db, "%ld\n", balance);

    save_transaction(account, "Deposito", balance);

    fclose(users_db);
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

    clear();

    while (cursor != NULL && strcmp(event.args, cursor->payload->account) != 0)
        cursor = cursor->next;

    if (cursor != NULL) {
        printf("Ingresa el nip: ");
        fgets(nip, 99, stdin);
        stripln(nip);

        if (strcmp(cursor->payload->nip, nip) == 0) {
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
    clear();
    printf("Para depositar dinero tiene que teclear F seguido de dos puntos y\n");
    printf("la cantidad que desea depositar. Tiene que ser multiplo de 100\n");
    printf("Ejemplo:  F:200\n");

    printf("\n\n>");
}

int mensaje_R(void) {
    clear();
    printf("Opciones para retirar dinero:\n");
    printf("\t1: $500 \t4: $3000\n");
    printf("\t2: $1000\t5: $4000\n");
    printf("\t3: $2000\tO: Otra cantidad\n");
    printf("\nSi se desea ingresar otra cantidad, teclear O seguido de dos puntos\n");
    printf("y la cantidad que se desea sacar. Ejemplo O:200\n");

    printf("\n\n>");
}

int imp_saldo(void) {
    clear();
    printf("Tu saldo actual es: $%ld mxn\n", user->balance);
    cont();
}

int mensaje_mov(void) {
    clear();
    printf("Movimientos de la cuenta\n");
    printf("\tA  Imprime todos los movimientos de la cuenta\n");
    printf("\tD  Filtra los movimientos por deposito o retiro\n");
    printf("\nSi se desea filtrar se tiene que ingresar D seguido de dos puntos\n");
    printf("y la palabra deposito o retiro. Ejemplo D:retiro o D:deposito\n");

    printf("\n\n>");
}

int mensaje_C(void) {
    clear();

    printf("Cambio de nip\n");
    printf("Para poder realizar el cambio de nip es nesecario que ingrese P seguido\n");
    printf("de dos puntos y el nuevo nip que desea usar, posteriormente tendra\n");
    printf("que ingresarlo nuevamente\n");
    printf("Ejemplo: P:nuevo_nip\n");

    printf("\n\n>");
}

int mensaje_prin(void) {
    clear();
    printf("Opciones disponibles:\n");
    printf("\tI: Depositar dinero\n");
    printf("\tR: Retirar dinero\n");
    printf("\tS: Consultar saldo\n");
    printf("\tM: Consultar movimientos\n");
    printf("\tC: Cambiar NIP\n");
    printf("\tE: Retirar tarjeta\n");

    printf("\n\n>");
}

int mul_100_I(void) {
    long number;

    number = atol(event.args);

    if (number % 100 != 0)
        return 2;
    else
        return 3;
}

int mul_100_R(void) {
    long ammount = atol(event.args);

    if (ammount % 100 != 0 || user->balance - ammount < 0)
        return 4;
    else
        return 5;
}

int m_filt(void) {
    clear();

    char t_name[100], *line = NULL, mode = 'a';
    long length = 0, fe;

    sprintf(t_name, "%s_transactions.txt", user->account);
    FILE *transactions = open_file(t_name, "r");

    fseek(transactions, 0, SEEK_END);
    fe = ftell(transactions);
    fseek(transactions, 0, SEEK_SET);

    if (strcmp(event.args, "retiro") == 0)
        mode = 'R';
    else if (strcmp(event.args, "deposito") == 0)
        mode = 'D';

    while (ftell(transactions) < fe) {
        getline(&line, &length, transactions);

        if (line[27] == mode || mode == 'a')
            printf("%s", line);
    }

    fclose(transactions);

    cont();
}

int m_todo(void) {
    clear();

    char t_name[100], *line = NULL;
    long length = 0, fe;

    sprintf(t_name, "%s_transactions.txt", user->account);
    FILE *transactions = open_file(t_name, "r");

    fseek(transactions, 0, SEEK_END);
    fe = ftell(transactions);
    fseek(transactions, 0, SEEK_SET);

    while (ftell(transactions) < fe) {
        getline(&line, &length, transactions);
        printf("%s", line);
    }

    fclose(transactions);

    cont();
}

int check_P(void) {
    char repeat[100];

    clear();
    printf("Digite de nuevo el nuevo nip: \n");
    fgets(repeat, 99, stdin);
    stripln(repeat);

    if (strcmp(event.args, repeat) == 0)
        return 7;
    else
        return 6;
}

int error_nip(void) {
    printf("\n\tEl numero de tarjeta y/o el nip son incorrectos\n");
    cont();
}

int error_mul_100_I(void) {
    clear();
    printf("La cantidad ingresada no es multiplo de 100\n");
    cont();
}

int agr_I(void) {
    user->balance += atol(event.args);

    save_transaction(user->account, "Deposito", atol(event.args));
    save_users();

    clear();
    printf("Saldo actual: %ld\n", user->balance);
    cont();
    clear();
    printf("Gracias por haber usado Cajeros Cristobalianos S.A. de C.V.\n");
    cont();
}

int error_mul_100_R(void) {
    clear();

    if (atol(event.args) % 100 != 0)
        printf("El monto ingresado no es multiplo de 100\n");

    else
        printf("No cuentas con los fondos suficientes para retirar %ld\n", atol(event.args));

    cont();
}

int agr_R(void) {
    user->balance -= atol(event.args);

    save_transaction(user->account, "Retiro", atol(event.args));
    save_users();

    clear();
    printf("Saldo actual: %ld\n", user->balance);
    cont();
    clear();
    printf("Gracias por haber usado Cajeros Cristobalianos S.A. de C.V.\n");
    cont();
}

int error_C(void) {
    clear();
    printf("El nip ingresado no coincide con el anterior\n");
    cont();
}

int agr_C(void) {
    user->nip = strdup(event.args);
    save_users();

    clear();
    printf("El nip fue cambiado exitosamente\n");
    cont();
}

int nul(void) {
}
