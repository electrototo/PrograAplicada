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
#include <time.h>

#include "tables.h"

// macro para no escribir tanto
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

// ---------- Funciones para listas dinamicas ---------- // 
// funcion auxiliar para crear un nuevo nodo dentro de la lista dinamica
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

// funcion auxiliar para insertar en la lista dinamica
node_t *insert_data(user_t *data, llist_t *llist) {
    node_t *new_node = create_new_node(data, llist->head, NULL);

    if (llist->tail == NULL)
        llist->tail = new_node;

    if (llist->head != NULL)
        llist->head->prev = new_node;

    llist->head = new_node;

    return new_node;
}

// funcion auxiliar que srive para encontrar un usuario
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
// ------- Termina funciones para listas dinamicas ------ // 

// se encarga de cargar los usuarios en memoria a partir de la "base de datos"
// que se encuentra en user_database.txt
void load_users() {
    long fl;
    user_t *actual;

    char name[100], account[20], nip[100];

    FILE *users_db = open_file("user_database.txt", "r");

    fseek(users_db, 0, SEEK_END);
    fl = ftell(users_db);
    fseek(users_db, 0, SEEK_SET);

    while (ftell(users_db) < fl) {
        // pide espacio de memoria para cada usuario que se encuentre en la
        // base de datos
        actual = (user_t *) malloc(sizeof(user_t));

        fscanf(users_db, "%s\n", name);
        fscanf(users_db, "%s\n", account);
        fscanf(users_db, "%s\n", nip);
        fscanf(users_db, "%ld\n", &actual->balance);
        fscanf(users_db, "%d\n", &actual->active);

        actual->name = strdup(name);
        actual->account = strdup(account);
        actual->nip = strdup(nip);

        // inserta a los usuarios en la lista dinamica
        insert_data(actual, &users);
    }

    fclose(users_db);
}

// se ejecutan todas las funciones de inicializacion
void initialise(void) {
    // semilla "aleatoria" para generar la cuenta de los usuarios nuevos
    srand(time(NULL));

    state = 0;

    // inicializa la lista dinamica
    users.head = NULL;
    users.tail = NULL;

    // imprime mensajes necesarios
    mensaje_trabajo();
    mensaje_init();

    // carga en memoria a los usuarios
    load_users();
}

// lee las senales para la maquina de estados
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
// imprime un agradable mensaje de despidad al usuario
int mensaje_desp(void) {
    clear();
    printf("Gracias por haber usado Cajeros Cristobalianos S.A. de C.V.\n");
    cont();
}

// se ejecuta siempre cuando el usuario teclee control-c
// para liberar la memoria ocupada
void quit(int dummy) {
    node_t *cursor = users.head;
    node_t *tmp;

    while (cursor != NULL) {
        tmp = cursor;

        free(cursor->payload->account);
        free(cursor->payload->nip);
        free(cursor->payload->name);

        cursor = cursor->next;
        free(tmp);
    }

    // no hay que olvidar esta funcion, si no el control-c
    // no tendra efecto alguno
    exit(0);
}

// quitas las nuevas lineas de una cadena de texto
void stripln(char *str) {
    char *s = str;

    while (*s != 0 && *s != '\n')
        s++;

    if (*s != 0)
        *s = 0;
}

// obtiene el tiempo de ahorita en formato de string
char *now_time() {
    time_t now;
    struct tm *info;

    char *buffer = (char *) malloc(sizeof(char) * 100);

    time(&now);
    info = localtime(&now);

    strftime(buffer, 99, "%c", info);

    return buffer;
}

// funcion auxiliar que abre los archivos y verifica que estos existan
FILE *open_file(char *name, char *mode) {
    FILE *fp;

    fp = fopen(name, mode);

    if (fp == NULL) {
        printf("Error al abrir el archivo %s\n", name);
        quit(0);
    }

    return fp;
}

// abre el archivo de transacciones para un usuario determinado
FILE *open_transactions(char *name) {
    char tr_name[200];
    FILE *transactions_db;

    sprintf(tr_name, "%s_transactions.txt", name);
    return open_file(tr_name, "a+");
}

// guarda con timestamp la transaccion realizada, en el archivo que
// le corresponde al usuario
void save_transaction(char *name, char *mode, long ammount) {
    char *datetime;
    FILE *transactions_db = open_transactions(name);

    datetime = now_time();

    fprintf(transactions_db, "[%s] %s de $%ld mxn\n", datetime, mode, ammount);

    free(datetime);
    fclose(transactions_db);
}

// guarda en la "base de datos" los usuarios que se encuentren cargados en memoria
void save_users() {
    FILE *users_db = open_file("user_database.txt", "w");
    node_t *cursor = users.head;

    while (cursor != NULL) {
        fprintf(users_db, "%s\n", cursor->payload->name);
        fprintf(users_db, "%s\n", cursor->payload->account);
        fprintf(users_db, "%s\n", cursor->payload->nip);
        fprintf(users_db, "%ld\n", cursor->payload->balance);
        fprintf(users_db, "%d\n", cursor->payload->active);

        cursor = cursor->next;
    }

    fclose(users_db);
}

// guarda en el archivo un nuevo usuario
// por default todos los usuarios van a estar a activos
void create_account(char *name, char *account, char *nip, long balance) {
    FILE *users_db = open_file("user_database.txt", "a+");

    fprintf(users_db, "%s\n", name);
    fprintf(users_db, "%s\n", account);
    fprintf(users_db, "%s\n", nip);
    fprintf(users_db, "%ld\n", balance);
    fprintf(users_db, "%d\n", 1);

    save_transaction(account, "Deposito", balance);

    fclose(users_db);
}

// idealmente esta funcion solo va a ser ejecutada por el administrador del
// sistema con el parametro -c al inciar el programa
void config() {
    char name[100], account[20], nip[100];
    long balance = -1;

    int i, option;

    mensaje_trabajo();
    clear();

    printf("Menu de configuracion:\n");
    printf("\t[1] Regstistrar un nuevo usuario\n");
    printf("\t[2] Dar de baja una cuenta\n");
    printf("\t[3] Reactivar una cuenta\n");
    printf("\t[4] Salir\n");

    do {
        printf("> ");
        scanf("%d", &option);
        getchar();
    } while (option < 1 || option > 4);

    // opcion de registrar a un nuevo usuario
    if (option == 1) {
        printf("Nombre del cuentahbitante:  ");
        fgets(name, 99, stdin);
        stripln(name);

        while (balance < 0) {
        printf("Saldo actual (>= 0):        ");
            scanf("%ld", &balance);
            getchar();
        }

        for (i = 0; i < 16; i++)
            account[i] = (char) (random() % 10 + '0');

        account[i] = 0;

        printf("Nip:                        ");
        fgets(nip, 99, stdin);
        stripln(nip);

        printf("\n\nEl numero de cuenta para el cuentahabitante %s es el siguiente:\n", name);
        printf("Numero de cuenta:           %s\n", account);

        create_account(name, account, nip, balance);
    }
    // opcion para dar de baja una cuenta o reactivarla
    // se encuentran en el mismo if porque son muy similares
    // a excepcion del activado o desactivado
    else if (option == 2 || option == 3) {
        load_users();
        clear();

        do {
            printf("Digite el numero de cuenta: ");
            fgets(account, 19, stdin);
            stripln(account);

            user = find_user(account, &users);

            if (user == NULL)
                printf("\n\tUsuario no encontrado\n");

        } while (user == NULL);

        if (option == 2) {
            user->active = 0;
            printf("\nEl usuario %s con numero de cuenta %s fue dado de baja\n", user->name, user->account);
        }
        else {
            user->active = 1;
            printf("\nEl usuario %s con numero de cuenta %s fue reactivado\n", user->name, user->account);
        }

        // hubieron cambios, asi que guardalos
        save_users();
    }
}

// mensaje amigable para continuar despues de una accion
void cont() {
    printf("\n\nPresione enter para continuar...");
    getchar();
}

// mensaje como requisito de la practica
void mensaje_trabajo() {
    clear();

    printf("Disenado y programado por Cristobal Liendo Infante\n\n");
    cont();
    clear();
    printf("Este programa busca simular el funcionamiento de un cajero autoatico\n");
    printf("a traves de maquinas de estado finitos, con la opcion -c para poder\n");
    printf("registrar a los cuentahabitantes\n");

    cont();
}

// checa si la cuenta esta activa y si esta existe
int c_nip(void) {
    node_t *cursor = users.head;
    char nip[100];

    clear();

    while (cursor != NULL && strcmp(event.args, cursor->payload->account) != 0)
        cursor = cursor->next;

    if (cursor != NULL && cursor->payload->active) {
        printf("Ingresa el nip: ");
        fgets(nip, 99, stdin);
        stripln(nip);

        // si el nip ingresado es la adecuada para la cuenta, entonces
        // guarda la "sesion" en user y regresa el estado correspondiente
        if (strcmp(cursor->payload->nip, nip) == 0) {
            user = cursor->payload;

            return 0;
        }
    }

    // si no, esta activa o el nip es el incorrecto, marca error 
    user = cursor->payload;

    return 1;
}

// mensaje agradable e informativo a la vista del usuario para saber el funcionamiento
// de la maquina
int mensaje_init(void) {
    clear();

    printf("Cajeros Cristobalianos S.A. de C.V.\n\n");
    printf("Para usar el cajero es necesario seguir el siguiente paso:\n");
    printf("Ingrese la tarjeta al cajero ingresando T seguido de dos puntos\n");
    printf("y el numero de su tarjeta. Ejemplo: T:1234567898765432\n\n>");
}

// mensaje de instrucciones para depositar dinero
int mensaje_I(void) {
    clear();
    printf("Para depositar dinero tiene que teclear F seguido de dos puntos y\n");
    printf("la cantidad que desea depositar. Tiene que ser multiplo de 100\n");
    printf("Ejemplo:  F:200\n");

    printf("\n\n>");
}

// mensaje de instrucciones para retirar dinero
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

// mensaje que contiene el saldo del usuario
int imp_saldo(void) {
    clear();
    printf("Tu saldo actual es: $%ld mxn\n", user->balance);
    cont();
}

// mensaje de instrucciones para listar los movimientos
// dentro de la cuenta del usuario
int mensaje_mov(void) {
    clear();
    printf("Movimientos de la cuenta\n");
    printf("\tA  Imprime todos los movimientos de la cuenta\n");
    printf("\tD  Filtra los movimientos por deposito o retiro\n");
    printf("\nSi se desea filtrar se tiene que ingresar D seguido de dos puntos\n");
    printf("y la palabra deposito o retiro. Ejemplo D:retiro o D:deposito\n");

    printf("\n\n>");
}

// mensaje de instrucciones para el cambio de nip
int mensaje_C(void) {
    clear();

    printf("Cambio de nip\n");
    printf("Para poder realizar el cambio de nip es nesecario que ingrese P seguido\n");
    printf("de dos puntos y el nuevo nip que desea usar, posteriormente tendra\n");
    printf("que ingresarlo nuevamente\n");
    printf("Ejemplo: P:nuevo_nip\n");

    printf("\n\n>");
}

// mensaje de instrucciones para el uso del cajero
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

// verifica que la cantidad que se desea depositar
// sea multiplo de 100
int mul_100_I(void) {
    long number;

    number = atol(event.args);

    if (number % 100 != 0)
        return 2;
    else
        return 3;
}

// verifica que la cantidad que se desea retrirar
// sea multiplo de 100
int mul_100_R(void) {
    long ammount = atol(event.args);

    if (ammount % 100 != 0 || user->balance - ammount < 0)
        return 4;
    else
        return 5;
}

// funcion que se encarga de imprimir de forma filtrada
// todos los movimientos realizados por el usuario
int m_filt(void) {
    clear();

    char t_name[100], *line = NULL, mode = 'a';
    long length = 0, fe;

    // genera el nombre del archivo de transacciones y lo abre
    sprintf(t_name, "%s_transactions.txt", user->account);
    FILE *transactions = open_file(t_name, "r");

    fseek(transactions, 0, SEEK_END);
    fe = ftell(transactions);
    fseek(transactions, 0, SEEK_SET);

    // obtiene la modalidad de filtro que desea el usuario
    if (strcmp(event.args, "retiro") == 0)
        mode = 'R';
    else if (strcmp(event.args, "deposito") == 0)
        mode = 'D';

    while (ftell(transactions) < fe) {
        getline(&line, &length, transactions);

        // filtra todas las lineas de texto que cumpla con el filtro
        // impuesto por el usuario
        if (line[27] == mode || mode == 'a')
            printf("%s", line);
    }

    fclose(transactions);

    cont();
}

// muestra todas las transacciones realizadas por el usuario
int m_todo(void) {
    clear();

    char t_name[100], *line = NULL;
    long length = 0, fe;

    // genera el nombre del archivo de transacciones y lo abre
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

// funcion que se encarga de verificar que el nip ingresado por el usuario
// sea el nip asociado a la cuenta bancaria
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

// si el nip no coincide con la cuenta bancaria, imprime un error informativo
int error_nip(void) {
    if (user == NULL)
        printf("\n\tEl numero de tarjeta y/o el nip son incorrectos\n");
    else
        printf("\n\tTu cuenta ha sido desactivada\n");

    cont();
}

// imprime un error si la cantidad depositada no es multiplo de 100
int error_mul_100_I(void) {
    clear();
    printf("La cantidad ingresada no es multiplo de 100\n");
    cont();
}

// funcion que se encarga de depositar la cantidad ingresada por el usuario
// a su cuenta
int agr_I(void) {
    user->balance += atol(event.args);

    // genera un registro en los movimientos del usuario
    save_transaction(user->account, "Deposito", atol(event.args));
    
    // simulando las funciones del framework django para facilitar el codigo
    // guarda los cambios en la "base de datos"
    save_users();

    clear();
    printf("Saldo actual: $%ld mxn\n", user->balance);
    cont();
    clear();
    printf("Gracias por haber usado Cajeros Cristobalianos S.A. de C.V.\n");
    cont();
}

// error que se muestra cuando el usuario intenta retirar una cantidad de dinero
// que no sea multiplo de 100
int error_mul_100_R(void) {
    clear();

    if (atol(event.args) % 100 != 0)
        printf("El monto ingresado no es multiplo de 100\n");

    else
        printf("No cuentas con los fondos suficientes para retirar %ld\n", atol(event.args));

    cont();
}

// funcion que se encarga de retirar la cantidad ingresada por el usuario de su
// cuenta
int agr_R(void) {
    user->balance -= atol(event.args);

    // genera un registro en los movimientos del usuario
    save_transaction(user->account, "Retiro", atol(event.args));

    // simulando las funciones del framework django para facilitar el codigo
    // guarda los cambios en la "base de datos"
    save_users();

    clear();
    printf("Saldo actual: %ld\n", user->balance);
    cont();
    clear();
    printf("Gracias por haber usado Cajeros Cristobalianos S.A. de C.V.\n");
    cont();
}

// error si el usuario ingresa dos nips que no coinciden cuando este desea
// cambiar su nip
int error_C(void) {
    clear();
    printf("El nip ingresado no coincide con el anterior\n");
    cont();
}

// funcion que se ejecuta para cambiar el nip de un usuario
int agr_C(void) {
    user->nip = strdup(event.args);

    // simulando las funciones del framework django para facilitar el codigo
    // guarda los cambios en la "base de datos"
    save_users();

    clear();
    printf("El nip fue cambiado exitosamente\n");
    cont();
}

int nul(void) {
    }
