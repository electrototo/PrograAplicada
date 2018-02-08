/*
 * autor: cristobal liendo i
 * fecha: Tue 06 Jan 2018 18:36:32 PM CST
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

void find_erase(int data, node_t **root, node_t **parent);
void insert_branch(node_t *branch, node_t **root);

int menu();

int main() {
    int data, choice;
    node_t *root = NULL;

    while ((choice = menu()) < 4) {
        switch (choice) {
            case 1:
                printf("Dato: ");
                scanf("%d", &data);
                getchar();
                insert_tree(data, &root);
                break;
            case 2:
                printf("Ingresa el dato a borrar: ");
                scanf("%d", &data);
                getchar();

                find_erase(data, &root, NULL);
                break;

            case 3:
                print_tree(root);
                break;

            default:
                break;
        }
    }
    free_tree(root);

    return 0;
}

void find_erase(int data, node_t **root, node_t **parent) {
    node_t *left_branch, *right_branch;

    if (*root == NULL)
        return;
    else if (data == (*root)->data) {
        left_branch = (*root)->left;
        right_branch = (*root)->right;

        *root = NULL;

        insert_branch(right_branch, parent);
        insert_branch(left_branch, parent);

    }
    else if (data < (*root)->data)
        find_erase(data, &(*root)->left, root);
    else
        find_erase(data, &(*root)->right, root);
}

void insert_branch(node_t *branch, node_t **root) {
    if (*root == NULL || branch == NULL)
        *root = branch;

    else if (branch->data < (*root)->data)
        insert_branch(branch, &(*root)->left);

    else
        insert_branch(branch, &(*root)->right);
}

int menu() {
    int data;

    printf("\n[1] Ingresar dato\n");
    printf("[2] Borrar dato\n");
    printf("[3] Imprimir arbol\n");
    printf("[4] Salir\n");
    printf("Opcion: ");
    scanf("%d", &data);

    return data;
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
