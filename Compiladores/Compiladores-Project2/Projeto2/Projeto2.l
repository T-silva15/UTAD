/*** Definition section ***/

/*** flex Projeto2.l && gcc lex.yy.c -ll && ./a.out  ***/

%option noyywrap
%{
    #include <stdio.h>
//-----------------------struct----------------------------

    struct Tuple{
        char material[10];
        int quantidade;
    };
//--------------------------variaveis----------------------------
    //estado bateria
    int Estado_Bateria = 100;
    //localizacao
    char arrayLocalizacao[4][50] = {"Posto de carregamento","Posto de manutencao","Armazem","Linha de montagem"};
    int localizacao = 0;
    char Linha_Montagem[10] = "";
    //counter manutencao
    int Vezes_Manutencao = 0;

    int Carga_Total = 0;

        //lista de pecas + quantidade (M,Q) material , quantidade
        //RECOLHE([(A4gt6,300),(cbv45,3),(12345,21)])
    struct Tuple TupleList[100];

    int Posicao_Tupla = 0; //lista vazia


//--------------------funcoes--------------------

    int countOpenParentheses(const char *str) {
        int count = 0;
        for (int i = 0; str[i] != '\0'; i++) {
            if (str[i] == '(') {
                count++;
            }
        }
        return count;
    }

      int countOpenCommas (const char *str) {
        int count = 0;
        for (int i = 0; str[i] != '\0'; i++) {
            if (str[i] == ',') {
                count++;
            }
        }
        return count;
    }
    
    void storeTuples(char* input) {

        char M[50];
        int Q;

        //comecamos com RECOLHE([(A4gt6,300),(cbv45,3),(12345,21)])
        char* string = (char*)malloc(strlen(input)+1);
        strcpy(string , input + 8);
        int parenteses = countOpenParentheses(string);

        //string é [(A4gt6,300),(cbv45,3),(12345,21)])

        char* token = strtok(string,"(");


        for (int i=0 ; i< parenteses ; i++){
            token = strtok(NULL,",");
            strcpy(M,token);
            

            //string é 300),(cbv45,3),(12345,21)])
            token = strtok(NULL,")");
            Q = atoi(token);

            if(Carga_Total + Q > 80){
                printf("Impossivel carregar material %s pois excede a carga maxima de 80\n",M);
                Posicao_Tupla --;
            }
            else{
                //checkar se material ja existe
                int existe = 0;

                for(int y = 0;y<Posicao_Tupla;y++){
                    if(strcmp(TupleList[y].material,M) == 0){
                        existe = 1;
                        TupleList[y].quantidade += Q;
                        Carga_Total += Q;
                        Posicao_Tupla --;
                        break;
                    }
                }
                if(existe == 0){
                    strcpy(TupleList[Posicao_Tupla].material,M);
                    TupleList[Posicao_Tupla].quantidade = Q;
                    Carga_Total += Q;
                }
            }
            
            //string é ,(cbv45,3),(12345,21)])
           
            token = strtok(NULL,"(");
            //recursivo a partir daqui
            Posicao_Tupla ++;
        }
        free(string);
    }

    void removeTuples(char* M,int Q, int PosicaoRemover){
        //ENTREGA(AB50,A4gt6,300)

        //se forem entregues a totalidade de itens
            if(TupleList[PosicaoRemover].quantidade == Q){
                Carga_Total-= Q;

                if (PosicaoRemover == Posicao_Tupla){
                    Posicao_Tupla --;
                }
                else{
                    for(int i = PosicaoRemover ; i<Posicao_Tupla - 1 ; i++){
                        strcpy(TupleList[i].material , TupleList[i+1].material); 
                        TupleList[i].quantidade = TupleList[i+1].quantidade;
                        }
                        Posicao_Tupla--;
                   
                }
            }
            //se apenas for entregue uma parte
            else if(TupleList[PosicaoRemover].quantidade > Q){
                TupleList[PosicaoRemover].quantidade -= Q;
                Carga_Total-= Q;
            }
            else if (TupleList[PosicaoRemover].quantidade < Q){
                printf("Impossivel entregar mais materias do que aqueles contidos no veiculo\n");
            }
    }

    void print_states(){

        printf("Bateria : %i \n", Estado_Bateria);
        printf("Contador Manutencao : %i \n", Vezes_Manutencao);
        printf("Localizacao: %s %s\n", arrayLocalizacao[localizacao],Linha_Montagem);
        printf("Carga Total: %d \n", Carga_Total);

        for (int i = 0; i < Posicao_Tupla; i++) {
            if(i == Posicao_Tupla - 1){
                printf("(%s, %d)",TupleList[i].material, TupleList[i].quantidade);  
            }
            else{
                printf("(%s, %d) ,",TupleList[i].material, TupleList[i].quantidade);
            }
        }   
        printf("\n");
    }

    void deslocar(int input){

        strcpy(Linha_Montagem,""); 
        localizacao = input;
        printf("O veiculo deslocou-se ate: %s %s\n",arrayLocalizacao[input], Linha_Montagem);
    }

    void print_Estado(int array[3]){
        if(array[0]){
            printf("Bateria : %d\n",Estado_Bateria); 
        }
        if(array[1]){
           printf("Tarefas pendentes : 0\n");  
        }
        if(array[2]){
            for (int i = 0; i < Posicao_Tupla; i++) {
            if(i == Posicao_Tupla - 1){
                printf("(%s, %d)",TupleList[i].material, TupleList[i].quantidade);  
            }
            else{
                printf("(%s, %d) ,",TupleList[i].material, TupleList[i].quantidade);
            }
        }   
        printf("\n");

        }

    }

%}

/*** macros ***/

MANUTENCAO  MANUTENCAO\([0-2]\)
CARREGA     CARREGA-BATERIA\([0-2]\)
ENTREGA     ENTREGA\([A-Z]{2}([1-9]|00[1-9]|[1-9][0-9]|0[1-9][0-9]|100),[A-Za-z0-9]{5},[1-9][0-9]*\)
RECOLHE     RECOLHE\(\[(\([A-Za-z0-9]{5},0*[1-9][0-9]*\),)*\([A-Za-z0-9]{5},0*[1-9][0-9]*\)\]\)
ESTADO      ESTADO\(([BMT]|([BT],M|[MT],B|[MB],T)|(T,(M,B|B,M)|M,(T,B|B,T)|B,(T,M|M,T)))\)



%%

{MANUTENCAO}.* {
//deve se deslocar ate a manutencao

    if (localizacao != 1){
         if(Estado_Bateria - 10 - Carga_Total >= 0){ //se bateria for suficiente
            deslocar(1);
            Estado_Bateria = Estado_Bateria - 10 - Carga_Total;   
            Vezes_Manutencao ++;
            if(Vezes_Manutencao == 3){
                printf("Veiculo foi 3 vezes a manutencao, contador sera colocado a 0\n");
                Vezes_Manutencao = 0;
            }
        } 
        else{
            printf("Nao ha bateria suficiente para esta deslocacao");
        }
    }
    else{
        printf("O veiculo ja se encontra na zona de manutencao\n");
    }

    print_states();
}

{CARREGA}.* {
    //deve se deslocar ao posto de carregamento

    if(Estado_Bateria == 100){

        printf("Foi pedido um carregamento com a bateria a 100\n");
    }

    if (localizacao != 0){ 
        if(Estado_Bateria - 10 - Carga_Total >= 0){ //se bateria for suficiente
            deslocar(0);
            Estado_Bateria = 100;   
        } 
        else{
            printf("Nao ha bateria suficiente para esta deslocacao\n");
        }
    }
    else{
        printf("O veiculo ja se encontra na zona de carregamento \n");
    }

    print_states();
}

{ENTREGA}.* {
//deve fazer uma entrega na linha de montagem

        int PosicaoRemover = -1;
        int Q;
        char M[50];
        char L[50];
        char* string = (char*)malloc(strlen(yytext)+1);

        strcpy(string , yytext + 8);
        // string AB50,A4gt6,300)
        
        char* token = strtok(string,",");
        strcpy(L,token);
       
        //A4gt6,300)
        token = strtok(NULL,",");
        strcpy(M,token);
    
        //300)
        token = strtok(NULL,")");
        Q = atoi(token);

        free(string);

        //localizar material

        for (int i = 0; i <Posicao_Tupla; i++){

            if(strcmp(TupleList[i].material,M) == 0){
                PosicaoRemover = i;
            }
        }

        if(PosicaoRemover == -1){
            printf("Material nao existe\n");
        }
        else{
            if (localizacao != 3){ //nao se encontra na linha de montagem
                if(Estado_Bateria - 10 - Carga_Total >= 0){ //se bateria for suficiente
                    deslocar(3);
                    Estado_Bateria = Estado_Bateria - 10 - Carga_Total; 
                    strcpy(Linha_Montagem,L); 
                    printf("entregou\n"); //---------------------------------------------------------debug line
                    removeTuples(M,Q,PosicaoRemover); //fazer uma entrega 
                } 
                else{
                    printf("Nao ha bateria suficiente para esta deslocacao");
                }
            }
            else{ //ja se encontra na linha de montagem
                if(strcmp(Linha_Montagem,L) == 0){
                    printf("Ja se encontra na linha de montagem %s\n",Linha_Montagem);
                    removeTuples(M,Q,PosicaoRemover); //fazer uma entrega
                }
                else{
                    if(Estado_Bateria - 5 - Carga_Total >= 0){ //se bateria for suficiente
                        strcpy(Linha_Montagem,L);
                        printf("Ja se encontra numa linha de montagem, moveu-se para %s\n",Linha_Montagem);
                        Estado_Bateria = Estado_Bateria - 5 - Carga_Total; 
                        removeTuples(M,Q,PosicaoRemover); //fazer uma entrega 
                    } 
                    else{
                        printf("Nao ha bateria suficiente para esta deslocacao");
                    }

                }
            }
        }

    print_states();
}

{RECOLHE}.* {
//deve se deslocar ao armazem para recolher itens
//RECOLHE([(A4gt6,300),(cbv45,3),(12345,21)])


    if (localizacao != 2){
        if(Estado_Bateria - 10 - Carga_Total >= 0){ //se bateria for suficiente
            deslocar(2);
            Estado_Bateria = Estado_Bateria - 10 - Carga_Total;  
            storeTuples(yytext); //recolhe se estiver no armazem
        } 
        else{
            printf("Nao ha bateria suficiente para esta deslocacao");
        }
    }
    else{
        printf("O veiculo ja se encontra no armazem\n");
        storeTuples(yytext); //recolhe se estiver no armazem
    }

    print_states();
}

{ESTADO}.* {
//Indica o estado atual do veiculo onde B - Bateria  M- Lista de materiais t - tarefas pendentes
    //ESTADO(B,M,T) 3
    //ESTADO(B) 1
    //ESTADO(B,M) 2
    char Caracteres[3];
    int array[3] = {0,0,0}; //bateria,tarefas,materiais e quantidade
    char* token;
    char* string = (char*)malloc(strlen(yytext)+1);
    strcpy(string , yytext + 7);
    int comas = countOpenCommas(string);


    if(comas == 0){
        token = strtok(string,")");
        Caracteres[0] = *token; 

        for(int i=0;i<1;i++){
            if(Caracteres[i] == 'B'){
                array[0] = 1;
            }
            if(Caracteres[i] == 'T'){
                array[1] = 1;
            }
            if(Caracteres[i] == 'M'){
                array[2] = 1;
            }
        }   
    }
    else if(comas == 1){
        token = strtok(string,",");
        Caracteres[0] = *token;
        token = strtok(NULL,")");
        Caracteres[1] = *token;

        for(int i=0;i<2;i++){
            if(Caracteres[i] == 'B'){
                array[0] = 1;
            }
            if(Caracteres[i] == 'T'){
                array[1] = 1;
            }
            if(Caracteres[i] == 'M'){
                array[2] = 1;
            }
        }  
    }
    else if(comas == 2){
        for(int i = 0;i<3;i++){
            array[i] = 1;
        }
    }

    print_Estado(array);


}


\n {printf("\n");}


.* {printf("Comando nao reconhecido\n");}

%%

/*** C Code section ***/

int main(void)
{
    yylex();
    printf("---Analise terminada---\n");
    print_states();
    return 0;
}