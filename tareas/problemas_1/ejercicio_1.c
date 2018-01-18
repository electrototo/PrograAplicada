/*
 * autor: cristobal liendo
 * fecha: 17/1/18
 * descripcion: pide "n" cantidad de numeros distinots de cero, imprime los numeros
 *              y termina con el valor de 0. se despliega la cantidad de valores
 *              leidos
 *              (el ejercicio no dice cuantos numeros se van a introducir, he ahi
 *               la eleccion de single linked-lists)
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node_t {
    int data;
    struct node_t *next;
} node_t;

node_t *insert(int data, node_t **head);

void print_list(node_t *head);
void free_list(node_t **head);

int main() {
    node_t *head = NULL;
    int number, total = 0;

    printf("Ingresa los numeros a guardar, para terminar ingresa el numero 0:\n");

    do {
        printf("Numero: ");
        scanf("%d", &number);

        if (number != 0) {
            total++;
            insert(number, &head);
        }

    } while (number != 0);
    
    printf("\nNumeros almacenados:\n");
    print_list(head);
    free_list(&head);

    printf("\nTotal: %d\n", total);

    return 0;
}

node_t *insert(int data, node_t **head) {
    node_t *new_node = malloc(sizeof(node_t));

    if (new_node == NULL) {
        printf("Error de memoria. Abortando.\n");
        exit(0);
    }

    new_node->data = data;
    new_node->next = *head;

    *head = new_node;

    return new_node;
}

void print_list(node_t *head) {
    node_t *current = head;

    while (current != NULL) {
        printf("Numero: %d\n", current->data);

        current = current->next;
    }
}

void free_list(node_t **head) {
    node_t *next = *head;

    while (next != NULL) {
        next = (*head)->next;
        free(*head);
        *head = next;
    }
}
