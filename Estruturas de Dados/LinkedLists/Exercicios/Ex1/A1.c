#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>

// boolean Definition
typedef enum boolean{
    false=0,
    true=1,
}Boolean;

// book Structure
typedef struct Book{
    char title[50];
    char author[50];
    Boolean state;
}Book;

// book List Structure
typedef struct Node1{
    Book book;
    struct Node1* next;
}BookList;

// member Structure	
typedef struct member{
    char name[50];
    int id;
    int requested;
}Member;

// member List Structure
typedef struct Node2{
    Member member;
    struct Node2* next;
}MemberList;

// genmemberates a random name
char* generateRandomName(int length) {
    // character set for the random name
    char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    char *randomName;

    // allocate memory for the random name
    if (randomName = (char*)malloc((length + 1) * sizeof(char)) == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // seed the random number generator
    srand((unsigned int)time(NULL));

    // generate random name
    for (int i = 0; i < length; i++) {
        randomName[i] = charset[rand() % (sizeof(charset) - 1)];
    }

    // add null terminator to the end of the string
    randomName[length] = '\0'; 
    return randomName;
}

// save the list of books in the file
void saveFileBook(BookList* List){
    // generates random file name to avoid overwriting
    char* file = strcat("livros", generateRandomName);
    file = strcat(file,".txt");
    
    if(file == NULL){
        printf("Erro ao abrir o ficheiro\n");
        return;
    }
    // Write the list to the file
    while (List != NULL){
        fprintf(file, "%s;%s;%d\n", List->book.author, List->book.title, List->book.state);
        List = List->next;
    }
    // Close the file
    fclose(file);
}

// save the list of members in the file
void saveFileMember(MemberList* List){
    // generates random file name to avoid overwriting
    char* file = strcat("socios", generateRandomName);
    file = strcat(file,".txt");
    
    if(file == NULL){
        printf("Erro ao abrir o ficheiro\n");
        return;
    }
    // Write the list to the file
    while (List != NULL){
        fprintf(file, "%s;%s;%d\n", List->member.id, List->member.name, List->member.requested);
        List = List->next;
    }
    // Close the file
    fclose(file);
}

// read the file and store the data in the list
void readFileMember(MemberList* List){
    FILE* file = fopen("livros.txt","r");
    if(file == NULL){
        printf("Erro ao abrir o ficheiro\n");
        return;
    }
    // Read the file 
    while (fscanf(file, "%[^;];%[^;];%d\n", List->member.id, List->member.name, List->member.requested) == 3) {           
        // Check if the end of the file was reached
        if (feof(file)) break;
        // Allocate memory for the next node
        List->next = (MemberList*)malloc(sizeof(MemberList));
        // Attach the new node to the list and move to the next node
        // Move to the next node
        List = List->next;
    };
    // Close the file
    fclose(file);
}

// read the file and store the data in the list
void readFileBook(BookList* List){
    FILE* file = fopen("livros.txt","r");
    if(file == NULL){
        printf("Erro ao abrir o ficheiro\n");
        return;
    }
    // Read the file 
    while (fscanf(file, "%[^;];%[^;];%d\n", List->book.author, List->book.title, &List->book.state) == 3) {           
        // Check if the end of the file was reached
        if (feof(file)) break;
        // Allocate memory for the next node
        List->next = (BookList*)malloc(sizeof(BookList));
        // Attach the new node to the list and move to the next node
        // Move to the next node
        List = List->next;
    };
    // Close the file
    fclose(file);
}

// prints list of members
void printListMember(MemberList* List){
    if (List == NULL){
        printf("Lista vazia\n");
        return;
    }

    while (List != NULL){
        fprintf("ID de Socio: %s\n", List->member.id);
        fprintf("Nome: %s\n",List->member.name);
        fprintf("Livro Requesitado: %s\n\n", List->member.requested == -1 ? "Sim" : "Não");
        
        List = List->next;
    }
}

// print the list of books
void printListBook(BookList* List){
    if (List == NULL){
        printf("Lista vazia\n");
        return;
    }

    while(List != NULL){
        printf("Autor do Livro: %s\n",List->book.author);
        printf("Titulo do Livro: %s\n",List->book.title);
        printf("Estado do Livro: %s\n\n",List->book.state == 0 ? "Disponivel" : "Emprestado");

        List = List->next;
    }
}

// deletes book by title
void deleteListBook(BookList** List, char* title){
    BookList* current = *List;
    BookList* previous = NULL;
    // Loops until book is found
    while(strcmp(current->book.title,title) != 0){
        previous = current;
        current = current->next;
    }
    // when book is not found
    if (current == NULL) {
        printf("Livro com o titulo '%s' nao encontrado.\n", title);
        return;
    }
    // If the node to delete is the first node
    if (previous == NULL) {
        *List = current->next;
    } else {    
        // redirects node to node after the deleted node
        previous->next = current->next;
    } 
    // Frees the memory of the deleted node
    free(current);
    saveFileBook(*List);
}

// deletes member by id
void deleteMember(MemberList** List, int id){
    MemberList* current = *List;
    MemberList* previous = NULL;

    // loops until member is found
    while (current->member.id != id){
        previous = current;
        current = current->next;
    }
    // member not found
    if (current == NULL) {
        printf("Socio com id '%d' nao encontrado.\n", id);
        return;
    }
    // If the node to delete is the first node
    if (previous == NULL) {
        *List = current->next;
    } else {    
        // redirects node to node after the deleted node
        previous->next = current->next;
    }
    // Frees the memory of the deleted node
    free(current);
    saveFileMember(*List);
}

// returns book state by author and title
int searchStateBook(BookList* List, char* author, char* title){
    // Loops through List until book with that author and name are found
    while (strcmp(List->book.author, author) != 0 && strcmp(List->book.title, title) != 0){
        List = List->next;
    }
    // If book not found print message and return -1
    if (List->next == NULL && strcmp(List->book.author, author) != 0 || strcmp(List->book.title, title) != 0){
        return -1;
    }
    // If book is found return state of book
    else{
        return List->book.state;
    }
}

// adds book to beginning of list
void addBook(BookList** List, Book book){
    BookList* new;

    // allocate memory for the new node
    if ((new = (BookList*)malloc(sizeof(BookList))) == NULL) {
        printf("\nLinkedList node: memory allocation error");
        return;
    }
    // store given book in new node
    new->book = book;
    // point new node to the head of the current list
    new->next = *List;
    // point the head of the list to the new node
    *List = new;
    return;
}

// adds member to beginning of list
void addMember(MemberList** List, Member member){
    MemberList* new;

    // allocate memory for the new node
    if (new = (MemberList*)malloc(sizeof(MemberList)) == NULL){
        printf("\nLinkedList node: memory allocation error");
        return;
    }
    // store given member in new node
    new->member = member;
    // point new node to the head of the current list
    new->next = *List;
    // point the head of the list to the new node
    *List = new;
}

// main function
int main(){
    BookList* List = (BookList*)malloc(sizeof(BookList));
    readFileBook(List);
    printListBook(List);
/*    
    printf("//////////////////////////////////////\n\n");
    deleteListBook(&List, "Caes Pretos");
    printListBook(List);
    int res = searchStateBook(List, "Jose Saramago", "O Ano da Morte de Ricardo Reis");

     switch (res)
    {
    case 0:
        printf("Livro Disponivel!");
        break;
    case 1:
        printf("Livro Emprestado!");
        break;
    case -1:
        printf("Livro nao encontrado!");
        break;
    default:
        printf("Livro nao encontrado!");
        break;
    } 
    printf("//////////////////////////////////////\n\n\n\n\n");
    addBook(&List, (Book){"1984", "George Orwell", false});
    printListBook(List); 
*/
    return 1;

}