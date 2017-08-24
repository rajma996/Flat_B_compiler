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
%token <id> array_size
%token print
%token comma
%token read_token
%token codeblock
%token declblock
%token println
%token exit_command
%token <num> number
%token <id> identifier
%token <id> string
%type <num> line exp term

%%

/* descriptions of expected inputs     corresponding actions (in C) */

program : code_line ;

program : declblock '{' decl_statements '}'  codeblock '{' code_line '}' ; 

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
                  | identifier array_size {printf("setting up arrar %s\n",$2);}
                  ;
 
code_line :      print printexp ';'		{;}
                 | read_token scan_iden ';' {;}
                 | code_line print printexp ';'	{;}
                 | code_line read_token scan_iden ';' {;}
                 ;

scan_iden   :    identifier {printf("scanning var %s\n",$1);}  ;

printexp :      printexp comma final_printexp {;}
                | final_printexp {;}
                ;

final_printexp : identifier {printf("print var %s\n",$1);}
               | string {printf("print string %s\n",$1);}
               ;

%%                     /* C code */

int main (void) {
	/* init symbol table */
	int i;
	for(i=0; i<52; i++) {
		symbols[i] = 0;
	}

	return yyparse ( );
}

void yyerror (char *s) {fprintf (stderr, "%s\n", s);}
