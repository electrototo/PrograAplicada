/*
 * autor: cristobal liendo i
 * fecha: Tue 06 Jan 2018 18:36:32 PM CST
 * descripcion: arboles
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node_t {
    int data;
    struct node_t *left, *right, *parent;
} node_t;

node_t *create_node(int data, node_t *left, node_t *right, node_t *parent);
void insert_tree(int data, node_t **root);
void print_tree(node_t *root);
void free_tree(node_t *root);

node_t *find_min(node_t *root);
node_t *successor(node_t *root);
void delete_node(node_t **root, node_t *to_delete);
node_t *find_node(int data, node_t *root);
void find_and_delete(int data, node_t **root);

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

                find_and_delete(data, &root);
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

node_t *create_node(int data, node_t *left, node_t *right, node_t *parent) {
    node_t *new_node = (node_t *) malloc(sizeof(node_t));

    if (new_node == NULL) {
        printf("malloc error\n");

        exit(0);
    }

    new_node->left = left;
    new_node->right = right;
    new_node->parent = parent;

    new_node->data = data;

    return new_node;
}

void insert_tree(int data, node_t **root) {
    node_t *parent = NULL;
    node_t *current = *root;

    node_t *new_node;

    while (current != NULL) {
        parent = current;

        if (data < current->data)
            current = current->left;
        else
            current = current->right;
    }

    new_node = create_node(data, NULL, NULL, parent);

    if (parent == NULL)
        *root = new_node;

    else if (data < parent->data)
        parent->left = new_node;

    else
        parent->right = new_node;
}

node_t *find_min(node_t *root) {
    while (root->left != NULL)
        root = root->left;

    return root;
}

node_t *successor(node_t *root) {
    node_t *parent, *current;

    if (root->right != NULL)
        return find_min(root->right);

    parent = root->parent;
    current = root;

    while (parent != NULL && current == parent->right) {
        current = parent;
        parent = parent->parent;
    }

    return parent;
}

void delete_node(node_t **root, node_t *z) {
    node_t *y, *x;

    if (z->left == NULL || z->right == NULL)
        y = z;
    else
        y = successor(z);

    if (y->left != NULL)
        x = y->left;
    else
        x = y->right;

    if (x != NULL)
        x->parent = y->parent;

    if (y->parent == NULL)
        *root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    if (y != z) {
        z->data = y->data;
        free(y);
    }
}

node_t *find_node(int data, node_t *root) {
    if (root == NULL)
        return NULL;

    else if (data == root->data)
        return root;

    else if (data < root->data)
        find_node(data, root->left);

    else
        find_node(data, root->right);
}

void find_and_delete(int data, node_t **root) {
    node_t *pos = find_node(data, *root);
    delete_node(root, pos);
}

void print_tree(node_t *root) {
    if (root == NULL)
        return;

    printf("\nCurrent:     %p\n", root);
    printf("Left:        %p\n", root->left);
    printf("Right:       %p\n", root->right);
    printf("Parent:      %p\n", root->parent);
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
