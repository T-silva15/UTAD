
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

// Header file for LINKED_LIST
#ifndef _LINKED_LIST_DEFINITIONS
#define _LINKED_LIST_DEFINITIONS

//-------------------------------------------------------
#ifndef _LOGICAL
#define _LOGICAL
typedef enum { ERROR = 0, OK = 1 } STATUS;
typedef enum { FALSE = 0, TRUE = 1 } BOOLEAN;
#endif // !_LOGICAL

#define MAX_CHARS 50

//-------------------------------------------------------
// linked node and list definitions

typedef struct {
    char nome[MAX_CHARS];
    float custo;
    BOOLEAN estado;
    int liga;
}STATION;


typedef struct _LIST_NODE {
    STATION* data;
    struct _LIST_NODE* pNext;
}LIST_NODE;

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
STATUS newListNode(LIST_NODE**, STATION*);
STATUS destroyLinkedList(LINKED_LIST*);

// Input and Output -------------------------------------
STATUS putHeadLinkedList(LINKED_LIST*, STATION*);
STATUS removeHeadLinkedList(LINKED_LIST*, STATION**);

// Query ------------------------------------------------
BOOLEAN emptyLinkedList(LINKED_LIST);
int lengthLinkedList(LINKED_LIST);
LIST_NODE* getHeadLinkedList(LINKED_LIST);
LIST_NODE* getTailLinkedList(LINKED_LIST);
STATUS printLinkedList(LINKED_LIST);
#endif // !_LINKED_LIST_DEFINITIONS

STATUS startMetroLines(LINKED_LIST*, int);
STATUS addStation(LINKED_LIST*, char*);
void printMetroLine(LINKED_LIST);
void destroyMetroNetwork(LINKED_LIST*);
STATUS ReadLine(LINKED_LIST*, const char*);
STATUS saveMetroLines(LINKED_LIST, int);

// made by me
int getPosition(LINKED_LIST, const char* );
float lineCost(LINKED_LIST);   
STATUS enableStation(LINKED_LIST, const char*);
STATUS existStation(LINKED_LIST, const char*);
STATUS deleteStation(LINKED_LIST*, const char*);

int main()
{
    LINKED_LIST metroNetwork = NULL;
    int c, nLines;
    BOOLEAN out = FALSE;
    printf("Number of Metro Line: ");
    scanf("%d", &nLines);
    //flush the input buffer
    while ((c = getchar()) != '\n');
    system("cls");
    if (startMetroLines(&metroNetwork, nLines) == ERROR)
        return ERROR;
    do {
        fprintf(stdout, "\n\n");
        fprintf(stdout, "0 -- Exit\n");
        fprintf(stdout, "1 -- Add station (enter Line, Station and Position)\n");
        fprintf(stdout, "2 -- Delete Station (enter Line and Station)\n");
        fprintf(stdout, "3 -- On/Off Station (enter Station)\n");
        fprintf(stdout, "4 -- Journey Fare (enter Origin and Destination)\n");
        fprintf(stdout, "5 -- Print line (enter Line)\n");
        fprintf(stdout, "6 -- Save lines data\n");
        fprintf(stdout, "\nOption: ");
        scanf("%d", &c);
        //flush the input buffer
        while (getchar() != '\n');

        switch (c) {
        case 0: out = TRUE;
            break;
        case 1: 
            char afterStation[50];
            printf("Inserir a seguir a que estacao: ");
            scanf("%s", afterStation);
            
            if (addStation(&metroNetwork, afterStation) == OK)
                printf("Estacao Adicionada com sucesso!\n");
            else
                printf("ERRO!\n");
            break;

        case 2: 
            char stationDelete[50];
            printf("Nome da estacao a eliminar: ");
            scanf("%s", stationDelete);
            if (deleteStation(&metroNetwork, stationDelete) == OK)
                printf("Estacao eliminada com sucesso!\n");
            else
                printf("ERRO!\n");
            break;
        case 3: 
            char stationEnable[50];
            printf("Nome da estacao a Ativar/Desativar: ");
            scanf("%s", stationEnable);
            if (enableStation(metroNetwork, stationEnable) == OK)
                printf("Estacao adicionada com sucesso!\n");
            else
                printf("ERRO!\n");
            break;
        case 4:
            float custo = lineCost(metroNetwork);
        if (custo != -1){
            printf("Custo da viagem: %.2f\n", custo);
        }
        break;

        case 5: printMetroLine(metroNetwork);
            break;
        case 6: saveMetroLines(metroNetwork, nLines);
            break;
        default:fprintf(stdout, "Invalid option\n\n");
        }
    } while (out != TRUE);

    destroyMetroNetwork(&metroNetwork);

    return OK;


}
STATUS startMetroLines(LINKED_LIST* list, int nlines)
{
    char nomeArquivo[20];

    sprintf(nomeArquivo, "line%d.txt", nlines);
    if (ReadLine(list, nomeArquivo))
        return OK;
    return ERROR;
}

STATUS ReadLine(LINKED_LIST* list, const char* filename)
{
    FILE* fp;
    STATION* pt;
    int ativa;

    if ((fp = fopen(filename, "r")) != NULL)
    {
        while (!feof(fp))
        {
            if ((pt = (STATION*)malloc(sizeof(STATION))) != NULL && (putHeadLinkedList(list, pt) != ERROR))
            {
                fscanf(fp, "%[^;];%f;%d;%d\n", pt->nome, &(pt->custo), &ativa, &(pt->liga));
                pt->estado = FALSE;
                if (ativa)
                    pt->estado = TRUE;
            }
            else
            {
                destroyMetroNetwork(list);
                return ERROR;
            }
        }
        fclose(fp);
        return OK;
    }
    else
        return ERROR;
}

STATUS saveMetroLines(LINKED_LIST list, int nline) {
    FILE* fp;
    char nomeArquivo[20];  // Defina o tamanho adequado para o nome do arquivo

    sprintf(nomeArquivo, "line%d_Copia.txt", nline);

    if ((fp = fopen(nomeArquivo, "w")) != NULL) {
        while (list != NULL) {
            fprintf(fp, "%s;%.2f;%d;%d;\n",
                ((STATION*)DATA(list))->nome,
                ((STATION*)DATA(list))->custo,
                ((STATION*)DATA(list))->estado,
                ((STATION*)DATA(list))->liga);
            list = NEXT(list);
        }
        fclose(fp);
        return OK;

    }
    else
        return ERROR;
}

void printMetroLine(LINKED_LIST list)
{
    while (list != NULL)
    {
        printf("%s - %.2f\n", DATA(list)->nome, list->data->custo);
        list = NEXT(list);
    }
}

void destroyMetroNetwork(LINKED_LIST* L)
{

}

int getPosition(LINKED_LIST L, const char* station) {
    int i = 0;
    while (L != NULL && strcmp(L->data->nome, station) != 0){
        L = L->pNext;
        i = i + 1;
    }
    return i;
}

// made by me
float lineCost(LINKED_LIST L){
    
    // user input
    char origin[MAX_CHARS];
    char destination[MAX_CHARS];

    // user input
    printf("Insira o Nome da Estacao de origem: ");
    fflush(stdout); // flush the output buffer
    fgets(origin, MAX_CHARS, stdin);
    origin[strcspn(origin, "\n")] = '\0'; // remove trailing newline character
    
    printf("Insira o Nome da Estacao final: ");
    fflush(stdout); // flush the output buffer
    fgets(destination, MAX_CHARS, stdin);
    destination[strcspn(destination, "\n")] = '\0'; // remove trailing newline character
    
    if (getPosition(L,origin) >= getPosition(L, destination)){
        printf("A estacao de origem e posterior/igual a estacao de destino!\n");
        return -1;
    }

    // loops until the origin station is found
    while (strcasecmp(L->data->nome, origin) != 0){
        L = L->pNext;
    }
    // initialize and start calculating the cost
    float custo = 0;
    while (L != NULL){

        custo += L->data->custo;
        if (strcasecmp(L->data->nome, destination) == 0)
            return custo;
        
        L = L->pNext;
    }
}


// made by me
STATUS addStation(LINKED_LIST*L, char* afterStation){
    // allocate memory for the new node
    LIST_NODE* pt = (LIST_NODE*)malloc(sizeof(LIST_NODE));
    if (pt == NULL) {
        printf("Memory allocation error\n");
        return ERROR;
    }
    pt->data = (STATION*)malloc(sizeof(STATION));
    if (pt->data == NULL) {
        printf("Memory allocation error\n");
        return ERROR;
    }

    // user input
    printf("Insira o Nome da Estacao: ");
    while (getchar() != '\n');
    scanf("%s", pt->data->nome);
    
    printf("Insira o Custo da Estacao: ");
    while (getchar() != '\n');
    scanf("%f", &pt->data->custo);
    
    printf("Insira o Estado da Estacao (1-Ativa, 0-Inativa): ");
    while (getchar() != '\n');
    int estado;
    scanf("%d", &estado);
    if (estado == 1)
        pt->data->estado = TRUE;
    else 
        pt->data->estado = FALSE;


    // loop to find station 
    while (L != NULL) {
        if (strcasecmp((*L)->data->nome, afterStation) == 0) {
            // station is found
            // update the new node's next pointer
            pt->pNext = (*L)->pNext;
            // update the previous node's next pointer
            (*L)->pNext = pt;             
            
            return OK; 
        }
        L = &(*L)->pNext;
    }
    // station is not found
    return ERROR;
}

// made by me
STATUS existStation(LINKED_LIST L, const char* nome)
{
    while (L != NULL){
        if (strcmp(L->data->nome, nome) == 0)
            return OK;
        L = L->pNext;
    }
    return ERROR;
}

// made by me 
STATUS enableStation(LINKED_LIST L, const char* nome)
{
    while (L != NULL){
        if (strcmp(L->data->nome, nome) == 0){
            if (L->data->estado == TRUE)
                L->data->estado = FALSE;
            else
                L->data->estado = TRUE;
            return OK;
        }
        L = L->pNext;
    }
    return ERROR;
}

// made by me
STATUS deleteStation(LINKED_LIST* L, const char* nome){       
    LIST_NODE* current = *L;
    LIST_NODE* prev = NULL;

    // loop to find station 
    while (current != NULL) {
        if (strcmp(current->data->nome, nome) == 0) {
            // station is found

            // station is the head of the list
            if (prev == NULL) {
                // update head of the list
                *L = (*L)->pNext; 
            } else {
                // update the previous node's next pointer
                prev->pNext = current->pNext; 
            }

            // free station memory 
            free(current->data);
            free(current);
            
            return OK; 
        }

        // move to next node
        prev = current;
        current = current->pNext;
    }

    return ERROR;
}

// Source file for LINKED_LIST
//-------------------------------------------------------
// Constructor functions --------------------------------
STATUS newLinkedList(LINKED_LIST* pL)
{
    *pL = NULL;
    return OK;
}

//-------------------------------------------------------
STATUS newListNode(LIST_NODE** pN, STATION* X)
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
    //pTempN->data = X;
    NEXT(pTempN) = NULL;
    return OK;
}
//-------------------------------------------------------
// Destructor functions ---------------------------------
STATUS destroyLinkedList(LINKED_LIST* pL)
{
    STATION* pX = NULL;
    // underflow
    if (emptyLinkedList(*pL))
        return ERROR;
    // if pX = NULL - don't want to use the deleted data
    while (*pL != NULL)
        removeHeadLinkedList(pL, &pX);
    return OK;
}
//-------------------------------------------------------
// Input functions --------------------------------------
STATUS putHeadLinkedList(LINKED_LIST* pL, STATION* X)
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
STATUS removeHeadLinkedList(LINKED_LIST* pL, STATION** pX)
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


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
