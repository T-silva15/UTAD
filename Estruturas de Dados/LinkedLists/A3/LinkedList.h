// Header file for LINKED_LIST
#ifndef _LINKED_LIST_DEFINITIONS
#define _LINKED_LIST_DEFINITIONS

// ...
//-------------------------------------------------------
#ifndef _LOGICAL
#define _LOGICAL
typedef enum { ERROR = 0, OK = 1 } STATUS;
typedef enum { FALSE = 0, TRUE = 1 } BOOLEAN;
#endif // !_LOGICAL

//-------------------------------------------------------
// linked node and list definitions
struct LIST_NODE {
    int data;
    LIST_NODE* pNext;
};
typedef LIST_NODE* LINKED_LIST;

//-------------------------------------------------------
#ifndef _DATA_MACRO
#define _DATA_MACRO
// macro definition for easy access to single node data field
#define DATA(X) ((X)->data)
#endif // !_DATA_MACRO
//-------------------------------------------------------
#ifndef _LINK_LIST_MACRO
#define _LINK_LIST_MACRO
// macro definition for easy access to single LIST_NODE link field
#define NEXT(X) ((X)->pNext)
#endif // !_LINK_LIST_MACRO


//-------------------------------------------------------
// Functions Declaration --------------------------------
//-------------------------------------------------------


// Constructors and Destructors -------------------------
STATUS newLinkedList(LINKED_LIST*);
STATUS newListNode(LIST_NODE**, int);
STATUS destroyLinkedList(LINKED_LIST*);
// Input and Output -------------------------------------
STATUS putHeadLinkedList(LINKED_LIST*, int);
STATUS removeHeadLinkedList(LINKED_LIST*, int*);
// Query ------------------------------------------------
BOOLEAN emptyLinkedList(LINKED_LIST);
int lengthLinkedList(LINKED_LIST);
LIST_NODE* getHeadLinkedList(LINKED_LIST);
LIST_NODE* getTailLinkedList(LINKED_LIST);
STATUS printLinkedList(LINKED_LIST);
#endif // !_LINKED_LIST_DEFINITIONS