/*
 * autor: cristobal liendo i
 * fecha: Tue 06 Feb 2018 05:10:24 PM CST
 * descripcion: Genera un arbol de huffman, comprimiendo el archivo
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ADD_SYMBOL 1
#define CHANGE_SYMBOL 0

typedef struct l_node_t {
    struct l_node_t *next, *prev;
    struct t_node_t *payload;
} l_node_t;

typedef struct t_node_t {
    struct t_node_t *parent, *left, *right;

    char letter;
    char code;
    float frequency;
} t_node_t;

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

    if (*head == NULL) {
        printf("underflow\n");

        return NULL;
    }

    current = *head;
    payload = current->payload;

    *head = (*head)->next;

    free(current);

    return payload;
}

l_node_t *find_list(char symbol, l_node_t *head) {
    l_node_t *actual = head;

    while (actual != NULL && actual->payload->letter != symbol)
        actual = actual->next;

    return actual;
}

void modify_freq(char symbol, float new_frequency, l_node_t **head) {
    l_node_t *actual = find_list(symbol, *head);

    if (actual != NULL)
        actual->payload->frequency = new_frequency;
}

void delete_list(char symbol, l_node_t **head) {
    l_node_t *actual = find_list(symbol, *head);

    if (actual != NULL) {
        if (actual->next != NULL)
            actual->next->prev = actual->prev;

        if (actual->prev != NULL)
            actual->prev->next = actual->next;

        if (actual->next == NULL && actual->prev == NULL)
            *head = NULL;

        free(actual);
    }
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

// TODO: la frecuencia total no importa, asignarle una posicion de 0 a 255
// file operations
float *get_frequencies(FILE *fp, unsigned long *total) {
    // from ascii...
    float *frequencies = (float *) calloc(255, sizeof(float));
    unsigned long in_total = 0;

    unsigned char data;
    int non_zeros = 0;

    fseek(fp, 0, SEEK_SET);

    while (!feof(fp)) {
        data = fgetc(fp);
        frequencies[data]++;

        in_total++;
    }

    *total = in_total;

    fseek(fp, 0, SEEK_SET);

    return frequencies;
}

void compress_file(char *input, char *output) {
    FILE *file, *compressed;
    unsigned long total, new_size = 0;

    float *freq;

    l_node_t *head = NULL;
    t_node_t *root = NULL;

    char *codes[256], *start;
    unsigned char to_write = 0, index = 0;

    file = fopen(input, "rt");

    if (file == NULL) {
        printf("\tEl archivo %s no existe\n", input);

        return;
    }

    compressed = fopen(output, "wb");

    if (compressed == NULL) {
        printf("\tHubo un error al abrir %s\n", output);

        return;
    }

    freq = get_frequencies(file, &total);
    create_stack(freq, &head);
    root = create_tree(&head, total);

    for (int i = 0; i < 255; i++)
        if (freq[i] != 0)
            printf("letra: %c, frecuencia: %.2f\n", i, freq[i]);

    create_codes(root, NULL, 0, codes);

    for (int i = 0; i < 255; i++)
        if (freq[i])
            printf("Codigo para la letra 0x%02x (%c): %s\n", i, i, codes[i]);

    while (!feof(file)) {
        start = codes[fgetc(file)];

        while (*start) {
            if (index == 8) {
                fputc(to_write, compressed);

                index = 0;
                to_write = 0;
                new_size++;
            }

            to_write |= (*start == '1') << (7 - index);
            index++;
            start++;
        }
    }

    if (index != 0) {
        fputc(to_write, compressed);
        new_size++;
    }

    printf("\n[+] Peso total del archivo original:      %lu bytes\n", total);
    printf("[+] Peso total del archivo comprimido:    %lu bytes\n", new_size);
    printf("[+] Porcentaje de reduccion:              %.2f%%\n", ((float) new_size / total) * 100);

    fclose(file);
    fclose(compressed);

    free_stack(head);
    free(freq);
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
    scanf("%c", &symbol);
    getchar();

    t_node_t *tree_node;

    if (frequencies[symbol] != 0) {
        printf("El simbolo %c ya tiene una frecuencia asociada. Cambiar la frecuencia [s,n]? ", symbol);
        scanf("%c", &choice);
        getchar();

        if (choice != 'y' || choice != 'n') {
            printf("Opcion no reconocida\n");

            return -1;
        }

        if (choice == 'n')
            return -1;
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
            printf("Simbolo: %c, frequencia: %.2f\n", i, frequencies[i]);
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

    for (unsigned char i = 0; i < length; i++) {
        fscanf(dump, "%c,%f\n", &symbol, &frequency);
        frequencies[symbol] = frequency;
    }

    fclose(dump);

    printf("Simbolos leidos: %d\n", length);
    cont();

    return length;
}

void gen_print_codes(float *freq, char **codes) {
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

    cont();

    return;
}

int main(int argc, char **argv) {
    FILE *compressed;
    int choice, status;

    unsigned char length = 0;

    float frequencies[255];
    char *codes[255];

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
                gen_print_codes(frequencies, codes);

                break;

            case 7:
                // codificar mensaje
                break;

            case 8:
                // decodificar mensaje
                break;

            default:
                break;
        }
    }

    // compress_file(argv[1], argv[2]);

    // Decomprimir texto
    /*
    compressed = fopen(argv[2], "rb");

    char read = 0;
    t_node_t *current = root;
    unsigned long read_bytes = 0;

    while (!feof(compressed)) {
        to_write = fgetc(compressed);

        for (int i = 0; i < 8 && read_bytes < total - 1; i++) {
            read = to_write & (1 << (7 - i));

            if (read)
                current = current->right;
            else
                current = current->left;

            if (current->right == NULL && current->left == NULL) {
                printf("%c", current->letter);
                read_bytes++;

                current = root;
            }
        }
    }

    fclose(compressed);
    */

    return 0;
}
