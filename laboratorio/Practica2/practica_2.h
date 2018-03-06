/*
 * autor: cristobal liendo i
 * fecha: Mon 5 Mar 2018 22:04:00 PM CST
 * descripcion: declaracion de funciones 
*/

#ifndef PRACTICA_2H
#define PRACTICA_2H 

#define ADD_SYMBOL 1
#define CHANGE_SYMBOL 0
#define EXIT -1;

/**
@brief: nodos del stack
*/
typedef struct l_node_t {
    struct l_node_t *next, *prev;
    struct t_node_t *payload;
} l_node_t;

/**
@brief: nodos de arbol
*/
typedef struct t_node_t {
    struct t_node_t *parent, *left, *right;

    char letter;
    char code;
    float frequency;
} t_node_t;

/**
@brief: crea un nodo de lista
@param payload   un nodo de arbol
@param next      el siguiente elemento de la lista
@param prev      el nodo previo de la lista
@return nodo de una lista
*/
l_node_t *create_llist_node(t_node_t *payload, l_node_t *next, l_node_t *prev);

/**
@brief  inserta un elemento al stack
@param data   un nodo de un arbol
@param head   la cabeza de la lista
*/
void push(t_node_t *data, l_node_t **head);

/**
@brief  quita un elemento del stack
@param head   la cabeza de la lista
@return nodo de un arbol
*/
t_node_t *pop(l_node_t **head);

/**
@brief  libera de la memoria la lista
@param head   la cabeza de la lista
*/
void free_stack(l_node_t *head);

/**
@brief  crea un nodo de arbol
@param letter      el simbolo a guardar
@param code        sin uso
@param frequency   la frecuencia del simbolo
@param left, right hijos del nodo
@param parent      padre del nodo
@return un nodo de un arbol
*/
t_node_t *create_tree_node(char letter, char code, float frequency,
        t_node_t *left, t_node_t *right, t_node_t *parent);

/**
@brief  crea un stack a partir de frecuencias
@param freq  arreglo con frecuencias
@param head  cabeza de la lista
*/
void create_stack(float *freq, l_node_t **head);

/**
@brief crea un arbol de huffman a partir de un stack
@param head_stack  la cabeza del stack
@param total       el total de frecuencias
*/
t_node_t *create_tree(l_node_t **head_stack, unsigned long total);

/**
@brief crea los codigos de huffman
@param root  la raiz del arbol
@param code  el codigo actual
@param codes los codigos huffman
*/
void create_codes(t_node_t *root, char *code, int level, char **codes);

/**
@brief limpia el buffer de stdin
*/
void clear_buff();

/**
@brief imprime el mensaje de "continuar"
*/
void cont();

/**
@brief imprime el mensake inicial
*/
void splash();

/**
@brief imprime las opciones que tiene el usuario
*/
int menu();

/**
@brief inserta un simbolo y una frecuencia
@param lista de frecuencias
*/
int insert_symbol(float *frequencies);

/**
@brief imprime las frecuencias de un arreglo
@param frequencies el arrego con las frecuencias de los simbolos
*/
void print_frequencies(float *frequencies);

/**
@brief borra un simbolo de las frecuencias
@param frequencies frecuencias
*/
void delete_symbol(float *frequencies);

/**
@brief abre un archivo, manejando errores
@param mode el modo en el que se desea abrir el archivo
@return archivo
*/
FILE *open_file(char *mode);

/**
@brief guarda los simbolos en un archivo
@param frequencies  el arreglo con frecuencias
@param length       la cantidad total de simbolos
*/
void dump_symbols(float *frequencies, unsigned char length);

/**
@brief lee los simbolos y sus frecuencias de un archivo
@return cantidad total de simbolos leidos
*/
int read_symbols(float *frequencies);

/**
@brief genera e imprime los codigos
@param codes  arreglo de codigos de huffman
@param print  bandera para imprimir mensaje de continuacion
@return raiz del arbol
*/
t_node_t *gen_print_codes(float *freq, char **codes, int print);

/**
@brief codifica un mensaje
@param freq   el arreglo con frecuencias
@param codes  arreglo de codigos de huffman
*/
void codify(float *freq, char **codes);

/**
@brief decodifica una serie de codigos
@param freq   el areglo con frecuencias
@param codes  arreglo de codigos de huffman
*/
void decodify(float *freq, char **codes);
#endif
