#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>
//-------------------------------------------------------

// Source file for LINKED_LIST
#include "LinkedList.h"
//-------------------------------------------------------
// Constructor functions --------------------------------
STATUS newLinkedList(LINKED_LIST* pL)
{
    *pL = NULL;
    return OK;
}
//-------------------------------------------------------
STATUS newListNode(LIST_NODE** pN, int X)
{
    LIST_NODE* pTempN;
    // node allocation
    if ((pTempN = (LIST_NODE*)malloc(sizeof(LIST_NODE))) == NULL) {
        printf("\nLinkedList node: memory allocation error");
        return ERROR;
    }
    // list node update
    *pN = pTempN;
    DATA(pTempN) = X;
    NEXT(pTempN) = NULL;
    return OK;
}
//-------------------------------------------------------
// Destructor functions ---------------------------------
STATUS destroyLinkedList(LINKED_LIST* pL)
{
    int *pX = NULL;
    // underflow
    if (emptyLinkedList(*pL))
        return ERROR;
    // if pX = NULL - don't want to use the deleted data
    while (*pL != NULL)
        removeHeadLinkedList(pL, pX);
    return OK;
}
//-------------------------------------------------------
// Input functions --------------------------------------
STATUS putHeadLinkedList(LINKED_LIST* pL, int X)
{
    LIST_NODE* pTempN;
    // node creation
    if (newListNode(&pTempN, X) == ERROR)
        return ERROR;
    // list update
    NEXT(pTempN) = *pL;
    *pL = pTempN;
    return OK;
}
//-------------------------------------------------------
// Output functions -------------------------------------
STATUS removeHeadLinkedList(LINKED_LIST* pL, int* pX)
{
    LIST_NODE* pAuxN;
    //underflow
    if (emptyLinkedList(*pL))
        return ERROR;
    // node deletion
    pAuxN = *pL;
    *pL = NEXT(*pL);
    // node data and memory handling
    if (pX != NULL) // if pX = NULL - don't want to use the returned data
        *pX = DATA(pAuxN);
    else
        free(pAuxN);
    return OK;
}
//-------------------------------------------------------
// Query functions --------------------------------------
BOOLEAN emptyLinkedList(LINKED_LIST L)
{
    return ((L == NULL) ? TRUE : FALSE);
}
//-------------------------------------------------------
int lengthLinkedList(LINKED_LIST L)
{
    int size = 0;
    LIST_NODE* pAuxL = NULL;
    for (pAuxL = L; pAuxL != NULL; pAuxL = NEXT(pAuxL))
        size++;
    return size;
}
//-------------------------------------------------------
LIST_NODE* getHeadLinkedList(LINKED_LIST L)
{
    if (!emptyLinkedList(L))
        return (L);
    else
        return NULL;
}
//-------------------------------------------------------
LIST_NODE* getTailLinkedList(LINKED_LIST L)
{
    if (emptyLinkedList(L))
        return NULL;
    LIST_NODE* pTempL = L;
    while (NEXT(pTempL) != NULL)
        pTempL = NEXT(pTempL);
    return pTempL;
}
//-------------------------------------------------------
STATUS printLinkedList(LINKED_LIST L)
// non-generic - suitable only for int data
{
    int i = 0;
    LIST_NODE* pAuxL = NULL;
    if (emptyLinkedList(L)) {
        printf("\nEmpty List.\n");
        return ERROR;
    }
    for (pAuxL = L; pAuxL != NULL; pAuxL = NEXT(pAuxL), i++)
        printf("\nList element [%d]: %d", i, DATA(pAuxL));
    return OK;
}
//-------------------------------------------------------