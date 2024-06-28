#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NAME 20
#define STAGES 15

typedef struct _PLAYER
{
	char name[MAX_NAME];
	int sets;
}PLAYER;

typedef struct _BTREE_NODE
{
	PLAYER* pData;
	struct _BTREE_NODE* pL;
	struct _BTREE_NODE* pR;
} BTREE_NODE;


typedef BTREE_NODE* BTREE;
typedef enum _BOOLEAN { FALSE = 0, TRUE = 1 } BOOLEAN;
typedef enum _STATUS { ERROR = 0, OK = 1 } STATUS;

#define DATA(node) ((node)->pData)
#define LEFT(node) ((node)->pL)
#define RIGHT(node) ((node)->pR)

BTREE_NODE* NewBtreeNode(PLAYER* data);
BTREE_NODE* InitNode(PLAYER*, BTREE_NODE*, BTREE_NODE*);
BTREE_NODE* CreateBtree(PLAYER**, int, int);
STATUS ReadPlayersFromFile(PLAYER**, char*);
BOOLEAN BtreeLeaf(BTREE_NODE* /*or BTREE*/ node);
int CountLeafs(BTREE);

// made by me
void PrintLeafs(BTREE);
int TotalSets(BTREE);
void PrintGame(BTREE_NODE* /*BTREE*/);
void PrintAllGames(BTREE);
int CountNodes(BTREE);
int TotalGames(BTREE);
int PlayerWonSets(BTREE, char*);
int PlayerSetsPlayed(BTREE, char*);
void PrintPlayerGames(BTREE, char*);
int TreeHeight(BTREE);
BOOLEAN ChangePlayerName(BTREE, char*, char*);
void BtreeFree(BTREE*);

int main()
{
	BTREE Btree;

	PLAYER* players[STAGES];
	char file_name[MAX_NAME];
	char nome[MAX_NAME];

	if (ReadPlayersFromFile(players, "torneio.txt"))
	{
		Btree = CreateBtree(players, 0, STAGES);
		// printf("\n\nNumero de participantes: %d\n", CountLeafs(Btree));
		// printf("\n\nLista de participantes: ");
		// PrintLeafs(Btree);
		// printf("\n\nTotal de sets: %d", TotalSets(Btree));
		// printf("\n\nJogo da final: ");
		// PrintGame(Btree);
		// printf("\n\nNumero de eliminatorias: %d", TotalGames(Btree));
		// printf("\nLista de jogos: ");
		// PrintAllGames(Btree);
		//printf("\nSets ganhos do player1 = %d", PlayerWonSets(Btree,"Player1"));
		//printf("\nAltura da arvore = %d", TreeHeight(Btree));
		//printf("\nSets jogados pelo player1 = %d", PlayerSetsPlayed(Btree,"Player1"));
		//PrintAllGames(Btree);
		// if (ChangePlayerName(Btree,"Player1","teste")){
		// 	printf("\nNome alterado com sucesso!");
		// }
		// PrintPlayerGames(Btree,"teste");
		PrintPlayerGames(Btree,"Player2");	
		BtreeFree(&Btree);
		PrintPlayerGames(Btree,"Player2");
	}
	else
		printf("ERRO na leitura do ficheiro\n");

	return 0;
}

BTREE_NODE* NewBtreeNode(PLAYER* data)
{
	BTREE_NODE* tmp_pt;

	if ((tmp_pt = (BTREE_NODE*)malloc(sizeof(BTREE_NODE))) != NULL)
	{
		DATA(tmp_pt) = data;
		LEFT(tmp_pt) = RIGHT(tmp_pt) = NULL;
	}
	return tmp_pt;
}

BTREE_NODE* InitNode(PLAYER* ptr_data, BTREE_NODE* node1, BTREE_NODE* node2)
{
	BTREE_NODE* tmp_pt = NULL;

	// if (tmp_pt = (BTREE_NODE*)malloc(sizeof(BTREE_NODE)) != NULL)
	// {
	// 	DATA(tmp_pt) = ptr_data;
	// 	LEFT(tmp_pt) = node1;
	// 	RIGHT(tmp_pt) = node2;
	// }
	tmp_pt = NewBtreeNode(ptr_data);
	LEFT(tmp_pt) = node1;
	RIGHT(tmp_pt) = node2;
	return(tmp_pt);
}

BTREE_NODE* CreateBtree(PLAYER** v, int i, int size)
{
	if (i >= size)
		return(NULL);
	else
		return(InitNode(*(v + i), CreateBtree(v, 2 * i + 1, size), CreateBtree(v, 2 * i + 2, size)));
}

STATUS ReadPlayersFromFile(PLAYER** players, char* file_name)
{
	FILE* fp;
	int i = 0;

	PLAYER* ptr_data;

	if ((fp = fopen(file_name, "r")) != NULL)
	{
		while (!feof(fp))
		{
			if ((ptr_data = (PLAYER*)malloc(sizeof(PLAYER))) != NULL)
			{
				fscanf(fp, "%[^;];", ptr_data->name);
				fscanf(fp, "%d\n", &ptr_data->sets);
				players[i] = ptr_data;
				i++;
			}
			else
			{
				for (int j = i; j >= 0; j--)
					free(players[j]);
				return(ERROR);
			}
		}
		fclose(fp);
		return(OK);
	}
	else
		return(ERROR);
}

BOOLEAN BtreeLeaf(BTREE_NODE* btree)
{
	return ((LEFT(btree) == NULL) && (RIGHT(btree) == NULL)) ? TRUE : FALSE;
}

int CountLeafs(BTREE btree) {
	if (BtreeLeaf(btree))
		return 1;
	return CountLeafs(LEFT(btree)) + CountLeafs(RIGHT(btree));
}


// made by me
void PrintLeafs(BTREE btree)
{
	// if node is leaf print the name
	if (BtreeLeaf(btree)){
		printf("\n%s",DATA(btree)->name);
	}
	// if node is not leaf go to the left and right nodes
	else {
		PrintLeafs(LEFT(btree));
		PrintLeafs(RIGHT(btree)); 
	}
}

int TotalSets(BTREE btree){
	// if node exists return the sets of that node plus the sets of the left and right nodes
	if (btree != NULL){
		return ((DATA(btree)->sets) + TotalSets(LEFT(btree)) + TotalSets(RIGHT(btree)));
	}
}

void PrintGame(BTREE_NODE* node /* BTREE btree*/ ){
	if (BtreeLeaf(node) || node == NULL) {
		printf("\nJogo nao existe!");
		return;
	}
	printf("\nJogadores: %s vs %s",DATA(LEFT(node))->name,DATA(RIGHT(node))->name);
	printf("\n      	   Sets: %d | %d",DATA(LEFT(node))->sets,DATA(RIGHT(node))->sets);
	DATA(LEFT(node))->sets > DATA(RIGHT(node))->sets ? printf("\nVencedor: %s",DATA(LEFT(node))->name) : printf("\nVencedor: %s",DATA(RIGHT(node))->name);
}

void PrintAllGames(BTREE btree){
		if (BtreeLeaf(btree) || btree == NULL)
			return;
		PrintAllGames(LEFT(btree));
		PrintAllGames(RIGHT(btree));
		PrintGame(btree);
}

int CountNodes(BTREE btree){
	if (BtreeLeaf(btree)){
		return 1;
	}
	else {
		return 1 + CountNodes(LEFT(btree)) + CountNodes(RIGHT(btree));
	}
}

int TotalGames(BTREE btree){
	return (CountNodes(btree) - 1)/2;
}

int PlayerWonSets(BTREE btree, char* name){
	int sets = 0;
	if (btree != NULL){
		// if player is found add sets
		if (strcmp(DATA(btree)->name,name) == 0){
			sets += DATA(btree)->sets;
		}
		// regardless of if the player was found check the left and right nodes
		sets += PlayerWonSets(LEFT(btree),name) + PlayerWonSets(RIGHT(btree),name);
	}
	return sets;
}

int PlayerSetsPlayed(BTREE btree, char* name){
	int sets = 0;
	if (btree != NULL && !BtreeLeaf(btree)) {
		if (strcmp(DATA(LEFT(btree))->name,name) == 0 || strcmp(DATA(RIGHT(btree))->name,name) == 0){
			sets += DATA(LEFT(btree))->sets + DATA(RIGHT(btree))->sets;
		}
		sets += PlayerSetsPlayed(LEFT(btree),name);
		sets += PlayerSetsPlayed(RIGHT(btree),name);
	}
	return sets;
}

void PrintPlayerGames(BTREE btree, char* name){
	if (btree != NULL && !BtreeLeaf(btree)){
		if (strcmp(DATA(LEFT(btree))->name,name) == 0 || strcmp(DATA(RIGHT(btree))->name,name) == 0){
			PrintGame(btree);
		}
		PrintPlayerGames(LEFT(btree),name);
		PrintPlayerGames(RIGHT(btree),name);
	}
}

int TreeHeight(BTREE btree){	
	int total = 0, sizeleft = 0, sizeright = 0;

	if (btree == NULL)
		return 0;
	else {
		sizeleft = TreeHeight(LEFT(btree));
		sizeright = TreeHeight(RIGHT(btree));
		if (sizeleft > sizeright)
			total = sizeleft + 1;
		else
			total = sizeright + 1;
	}	
}

BOOLEAN ChangePlayerName(BTREE btree, char* oldname, char* newname){
	BOOLEAN find = FALSE;
	if (btree != NULL){
		if (strcmp(DATA(btree)->name,oldname) == 0){
			strcpy(DATA(btree)->name,newname);
			find = TRUE;
		}
		find = ChangePlayerName(LEFT(btree),oldname,newname) || find;
		find = ChangePlayerName(RIGHT(btree),oldname,newname) || find;	
	}
	return find;
}

void BtreeFree(BTREE* btree){
	if (btree != NULL){
		BtreeFree(&(LEFT(*btree)));
		BtreeFree(&(RIGHT(*btree)));

		free(DATA(*btree));
		free(*btree);
		*btree = NULL;
	} 
}