%{
#include<bits/stdc++.h>
#include"ASTDefinitions.h"
  
using namespace std;
extern "C" int yylex();
extern union node yylval;

 int errors;
 void yyerror(char *);

 
%}

%token int_datatype
%token <id> array_num_index
%token <id> array_identi_index
%token <id> label
%token if_token
%token for_token
%token print
%token comma
%token read_token
%token codeblock
%token declblock
%token println
%token goto_token
%token colon
%token lcb
%token rcb
%token lrb
%token rrb
%token pluss
%token minuss
%token mul
%token lt
%token lte
%token gt
%token gte
%token eq
%token eqeq
%token neq
%token andand
%token  oror
%token mod
%token divi
%token rsb
%token lsb

%token exit_command
%token <num> number
%token <id> identifier
%token <id> strings

%left eqeq neq
%left andand oror
%left lt gt lte gte
%left pluss minuss
%left mul divi

%type <variables> variables
%type <final_printexp> final_printexp
%type <printexp> printexp
%type <term> term
%type <exp> exp
%type <assignment> assignment
%type <goto_statement> goto_statement
%type <for_statement> for_statement
%type <code_line> code_line
%type <readexp> readexp

%start program;

%%

/* descriptions of expected inputs corresponding actions (in C) */


program : declblock decl_statements codeblock code_statements ;

decl_statements : lcb rcb  {;}
                | lcb decl_statement rcb {;}

/* declaration statements */
decl_statement : int_datatype literals ';' {;}
                 | decl_statement int_datatype literals ';' {;}
                 ;

code_statements : lcb rcb  {;}
                | lcb code_line rcb {;}

/* comma separated values */
literals : literals comma final_identifier {;}
           | final_identifier {;} 
           ;

/* the final identifier array or simple variable */
final_identifier : identifier {printf("setting up var %s\n",$1);}
                  | identifier  lsb  number rsb {printf("setting up arrar %d\n",$3);}                  ;

/* all possible code lines : print, read, if, for, assignment,goto */
code_line :      goto_statement ';'                   {$$=$1;}
                 | for_statement                      {$$=$1;}
                 | if_statement                       {;}
                 | assignment ';'                     {$$=$1;}
                 | print printexp ';'		      {$$=$2;}
                 | read_token readexp ';'             {$$=$2;}
                 | label colon                        {;}
                 | code_line print printexp ';'	      {;}
                 | code_line read_token readexp ';'   {;}
                 | code_line assignment ';'           {;}
                 | code_line if_statement             {;}
                 | code_line for_statement            {;}
                 | code_line goto_statement ';'       {;}
                 | code_line label colon              {;}
                 ;


if_statement : if_token lrb exp rrb lcb code_line rcb {printf("if statement");} ;

for_statement : for_token identifier eq number comma number lcb code_line rcb {$$ = new ASTfor_statement($2,$4,$6) ;} ;

goto_statement : goto_token label if_token exp { $$ = new ASTgoto_statement($2,$4);}
            | goto_token label { $$ = new ASTgoto_statement($2,NULL);} ;

assignment : variables eq exp  { $$ = new ASTassignment($1,$3);}
           ;

variables : identifier {$$ = new ASTvariables("normal","none",$1,-1,"none"); }
            | identifier lsb number rsb {$$ = new ASTvariables("array","integer",$1,$3,"none");}; 
            | identifier lsb identifier rsb {$$ = new ASTvariables("array","identifier",$1,-1,$3) ;}



exp     :  exp pluss exp {;}
           | exp minuss exp {$$ = new ASTexp("nonterminal",$1,$3,"minuss",NULL) ;}
           | exp mul exp {$$ = new ASTexp("nonterminal",$1,$3,"mul",NULL);}
           | exp divi exp {$$ = new ASTexp("nonterminal",$1,$3,"divi",NULL);}
           | exp lt exp {$$ = new ASTexp("nonterminal",$1,$3,"lt",NULL);}
           | exp gt exp {$$ = new ASTexp("nonterminal",$1,$3,"gt",NULL);}
           | exp lte exp {$$ = new ASTexp("nonterminal",$1,$3,"lte",NULL);}
           | exp gte exp {$$ = new ASTexp("nonterminal",$1,$3,"gte",NULL);}
           | exp oror exp {$$ = new ASTexp("nonterminal",$1,$3,"oror",NULL);}
           | exp andand exp {$$ = new ASTexp("nonterminal",$1,$3,"andand",NULL);}
           | exp eqeq exp {$$ = new ASTexp("nonterminal",$1,$3,"eqeq",NULL);}
           | exp neq exp { $$ = new ASTexp("nonterminal",$1,$3,"neq",NULL);}
           | lrb exp rrb { $$ = $2;} 
           | term { $$ = new ASTexp("term",NULL,NULL,"NULL",$1) ;}
           ;

term    : number { $$ = new ASTterm($1,NULL,"number")  ;}
         | variables { $$ = new ASTterm(-1,$1,"variable") ;}
;

/* print expression after print key word,comma separated identifiers or strings  */

printexp :      printexp comma final_printexp { $$->push_back($3);  }
                | final_printexp { $$ = new ASTprintexp($1); }
                ;

final_printexp : strings { $$=new ASTfinal_printexp($1,NULL); printf("print string %s\n",$1);} 
| variables { $$ = new ASTfinal_printexp("none",$1); }
               ;

readexp :      readexp comma variables { $$->push_back($3); }
                | variables { $$ = new ASTreadexp($1); }
                ;


%%       /* C code */

int main (void)
{
/* init symbol table */
  errors = 0;
  return yyparse ();
  
}

void yyerror (char *s) {fprintf (stderr, "%s\n", s);}
