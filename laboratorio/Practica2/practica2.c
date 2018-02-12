/*
 * autor: cristobal liendo i
 * fecha: Tue 06 Feb 2018 05:10:24 PM CST
 * descripcion: Genera un arbol de huffman, comprimiendo el archivo
*/

#include <stdio.h>
#include <stdlib.h>

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

void print_stack(l_node_t *head) {
    l_node_t *current = head;

    while (current != NULL) {
        printf("Current:     %p\n", current);
        printf("Next:        %p\n", current->next);
        printf("Prev:        %p\n", current->prev);
        printf("Letter:      0x%02x\n\n", current->payload->letter);

        current = current->next;
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

void print_tree(t_node_t *root) {
    if (root == NULL)
        return;

    print_tree(root->left);
    printf("Actual:        %p\n", root);
    printf("Right:         %p\n", root->right);
    printf("Left:          %p\n", root->left);
    printf("Parent:        %p\n", root->parent);
    printf("Letter:        0x%02x\n", root->letter);
    printf("Frequency:     %lu\n", root->frequency);
    printf("Code:          %d\n\n", root->code);
    print_tree(root->right);
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

int main(int argc, char **argv) {
    // frequency test
    FILE *file;
    unsigned long *freq, total;

    l_node_t *head = NULL;
    t_node_t *root;

    file = fopen(argv[1], "rt");
    freq = get_frequencies(file, &total);

    create_stack(freq, &head);
    root = create_tree(&head, total);


    print_tree(root);
    print_stack(head);

    fclose(file);
    free_stack(head);
    free(freq);

    return 0;
}
