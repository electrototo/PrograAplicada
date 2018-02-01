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

typedef struct leaf_t {
    struct node_t *data;
    struct leaf_t *next;
} leaf_t;

node_t *create_node(int data, node_t *left, node_t *right);
void insert_tree(int data, node_t **root);
void print_tree(node_t *root);
void free_tree(node_t *root);

void push(node_t *node, leaf_t **head);
node_t *pop(leaf_t **head);

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

void free_tree(node_t *root) {
    if (root == NULL)
        return;
    else {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

void print_tree(node_t *root) {
    leaf_t *stack_head = NULL;
    node_t *current;

    push(root, &stack_head);

    while ((current = pop(&stack_head)) != NULL){
        printf("Node:     %p\n", current);
        printf("Left:     %p\n", current->left);
        printf("Right:    %p\n", current->right);
        printf("Data:     %d\n\n", current->data);

        if (current->right != NULL)
            push(current->right, &stack_head);

        if (current->left != NULL)
            push(current->left, &stack_head);
    }
}

// linked list
leaf_t *new_leaf(node_t *data, leaf_t *next) {
    leaf_t *new_node = (leaf_t *) malloc(sizeof(leaf_t));

    if (new_node == NULL) {
        printf("malloc error\n");
        exit(0);
    }

    new_node->data = data;
    new_node->next = next;

    return new_node;
}

void push(node_t *node, leaf_t **head) {
    leaf_t *new_node = new_leaf(node, *head);
    *head = new_node;
}

node_t *pop(leaf_t **head) {
    node_t *current;
    leaf_t *to_free;

    if (*head == NULL) {
        return NULL;
    }

    to_free = *head;

    current = (*head)->data;
    *head = (*head)->next;

    free(to_free);

    return current;
}
