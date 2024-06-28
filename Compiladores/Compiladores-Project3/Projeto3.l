/*** Definition section ***/

/*** flex Projeto2.l && gcc lex.yy.c -ll && ./a.out  ***/

%option noyywrap

%{ 

    #include "Parser.tab.h"
    #include "string.h"
    #include <stdlib.h>
    #include <stdio.h>
%}

/*** macros ***/


L       ([A-Z]{2}([1-9]|00[1-9]|[1-9][0-9]|0[1-9][0-9]|100))
M       [A-Za-z0-9]{5}
Q       0|[1-9][0-9]*
I       ([BMT]|([BT],M|[MT],B|[MB],T)|(T,(M,B|B,M)|M,(T,B|B,T)|B,(T,M|M,T)))
LISTA   (\([A-Za-z0-9]{5},0*[1-9][0-9]*\),)*\([A-Za-z0-9]{5},0*[1-9][0-9]*\)


%%
INICIO-DAS-INSTRUCOES   {return START;}

FINAL-DAS-INSTRUCOES    {return END;}

"MANUTENCAO"            {yylval.mystring = "MANUTENCAO" ;return MANUTENCAO;}

"CARREGA-BATERIA"       {yylval.mystring = "CARREGA-BATERIA"; return CARREGA;}

"ENTREGA"               {yylval.mystring = "ENTREGA";return ENTREGA;}

"RECOLHE"              {yylval.mystring = "RECOLHE";return RECOLHE;}

"ESTADO"                {yylval.mystring = "ESTADO";return ESTADO;}

"INIT-ESTADO"            {yylval.mystring = "INIT-ESTADO" ;return INITESTADO;}

"Posto de carregamento"             {yylval.numero = 0 ;return LOCALIZACAO;}
"Posto de manutencao"               {yylval.numero = 1 ;return LOCALIZACAO;}
"Armazem"                           {yylval.numero = 2 ;return LOCALIZACAO;}
"Linha de montagem"                 {yylval.numero = 3 ;return LOCALIZACAO;}

{Q}                     {yylval.numero = atoi(yytext);return Q;}             // 0 - infinito
{L}                     {yylval.mystring = strdup(yytext);return L;}
{M}                     {yylval.mystring = strdup(yytext);return M;}
{I}                     {yylval.mystring = strdup(yytext) ;return I;}
{LISTA}                 {yylval.mystring = strdup(yytext);return LISTA;}


";"                     {yylval.caracter = ';' ;return PONTOEVIRGULA;}

"{"                     {yylval.caracter = '{' ;return CHAVETAE;}    
"}"                     {yylval.caracter = '}' ;return CHAVETAD;}   

","                     {yylval.caracter = ',' ;return VIRGULA;}

"("                     {yylval.caracter = '(' ;return PARENTE;}    
")"                     {yylval.caracter = ')' ;return PARENTD;} 

"["                     {yylval.caracter = '[' ;return RETOE;}    
"]"                     {yylval.caracter = ']' ;return RETOD;} 



[ \t\n]                 {}

.                       {}

%%
