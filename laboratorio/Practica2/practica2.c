/*
 * autor: cristobal liendo i
 * fecha: Tue 06 Feb 2018 05:10:24 PM CST
 * descripcion: Genera un arbol de huffman, comprimiendo el archivo
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct l_node_t {
    struct l_node_t *next, *prev;
    struct t_node_t *payload;
} l_node_t;

typedef struct t_node_t {
    struct t_node_t *parent, *left, *right;

    char letter;
    char code;
    unsigned long frequency;
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
t_node_t *create_tree_node(char letter, char code, unsigned long frequency,
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

void create_stack(unsigned long *freq, l_node_t **head) {
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

    while (sum < total) {
        node_1 = pop(head_stack);
        node_2 = pop(head_stack);

        if (node_1 == NULL || node_2 == NULL)
            break;

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

// file operations
unsigned long *get_frequencies(FILE *fp, unsigned long *total) {
    // from ascii...
    unsigned long *frequencies = (unsigned long *) calloc(256, sizeof(unsigned long));
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
    unsigned long *freq, total, new_size = 0;

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

int main(int argc, char **argv) {
    FILE *compressed;

    compress_file(argv[1], argv[2]);

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
