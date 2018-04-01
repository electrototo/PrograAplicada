/****************************************************************
 *                                                              *
 * Archivo: local.h                                             *
 * Descripcion: Archivo de encabezado para maquina de estados   *
 *      Aqui se definen todos los tipos de datos y              *
 *      constantes que se utilizan en el programa               *
 *                                                              *
 ****************************************************************/

/******************* CONSTANTES *******************
 * En esta seccion se declaran todas las          *
 * las constantes que se necesiten en el programa *
 **************************************************/
#define BUFFER        128
#define L_EVENT_ARGS  21


/****************** ESTRUCTURAS *****************
 * En esta seccion se declaran todas las        *
 * estructuras que se necesiten en el programa  *
 ************************************************/

// Este tipo de datos se utiliza para leer la informacion
// que teclea el usuario
struct event_s {
    int etype;
    char args[L_EVENT_ARGS];
};
typedef struct event_s EVENT;

// Este tipo de datos se utiliza para implementar
// la tabla auxiliar
struct aux_table_s {
    int (*action)();
    int moreacts;
    int nextstate;
};
typedef struct aux_table_s AUX_TAB;

// Este tipo de datos se utiliza para implementar
// la tabla de accion
struct action_tab_s {
    int event;
    int (*action)();
    int moreacts;
    int nextstate;
};
typedef struct action_tab_s ACTION_TAB;

// Este tipo de datos se utiliza para implementar
// la tabla de estados
struct state_tab_s {
    int state;
    int start;
    int end;
};
typedef struct state_tab_s STATE_TAB;

typedef struct user_t {
    char *name, *account, *nip;
    long balance;
    int active;
} user_t;

typedef struct node_t {
    struct node_t *next, *prev;
    user_t payload;
} node_t;

typedef struct llist_t {
    node_t *head, *tail;
} llist_t;

/********************* GLOBALES ***********************
 * En esta seccion se pueden declarar todas           *
 * variables globales que se necesiten en el programa *
 ******************************************************/
llist_t users;
user_t user;

/********************* EVENTOS *******************
 * En esta seccion se declarar como constantes   *
 * los eventos (entradas) que recibe el programa *
 *************************************************/


/********************* ESTADOS ******************
 * En esta seccion se declarar como constantes  *
 * los estados de que consta el programa        *
 ************************************************/
#define INIT 0
#define MAIN 1
#define DEPOSIT 2
#define WITHDRAWAL 3
#define MOV 4
#define CHANGE 5
