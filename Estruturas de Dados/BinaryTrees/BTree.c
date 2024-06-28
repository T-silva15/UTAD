// Header file for BTREE
#ifndef _BTREE_DEFINITIONS
#define _BTREE_DEFINITIONS

//-------------------------------------------------------
#ifndef _LOGICAL
#define _LOGICAL
typedef enum { ERROR = 0, OK = 1 } STATUS;
typedef enum { FALSE = 0, TRUE = 1 } BOOLEAN;
#endif // !_LOGICAL
//-------------------------------------------------------
// dlink node binary tree definition
typedef struct _BTREE_NODE {
int data;
struct _BTREE_NODE* pL;
struct _BTREE_NODE* pR;
}BTREE_NODE;

// binary tree definition
typedef BTREE_NODE* BTREE;
//-------------------------------------------------------
#ifndef _DATA_MACRO
#define _DATA_MACRO
// macro definition for easy access to BTREE_NODE data field
#define DATA(X) ((X)->data)
#endif // !_DATA_MACRO
//-------------------------------------------------------
#ifndef _CHILDREN_BTREE_MACROS
#define _CHILDREN_BTREE_MACROS
// macros definition for easy access to BTREE_NODE children fields
#define LEFT(X) ((X)->pL)
#define RIGHT(X) ((X)->pR)
#endif // !_CHILDREN_BTREE_MACROS
//-------------------------------------------------------
// Functions Declarations -------------------------------
//-------------------------------------------------------
//-------------------------------------------------------
// Constructors and Destructors -------------------------
STATUS newBTree(BTREE*);
STATUS newBTNode(BTREE*, int);
STATUS createSubBTree(BTREE*, int, BTREE_NODE*, BTREE_NODE*);
STATUS destroyBTree(BTREE*);
//-------------------------------------------------------
// Query - General --------------------------------------
BOOLEAN emptyBTree(BTREE);
BOOLEAN isLeaf(BTREE_NODE*);
int numberNodesBTree(BTREE);
//-------------------------------------------------------
// Query - Printing Tree Values -------------------------
STATUS printInOrderBTree(BTREE);

//-------------------------------------------------------
// Query - Traversing -----------------------------------
STATUS traverseBTreeInOrder(BTREE);

// made by me
STATUS printPreOrderBTree(BTREE);
STATUS printPostOrderBTree(BTREE);
STATUS insertBST(BTREE*, int);
int sumNodesBTree(BTREE);
int maxValBTree(BTREE);
STATUS findNumber(BTREE, int);

#endif // !_BTREE_DEFINITIONS

// Source file for BTREE
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

//-------------------------------------------------
// Constructor and Destructor Functions -----------
STATUS newBTree(BTREE* pBT)
{
    *pBT = NULL;
    return OK;
}
//-------------------------------------------------
STATUS newBTNode(BTREE* pN, int X)
{
    BTREE_NODE* pTempN;
    // node allocation
    if ((pTempN = (BTREE_NODE*)malloc(sizeof(BTREE_NODE))) == NULL)
        return ERROR;
    // btree node update
    DATA(pTempN) = X;
    LEFT(pTempN) = NULL;
    RIGHT(pTempN) = NULL;
    *pN = pTempN;
    return OK;
}
//-------------------------------------------------
STATUS createSubBTree(BTREE* pN, int X, BTREE_NODE* pL, BTREE_NODE* pR)
{
    BTREE_NODE* pTempN;
    // node creation
    if (newBTNode(&pTempN, X) == ERROR) {
        return ERROR;
    }
    // update btree with left and right subtrees
    LEFT(pTempN) = pL;
    RIGHT(pTempN) = pR;
    *pN = pTempN;
    return OK;
}
//-------------------------------------------------
STATUS destroyBTree(BTREE* pBT)
{
    // underflow
    if (*pBT == NULL)
        return ERROR;
    // destroy recursively
    destroyBTree(&LEFT(*pBT));
    destroyBTree(&RIGHT(*pBT));
    // free(DATA(*pBT));
    DATA(*pBT) = -1;
    free(*pBT);
    *pBT = NULL;
    return OK;
}
//-------------------------------------------------
// Query Functions --------------------------------
BOOLEAN emptyBTree(BTREE BT)
{
    return (BT == NULL) ? TRUE : FALSE;
}
//-------------------------------------------------
BOOLEAN isLeaf(BTREE_NODE* pBT)
{
    return ((LEFT(pBT) == NULL) && (RIGHT(pBT) == NULL)) ? TRUE : FALSE;
}
//-------------------------------------------------
int numberNodesBTree(BTREE BT)
{
    /*
    int cnt = 0;
    BTREE tempBT = BT;
    if (emptyBTree(tempBT) == TRUE)
        return cnt;
    int cntL = numberNodesBTree(LEFT(tempBT));
    int cntR = numberNodesBTree(RIGHT(tempBT));
    return (1 + cntL + cntR);
    */

   return BT == NULL ? 0 : 1 + numberNodesBTree(LEFT(BT)) + numberNodesBTree(RIGHT(BT));
}
//-------------------------------------------------
// Query Functions - Traversing -------------------
STATUS traverseBTreeInOrder(BTREE BT)
// non-generic - suitable only for int data
{
    BTREE tempBT = BT;
    if (emptyBTree(tempBT) == TRUE)
        return ERROR;
    traverseBTreeInOrder(LEFT(tempBT));
    // here is printing the node value; but any other action is admissible
    printf("%s, ", DATA(tempBT));
    traverseBTreeInOrder(RIGHT(tempBT));
    return OK;
}
//-------------------------------------------------
// Query Functions - Printing ---------------------
STATUS printInOrderBTree(BTREE BT)
// non-generic - suitable only for int data
{
    BTREE tempBT = BT;
    if (emptyBTree(tempBT) == TRUE)
        return ERROR;
    // print recursively
    printInOrderBTree(LEFT(tempBT));
    printf("%d, ", DATA(tempBT));
    printInOrderBTree(RIGHT(tempBT));
    return OK;
}

// made by me
STATUS printPreOrderBTree(BTREE BT)
// non-generic - suitable only for int data
{
    BTREE tempBT = BT;
    if (emptyBTree(tempBT) == TRUE)
        return ERROR;
    // print recursively
    printf("%d, ", DATA(tempBT));
    printPreOrderBTree(LEFT(tempBT));
    printPreOrderBTree(RIGHT(tempBT));
    return OK;
}

STATUS printPostOrderBTree(BTREE BT)
// non-generic - suitable only for int data
{
    BTREE tempBT = BT;
    if (emptyBTree(tempBT) == TRUE)
        return ERROR;
    // print recursively
    printPostOrderBTree(LEFT(tempBT));
    printPostOrderBTree(RIGHT(tempBT));
    printf("%d, ", DATA(tempBT));
    return OK;
}

STATUS insertBST(BTREE* pBT, int X){
    if (emptyBTree(*pBT)){
        BTREE tempBT;
        if (newBTNode(&tempBT, X) == ERROR){
            return ERROR;
        }
        *pBT = tempBT;
        return OK;
    }

    if (X > DATA(*pBT)){
        insertBST(&RIGHT(*pBT), X);
    }
    else{
        insertBST(&LEFT(*pBT),X);
    }
    return OK;
}

int sumNodesBTree(BTREE BT){

    // stop condition
    if (BT == NULL)
        return 0;

    // recursive call 
    return DATA(BT) + sumNodesBTree(LEFT(BT)) + sumNodesBTree(RIGHT(BT));
}

int maxValBTREE(BTREE BT){
    if (BT == NULL)
        return -1;
    int max = DATA(BT);

    // recursive calls
    int maxL = maxValBTREE(LEFT(BT));
    int maxR = maxValBTREE(RIGHT(BT));

    return (maxL > max) ? maxL : (maxR > max) ? maxR : max;
}

STATUS findNumber(BTREE BT, int X){
    // stop condition
    if (BT == NULL){
        return ERROR;
    }
    if (DATA(BT) == X){
        return OK;
    }

    // calls recursively on right if value is greater and left side if value is smaller
    (X > DATA(BT)) ? findNumber(RIGHT(BT), X) : findNumber(LEFT(BT), X);
}


void main(){
    BTREE btree;
    newBTree(&btree);
    
    insertBST(&btree,10);
    insertBST(&btree,7);
    insertBST(&btree,15);
    insertBST(&btree,9);
    insertBST(&btree,11);
    insertBST(&btree,17);
    insertBST(&btree,8);

    printInOrderBTree(btree);
    printf("\n");
    printPreOrderBTree(btree);
    printf("\n");
    printPostOrderBTree(btree);

    printf("\nsoma dos nos: %d", sumNodesBTree(btree));
    printf("\nmaior valor: %d", maxValBTREE(btree));

    if (findNumber(btree, 7) == OK){
        printf("\nNumero encontrado!");
    }
    else{
        printf("\nNumero nao encontrado!");
    }
}