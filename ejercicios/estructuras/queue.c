/*
 * autor: cristobal liendo i
 * fecha: Tue 25 Jan 2018 17:08:30 PM CST
 * descripcion:
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node_t {
    struct node_t *next;
    struct node_t *prev;

    int data;
} node_t;

typedef struct queue_t {
    node_t *head;
    node_t *tail;
} queue_t;

node_t *create_new_node(int data, node_t *next, node_t *prev);

void print_list(queue_t *queue);
void free_list(queue_t *queue);
void enqueue(int data, queue_t *queue);
int dequeue(queue_t *queue, int *error);
int menu();

int main() {
    queue_t queue;
    queue.head = NULL;
    queue.tail = NULL;

    int choice, data, error = 0;

    while ((choice = menu()) != 4) {
        switch (choice) {
            case 1:
                printf("Ingresa el dato: ");
                scanf("%d", &data);
                enqueue(data, &queue);

                printf("\n");

                break;

            case 2:
                print_list(&queue);

                break;

            case 3:
                free_list(&queue);
                printf("lista borrada\n");

                break;

            case 5:
                data = dequeue(&queue, &error);
                printf("dequeue: %d\n", data); 

            default:
                break;
        }
    }

    free_list(&queue);

    return 0;
}

node_t *create_new_node(int data, node_t *next, node_t *prev) {
    node_t *new_node = (node_t *) malloc(sizeof(node_t));

    if (new_node == NULL) {
        printf("malloc error\n");

        exit(0);
    }

    new_node->next = next;
    new_node->data = data;

    return new_node;
}

void enqueue(int data, queue_t *queue) {
    node_t *new_node = create_new_node(data, queue->head, NULL);

    if (queue->tail == NULL)
        queue->tail = new_node;

    if (queue->head != NULL)
        queue->head->prev = new_node;

    queue->head = new_node;
}

int dequeue(queue_t *queue, int *error) {
    node_t *current;
    int data;

    if (queue->tail == NULL) {
        printf("queue undeflow\n");
        *error = 1;

        return 0;
    }

    *error = 0;

    current = queue->tail;
    data = current->data;

    queue->tail = queue->tail->prev;

    if (queue->tail != NULL)
        queue->tail->next = NULL;
    else
        queue->head = NULL;

    free(current);

    return data;
}

void print_list(queue_t *queue) {
    node_t *current = queue->head;

    while (current != NULL) {
        printf("NODE %p\n", current);
        printf("\tdata: %d\n", current->data);
        printf("\tnext: %p\n\n", current->next);
        printf("\tprev: %p\n\n", current->prev);

        current = current->next;
    }
}

void free_list(queue_t *queue) {
    node_t *next;

    while (queue->head != NULL) {
        next = queue->head->next;
        free(queue->head);
        queue->head = next;
    }

    queue->head = NULL;
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
