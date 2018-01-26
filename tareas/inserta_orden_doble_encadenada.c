/*
 * autor: cristobal liendo i
 * fecha: Tue 23 Jan 2018 18:01:30 PM CST
 * descripcion:
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node_t {
    struct node_t *next;
    struct node_t *prev;
    int data;
} node_t;

typedef struct llist_t {
    node_t *head;
    node_t *tail;
} llist_t;

node_t *create_new_node(int data, node_t *next);
node_t *insert_data(int data, llist_t *llist);
void print_list(llist_t *llist);
void free_list(llist_t *llist);
int menu();

int main() {
    llist_t llist;

    llist.head = NULL;
    llist.tail = NULL;

    int choice, data;

    while ((choice = menu()) != 4) {
        switch (choice) {
            case 1:
                printf("Ingresa el dato: ");
                scanf("%d", &data);
                insert_data(data, &llist);
                printf("\n");

                break;

            case 2:
                print_list(head);

                break;

            case 3:
                free_list(&head);
                printf("lista borrada\n");

                break;

            default:
                break;
        }
    }

    free_list(&head);

    return 0;
}

node_t *create_new_node(int data, node_t *next) {
    node_t *new_node = (node_t *) malloc(sizeof(node_t));

    if (new_node == NULL) {
        printf("malloc error\n");

        exit(0);
    }

    new_node->next = next;
    new_node->data = data;

    return new_node;
}

node_t *insert_data(int data, node_t **head) {
    node_t *new_node = create_new_node(data, NULL);
    node_t *current = *head, *prev = NULL;

    while (current != NULL && current->data < data) {
        prev = current;
        current = current->next;
    }

    new_node->next = current;

    if (prev != NULL)
        prev->next = new_node;
    else
        *head = new_node;

    return *head;
}

void print_list(node_t *head) {
    node_t *current = head;

    while (current != NULL) {
        printf("NODE %p\n", current);
        printf("\tdata: %d\n", current->data);
        printf("\tnext: %p\n\n", current->next);

        current = current->next;
    }
}

void free_list(node_t **head) {
    node_t *next;

    while (*head != NULL) {
        next = (*head)->next;
        free(*head);
        *head = next;
    }

    *head = NULL;
}

int menu() {
    int c;

    printf("Menu:\n");
    printf("  [1] Introducir dato\n");
    printf("  [2] Imprimir lista\n");
    printf("  [3] Borrar lista\n");
    printf("  [4] Salir\n");
    printf("Opcion: ");

    scanf("%d", &c);

    printf("\n");

    return c;
}
