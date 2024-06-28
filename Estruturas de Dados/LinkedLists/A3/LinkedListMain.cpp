#include "LinkedList.cpp"
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

// Returns a reversed linked list
LINKED_LIST reverseLinkedList(LINKED_LIST List){
    LINKED_LIST reversedList;
    newLinkedList(&reversedList);
    int pX;
    int size = lengthLinkedList(List);
    
    for (int i = 0; i < size; i++){
        pX = getHeadLinkedList(List)->data;
        putHeadLinkedList(&reversedList, pX);
        List = List->pNext;
    }
    return reversedList;
}   


int main(){

    LINKED_LIST a;
    LINKED_LIST b;

    newLinkedList(&a);

    putHeadLinkedList(&a, 5);
    putHeadLinkedList(&a, 10);
    putHeadLinkedList(&a, 15);

    b = reverseLinkedList(a);

    printf("\nlista a");
    printLinkedList(a);
    printf("\nlista b");
    printLinkedList(b);
    
    return 0;
}