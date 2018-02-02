/*
 * autor: cristobal liendo i
 * fecha: Thu 01 Feb 2018 04:35:14 PM CST
 * descripcion: inserta nombres en arboles
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_t {
    char *data;
    struct node_t *left, *right;
} node_t;

node_t *create_node(char *data, node_t *left, node_t *right);
void insert_tree(char *data, node_t **root);
void print_tree(node_t *root);
void free_tree(node_t *root);

char *alloc_str(char *buffer);

int main() {
    char buffer[100];
    node_t *head = NULL;

    printf("Ordena nombres lexicograficamente en un arbol.\n");

    printf("Ingresa los nombres. Escribe fin para terminar\n\n");

    do {
        memset(buffer, 0, 100);
        fgets(buffer, 99, stdin);

        if (strcmp(buffer, "fin\n") != 0)
            insert_tree(alloc_str(buffer), &head);

    } while (strcmp(buffer, "fin\n") != 0);

    print_tree(head);
    free_tree(head);

    return 0;
}

node_t *create_node(char *data, node_t *left, node_t *right) {
    node_t *new_node = (node_t *) malloc(sizeof(node_t));

    if (new_node == NULL) {
        printf("malloc error\n");

        exit(0);
    }

    new_node->left = left;
    new_node->right = right;
    new_node->data = data;

    return new_node;
}

void insert_tree(char *data, node_t **root) {
    if (*root == NULL)
        *root = create_node(data, NULL, NULL);

    else if (strcmp(data, (*root)->data) < 0)
        insert_tree(data, &(*root)->left);

    else
        insert_tree(data, &(*root)->right);
}

void print_tree(node_t *root) {
    if (root == NULL)
        return;


    printf("\nCurrent:     %p\n", root);
    printf("Left:        %p\n", root->left);
    printf("Right:       %p\n", root->right);
    printf("Name:        %s", root->data);

    print_tree(root->left);
    print_tree(root->right);
}

void free_tree(node_t *root) {
    if (root == NULL)
        return;
    else {
        free_tree(root->left);
        free_tree(root->right);
        free(root->data);
        free(root);
    }
}

char *alloc_str(char *buffer) {
    char *pointer = (char *) malloc(strlen(buffer) + 1);
    strcpy(pointer, buffer);

    return pointer;
}
