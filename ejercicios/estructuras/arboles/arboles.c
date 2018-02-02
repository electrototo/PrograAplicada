/*
 * autor: cristobal liendo i
 * fecha: Tue 30 Jan 2018 05:46:32 PM CST
 * descripcion: arboles
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node_t {
    int data;
    struct node_t *left, *right;
} node_t;

node_t *create_node(int data, node_t *left, node_t *right);
void insert_tree(int data, node_t **root);
void print_tree(node_t *root);
void free_tree(node_t *root);

int main() {
    int data;
    node_t *root = NULL;

    while (scanf("%d", &data))
        insert_tree(data, &root);

    print_tree(root);
    free_tree(root);

    return 0;
}

node_t *create_node(int data, node_t *left, node_t *right) {
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

void insert_tree(int data, node_t **root) {
    if (*root == NULL)
        *root = create_node(data, NULL, NULL);

    else if (data < (*root)->data)
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
    printf("Data:        %d\n", root->data);

    print_tree(root->left);
    print_tree(root->right);
}

void free_tree(node_t *root) {
    if (root == NULL)
        return;
    else {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}
