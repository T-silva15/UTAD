#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>

// Sctruct definition
typedef struct Node{
    int data;
    struct Node* next;
}NODE;

void printList(NODE* n){
    if (n == NULL){
        printf("Lista vazia\n");
        return;
    }

    while(n != NULL){
        printf("%d\n",n->data);
        n = n->next;
    }
}
void deleteList(NODE** n){
    if (*n == NULL){
        printf("Lista vazia\n");
        return;
    }

    while (*n != NULL){
        NODE *current = *n;
        NODE *seguinte = current->next;

        while(current != NULL){
            seguinte = current->next; // Store the next node
            free(current);            // Free the current node
            current = seguinte;       // Move to the next node
        } 
        *n = NULL;
    }
    
}
int tamanhoList(NODE* n){
    if (n == NULL){
        return 0;
    }
    int size = 0;
    while(n != NULL){
        n = n->next;    // Move to the next node
        size++;         // Increment the size
    }
    return size;
}

void main(){
    NODE* primeiro = NULL;
    NODE* segundo = NULL;
    NODE* terceiro = NULL;

    primeiro = (NODE*)malloc(sizeof(NODE));
    segundo = (NODE*)malloc(sizeof(NODE));
    terceiro = (NODE*)malloc(sizeof(NODE));

    primeiro->data = 5;
    primeiro->next = segundo;

    segundo->data = 10;
    segundo->next = terceiro;

    terceiro->data = 15;
    terceiro->next = NULL;

    printList(primeiro);

    printf("Tamanho da lista: %d\n",tamanhoList(primeiro));
    deleteList(&primeiro);
    printf("Tamanho da lista: %d\n",tamanhoList(primeiro));
    printList(primeiro);


}