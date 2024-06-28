#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>

// Sctruct definition
typedef struct _data{
    int dia;
    int mes;
    int ano;
}DATA;

typedef struct {
    int numero;
    char nome[50];
    DATA dataNascimento;
}ALUNO;

typedef struct {
    int numero;
    char nome[50];
    DATA* dataNascimento;
}ALUNOP;

typedef struct _pessoa{
    int idade;
    char nome[50];
    struct _pessoa* pai;
}PESSOA;

void main(){
    ALUNO a;
    ALUNO* b;

    // Fill the struct
    a.numero = 12345;
    strcpy(a.nome,"Joao Pereira");
    a.dataNascimento.dia = 20;
    a.dataNascimento.mes = 5;
    a.dataNascimento.ano = 2000;	

    // Print the struct
    printf("\nNome: %s",a.nome);
    printf("\nNumero: %d",a.numero);
    printf("\nData de Nascimento: %d/%d/%d", a.dataNascimento.dia, a.dataNascimento.mes, a.dataNascimento.ano);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Allocates memory for the struct (b was defined with a pointer)
    b = (ALUNO*)malloc(sizeof(ALUNO));

    // Fill the struct
    b->numero = 1236;
    strcpy(b->nome,"Manuel Silva");
    b->dataNascimento.dia = 12;
    b->dataNascimento.mes = 1;
    b->dataNascimento.ano = 1999;

    // Print the struct
    printf("\nNome: %s",b->nome);
    printf("\nNumero: %d",b->numero);
    printf("\nData de Nascimento: %d/%d/%d", b->dataNascimento.dia, b->dataNascimento.mes, b->dataNascimento.ano);

    // Free the memory
    free(b);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ALUNOP x;

    DATA d;
    d.dia = 12;
    d.mes = 10;
    d.ano = 2000;

    x.numero = 1234;
    strcpy(x.nome,"Antonio Silva");

    // Allocates memory for the struct (DATA was defined with a pointer)
    //x.dataNascimento = (DATA*)malloc(sizeof(DATA));
    //x.dataNascimento->dia = 15;
    //x.dataNascimento->mes = 9;
    //x.dataNascimento->ano = 2004;

    // Or we can do it like this (using the d's already defined memory address)
    x.dataNascimento = &d;

    printf("\nNome: %s",x.nome);
    printf("\nNumero: %d",x.numero);
    printf("\nData de Nascimento: %d/%d/%d", x.dataNascimento->dia, x.dataNascimento->mes, x.dataNascimento->ano);

    // Free the memory
    //free(x.dataNascimento);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ALUNOP *y;

    // Allocates memory for the ALUNOP struct and the DATA pointer defined inside it
    y = (ALUNOP*)malloc(sizeof(ALUNOP));
    y->dataNascimento = (DATA*)malloc(sizeof(DATA));

    // Fill the struct with user input
    printf("\nInsira o nome: ");
    fgets(y->nome, 50, stdin); 
    printf("Insira o numero: ");
    scanf("%s", &y->numero);
    printf("Insira a data de nascimento dia: ");
    scanf("%d", &y->dataNascimento->dia);
    printf("Insira a data de nascimento mes: ");
    scanf("%d", &y->dataNascimento->mes);
    printf("Insira a data de nascimento ano: ");
    scanf("%d", &y->dataNascimento->ano);

    // Print the struct
    printf("\nNome: %s",y->nome);
    printf("Numero: %d",y->numero);
    printf("\nData de Nascimento: %d/%d/%d", y->dataNascimento->dia, y->dataNascimento->mes, y->dataNascimento->ano);

    // Free the memory
    free(y->dataNascimento);
    free(y);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    PESSOA r;
    PESSOA *t;

    r.idade = 23;
    strcpy(r.nome,"Joao Silva");
    r.pai = NULL;

    t = (PESSOA*)malloc(sizeof(PESSOA)); 
    t->idade = 45;
    strcpy(t->nome,"Manuel Pereira");
    t->pai = NULL;

    r.pai = t;

    // Print the struct
    printf("\nNome: %s",r.nome);
    printf("\nIdade: %d",r.idade);
    printf("\nNome do Pai: %s",r.pai->nome);
    printf("\nIdade do Pai: %d",r.pai->idade);

    // Free the memory
    free(t);
    // Set the pointer to NULL to avoid memory leaks  
    r.pai = NULL;
}