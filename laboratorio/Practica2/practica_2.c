/*
 * autor: cristobal liendo i
 * fecha: Tue 06 Feb 2018 05:10:24 PM CST
 * descripcion: Genera un arbol de huffman, comprimiendo el archivo
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "practica_2.h"

int main(int argc, char **argv) {
    FILE *compressed;
    int choice, status;

    unsigned char length = 0;

    float frequencies[255];
    char *codes[255], buffer[1024];

    l_node_t *stack_head = NULL;
    t_node_t *tree_root = NULL;

    for (int i = 0; i < 255; i++)
        frequencies[i] = 0;

    splash();

    while ((choice = menu()) != 9) {
        switch (choice) {
            case 1:
                // introducir simbolo
                status = insert_symbol(frequencies);

                if (status == ADD_SYMBOL)
                    length++;

                break;

            case 2:
                // listar simbolos
                print_frequencies(frequencies);

                break;

            case 3:
                // borrar simbolo
                delete_symbol(frequencies);
                length--;

                break;

            case 4:
                // guardar simbolos en archivo
                dump_symbols(frequencies, length);

                break;

            case 5:
                // leer simbolos de archivo
                read_symbols(frequencies);

                break;

            case 6:
                // generar codigos
                gen_print_codes(frequencies, codes, 1);

                break;

            case 7:
                // codificar mensaje
                codify(frequencies, codes);

                break;

            case 8:
                // decodificar mensaje
                decodify(frequencies, codes);

                break;

            default:
                break;
        }
    }

    return 0;
}

void clear_buff() {
    char c;

    while ((c = getchar()) != '\n' && c != EOF);
}

void cont() {
    printf("\nPresiona enter para continuar...");
    getchar();
}

void splash() {
    system("clear");
    printf("Huffman Coding\n");
    printf("Disenado e implementado por Cristobal Liendo\n");
    cont();
    system("clear");
    printf("Este es un sistema disenado para poder comprimir archivos de texto de acuerdo con el metodo\n");
    printf("de Huffman. Es conocido como un algoritmo \"envidioso\" (greedy en ingles) por la manera en\n");
    printf("la que opera, el cual es siempre escoger el camino mas eficiente.\n\n");
    printf("El usuario debera ingresar las probabilidades para cada simbolo para poder comprimir de manera\n");
    printf("adecuada el texto, aunque tambien se le ofrece la posibilidad de obtenerlas automaticamente\n\n");
    cont();
}

int menu() {
    int choice;

    system("clear");
    printf("Menu\n");
    printf("[1] Introducir simbolo\n");
    printf("[2] Listar simbolos\n");
    printf("[3] Borrar simbolo\n");
    printf("[4] Guardar simbolos en archivo\n");
    printf("[5] Leer simbolos en archivo\n");
    printf("[6] Generar codigos\n");
    printf("[7] Codificar mensaje\n");
    printf("[8] Decodificar mensaje\n");
    printf("[9] Salir\n");

    do {
        printf("Opcion: ");
        scanf("%d", &choice);
        getchar();
    } while (choice < 1 || choice > 9);

    system("clear");

    return choice;
}

int insert_symbol(float *frequencies) {
    int error = 0;
    char symbol, choice = 0;
    float frequency;

    printf("Ingresa el simbolo: ");
    symbol = getchar();
    clear_buff();

    t_node_t *tree_node;

    if (frequencies[symbol] != 0) {
        printf("El simbolo %c ya tiene una frecuencia asociada. Cambiar la frecuencia [s,n]? ", symbol);
        scanf("%c", &choice);
        clear_buff();

        if (choice != 's' && choice != 'n') {
            printf("Opcion no reconocida\n");
            cont();

            return EXIT;
        }

        if (choice == 'n')
            return EXIT;
    }

    do {
        if (error) {
            printf("\tLa frecuencia debe ser un numero entre el 0 y 100\n");
            error = 0;
        }
        printf("Ingresa la frecunecia: ");
        scanf("%f", &frequency);
        getchar();

        error = 1;
    } while (frequency > 100 || frequency <= 0);

    frequencies[symbol] = frequency;

    cont();

    if (choice == 's')
        return CHANGE_SYMBOL;
    else
        return ADD_SYMBOL;
}

void print_frequencies(float *frequencies) {
    int set = 0;
    for (int i = 0; i < 254; i++) {
        if (frequencies[i] > 0) {
            set = 1;
            printf("Simbolo: %c, frequencia: %2.2f%%\n", i, frequencies[i]);
        }
    }

    if (!set)
        printf("\tNo hay frecuencias registradas\n");

    cont();
}

void delete_symbol(float *frequencies) {
    char letter;

    printf("Ingresa el simbolo a borrar: ");
    scanf("%c", &letter);
    getchar();

    if (frequencies[letter] > 0) {
        frequencies[letter] = 0;
        printf("Simbolo exitosamente borrado\n");
    }

    else
        printf("El simbolo ingresado no estaba registrado\n");

    cont();
}

FILE *open_file(char *mode) {
    FILE *fp;
    char filename[100];

    printf("Ingresa el nombre del archivo: ");
    scanf("%s", filename);
    getchar();

    fp = fopen(filename, mode);

    if (fp == NULL) {
        printf("Hubo un error al abrir el archivo\n");

        return NULL;
    }

    return fp;
}

void dump_symbols(float *frequencies, unsigned char length) {
    FILE *dump = open_file("wt");

    fprintf(dump, "%c\n", length);

    for (unsigned char i = 0; i < 255; i++) {
        if (frequencies[i] > 0)
            fprintf(dump, "%c,%.2f\n", i, frequencies[i]);
    }

    printf("Simbolos exitosamente guardados\n");
    cont();

    fclose(dump);
}

int read_symbols(float *frequencies) {
    FILE *dump = open_file("rb");

    unsigned char length;
    unsigned char symbol;
    float frequency;

    fscanf(dump, "%c\n", &length);

    for (int i = 0; i < 255; i++)
        frequencies[i] = 0;

    for (unsigned char i = 0; i < length; i++) {
        fscanf(dump, "%c,%f\n", &symbol, &frequency);
        frequencies[symbol] = frequency;
    }

    fclose(dump);

    printf("Simbolos leidos: %d\n", length);
    cont();

    return length;
}

t_node_t *gen_print_codes(float *freq, char **codes, int print) {
    t_node_t *root;
    l_node_t *head = NULL;

    float total = 0;

    for (int i = 0; i < 255; i++)
        total += freq[i];

    if (total == 100) {
        create_stack(freq, &head);
        root = create_tree(&head, 100);
        create_codes(root, NULL, 0, codes);

        printf("Codigos:\n");

        for (int i = 0; i < 255; i++)
            if (freq[i] != 0)
                printf("Simbolo %c: %s\n", i, codes[i]);
    }
    else
        printf("Las frecuencias no suman 100%%\n");

    if (print == 1)
        cont();

    return root;
}

void codify(float *freq, char **codes) {
    // generar nuevos codigos
    char buffer[1024];
    int len, error = 0;

    printf("Usando los siguientes codigos:\n");
    gen_print_codes(freq, codes, 0);

    printf("Ingresa el mensaje a codificar:\n\n");
    fgets(buffer, 1023, stdin);

    len = strlen(buffer) - 1;
    buffer[len] = 0;

    // sanity check
    for (int i = 0; i < len; i++) {
        if (freq[buffer[i]] == 0) {
            printf("El caracter %c no se encuentra guardado\n", buffer[i]);
            error = 1;
        }
    }

    fseek(stdin, 0, SEEK_END);

    if (error)
        printf("Para generar los codigos, favor de corregir los errores\n");

    else {
        printf("Mensaje codificado:\n");
        for (int i = 0; i < len; i++)
            printf("%s", codes[buffer[i]]);

        printf("\n");
    }

    cont();

    return;
}

void decodify(float *freq, char **codes) {
    // generar nuevos codigos
    char buffer[2048], actual, code[16];
    int len, code_index = 0;

    t_node_t *root, *actual_node;

    printf("Usando los siguientes codigos para decodificar:\n");
    root = gen_print_codes(freq, codes, 0);

    actual_node = root;

    printf("Ingresa los simbolos a decodificar:\n\n");
    fgets(buffer, 2047, stdin);

    len = strlen(buffer) - 1;
    buffer[len] = 0;

    printf("\nMensaje decodificado:\n");
    for (int i = 0; i <= len; i++) {
        actual = buffer[i];

        if (actual_node != NULL) {
            if (actual_node->left == NULL && actual_node->right == NULL) {
                printf ("%c", actual_node->letter);
                actual_node = root;

                code_index = 0;
            }

            if (actual == '1') {
                actual_node = actual_node->right;
                code[code_index++] = '1';
            }
            else {
                actual_node = actual_node->left;
                code[code_index++] = '0';
            }
        }
        else {
            code[code_index] = 0;

            printf("Error, el codigo %s no se encuentra registrado\n", code);
            code_index = 0;
        }
    }

    printf("\n");

    cont();
}

// stack operations
l_node_t *create_llist_node(t_node_t *payload, l_node_t *next, l_node_t *prev) {
    l_node_t *new_node = (l_node_t *) malloc(sizeof(l_node_t));

    if (new_node == NULL) {
        printf("malloc error\n");
        exit(0);
    }

    new_node->next = next;
    new_node->prev = prev;

    new_node->payload = payload;

    return new_node;
}

void push(t_node_t *data, l_node_t **head) {
    // mayor a menor
    l_node_t *new_node = create_llist_node(data, NULL, NULL);
    l_node_t *current = *head, *prev = NULL;

    while (current != NULL && current->payload->frequency < new_node->payload->frequency) {
        prev = current;
        current = current->next;
    }

    if (prev == NULL)
        *head = new_node;
    else
        prev->next = new_node;

    if (current != NULL)
        current->prev = new_node;

    new_node->prev = prev;
    new_node->next = current;
}

t_node_t *pop(l_node_t **head) {
    l_node_t *current;
    t_node_t *payload;

    if (*head == NULL)
        return NULL;

    current = *head;
    payload = current->payload;

    *head = (*head)->next;

    free(current);

    return payload;
}

void free_stack(l_node_t *head) {
    l_node_t *current = head;
    l_node_t *tmp;

    while (current != NULL) {
        tmp = current->next;
        free(current->payload);
        free(current);
        current = tmp;
    }
}

// tree operations
t_node_t *create_tree_node(char letter, char code, float frequency,
        t_node_t *left, t_node_t *right, t_node_t *parent) {

    t_node_t *new_node = (t_node_t *) malloc(sizeof(t_node_t));

    if (new_node == NULL) {
        printf("malloc error\n");
        exit(0);
    }

    new_node->letter = letter;
    new_node->code = code;
    new_node->frequency = frequency;

    new_node->left = left;
    new_node->right = right;
    new_node->parent = parent;

    return new_node;
}

void create_stack(float *freq, l_node_t **head) {
    t_node_t *tree_node;

    for (int i = 0; i < 255; i++) {
        if (freq[i] > 0) {
            tree_node = create_tree_node(i, 0, freq[i], NULL, NULL, NULL);
            push(tree_node, head);
        }
    }
}

t_node_t *create_tree(l_node_t **head_stack, unsigned long total) {
    unsigned long sum = 0, accum = 0;
    t_node_t *new_node = NULL;
    t_node_t *node_1, *node_2;

    while ((node_1 = pop(head_stack)) != NULL && (node_2 = pop(head_stack)) != NULL) {
        node_1->code = 0;
        node_2->code = 1;

        sum = node_1->frequency + node_2->frequency;

        new_node = create_tree_node(';', 0, sum, node_1, node_2, NULL);

        node_1->parent = new_node;
        node_2->parent = new_node;

        push(new_node, head_stack);
    }

    return new_node;
}

void create_codes(t_node_t *root, char *code, int level, char **codes) {
    if (root == NULL)
        return;

    if (code == NULL)
        code = (char *) calloc(64, sizeof(char));

    // leaf node
    if (root->right == NULL && root->left == NULL)
        codes[root->letter] = strdup(code);

    level++;
    strcat(code, "0");
    create_codes(root->left, code, level, codes);

    code[level - 1] = 0;
    strcat(code, "1");
    create_codes(root->right, code, level, codes);
}
