%{
void yyerror (char *s);
#include <stdio.h>     /* C declarations used in actions */
#include <stdlib.h>
 
int symbols[52];
int symbolVal(char symbol);
void updateSymbolVal(char symbol, int val);
%}

%union {int num; char* id;}         /* Yacc definitions */

%start program;

%token int_datatype
%token <id> array_num_index
%token <id> array_identi_index 
%token print
%token comma
%token read_token
%token codeblock
%token declblock
%token println
%token lcb
%token rcb
%token lrb
%token rrb
%token plus
%token minus
%token mul
%token lt
%token lte
%token gt
%token gte
%token eq
%token eqeq
%token neq
%token and
%token  or
%token mod
%token divi

%token exit_command
%token <num> number
%token <id> identifier
%token <id> string
%type <num> term

%left eqeq neq
%left and or
%left lt gt lte gte
%left plus minus
%left mul divi


%%

/* descriptions of expected inputs     corresponding actions (in C) */

program : code_line ;

program : declblock lcb decl_statements rcb  codeblock lcb code_line rcb ; 

/* declaration statements */
decl_statements : int_datatype literals ';' {;}
                 | decl_statements int_datatype literals ';' {;}
                 ;

/* comma separated values */
literals : literals comma final_identifier {;}
           | final_identifier {;} 
           ;

/* the final identifier array or simple variable */
final_identifier : identifier {printf("setting up var %s\n",$1);}
                  | identifier array_num_index {printf("setting up arrar %s\n",$2);}
                  ;

/* all possible code lines : print, read */
code_line :      assignment ';'                       {;}
                 | print printexp ';'		      {;}
                 | read_token scan_iden ';'           {;}
                 | code_line print printexp ';'	      {;}
                 | code_line read_token scan_iden ';' {;}
                 | code_line assignment ';'           {;}
                 ;

assignment : assignment_lhs eq exp  {;}
           ;

assignment_lhs : identifier | identifier array_num_index | identifier array_identi_index {;}


exp     :  exp plus exp {;}
           | exp minus exp {;}
           | exp mul exp {;}
           | exp divi exp {;}
           | exp lt exp {;}
           | exp gt exp {;}
           | exp lte exp {;}
           | exp gte exp {;}
           | exp or exp {;}
           | exp and exp {;}
           | exp eqeq exp {;}
           | exp neq exp {;}
           | lrb exp rrb {;} 
           | term {;}
           ;

term    : identifier {;}
        | number {;}
        | identifier array_num_index {;}
        | identifier array_identi_index {;}
        ;

scan_iden   :    identifier {printf("scanning var %s\n",$1);} ;

/* print expression after print key word,comma separated identifiers or strings  */
printexp :      printexp comma final_printexp {;}
                | final_printexp {;}
                ;

/*string or identifier as component of print statement */
final_printexp : identifier {printf("print var %s\n",$1);}
               | string {printf("print string %s\n",$1);}
               | identifier array_num_index {;}
               | identifier array_identi_index {;}
               ;

%%       /* C code */

int main (void) {
	/* init symbol table */
	int i;
	for(i=0; i<52; i++) {
		symbols[i] = 0;
	}

	return yyparse ( );
}

void yyerror (char *s) {fprintf (stderr, "%s\n", s);}
