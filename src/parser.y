%{
#include<bits/stdc++.h>
#include"Intrepretor.cpp"
  
using namespace std;

extern "C" FILE* yyin;
extern "C" int yylex();
extern union node yylval;

int errors;
void yyerror(char *);
 
class ASTprogram *start = NULL;
 
%}

%token int_datatype
%token <id> array_num_index
%token <id> array_identi_index
%token <id> label
%token if_token
%token else_token
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
%type <if_statement> if_statement
%type <code_statements> code_statements
%type <literals> literals
%type <decl_statement> decl_statement
%type <decl_statements> decl_statements
%type <program> program
%type <code_lines> code_lines

%type <assignment> withoutlabelassignment
%type <assignment> withlableassignment
%type <printexp> withoutlabelprintexp
%type <printexp> withlabelprintexp
%type <readexp> withlabelreadexp
%type <readexp> withoutlabelreadexp
%type <if_statement> withoutlabelif_statement
%type <if_statement> withlabelif_statement
%type <for_statement> withoutlabelfor_statement
%type <for_statement> withlabelfor_statement
%type <printexp>  withlabelprintlnexp
%type <printexp> withoutlabelprintlnexp

%start program;
%%

/* descriptions of expected inputs corresponding actions (in C) */

program : declblock decl_statements codeblock code_statements
{
  $$ = new ASTprogram($2,$4);
  start = $$;
};

decl_statements : lcb decl_statement rcb
                { $$ = new ASTdecl_statements($2);  }


/* declaration statements */
decl_statement : int_datatype literals ';'
{
  $$ = new ASTdecl_statement($2);
}
| decl_statement int_datatype literals ';'
{
  $$->push_back($3);
};

code_statements : lcb rcb  {$$=new ASTcode_statements(NULL);}
                | lcb code_lines rcb {$$ = new ASTcode_statements($2);}
                
/* comma separated values */
literals : literals comma variables {$$->push_back($3); }
           | variables {$$ = new ASTliterals($1); }
           ;

code_lines : code_lines code_line { $1->push_back($2); $$=$1;}
           | code_line {$$ = new  vector<ASTcode_line*>(1,$1); }
;


/* all possible code lines : print, read, if, for, assignment,goto */
code_line :        goto_statement ';'                 {$$=$1;}
                 | withoutlabelfor_statement          {$$=$1;}
                 | withlabelfor_statement             {$$=$1;}
                 | withoutlabelif_statement           {$$=$1;}
                 | withlabelif_statement              {$$=$1;}
                 | withoutlabelassignment ';'         {$$=$1;}
                 | withoutlabelprintexp ';'           {$$=$1;}
                 | withlabelprintexp ';'              {$$=$1;}
                 | withoutlabelreadexp ';'            {$$=$1;}
                 | withlabelreadexp ';'               {$$=$1;}
                 | withlableassignment ';'            {$$=$1;}
                 | withoutlabelprintlnexp ';'            {$$=$1;}
                 | withlabelprintlnexp ';'               {$$=$1;}
                 ;




withoutlabelfor_statement : for_statement              {$$=$1;};

withlabelfor_statement : label colon for_statement     {$$=$3; $$->addlabel($1);};

withlabelif_statement : label colon if_token lrb exp rrb code_statements  {$$ = new ASTif_statement($5,$7,NULL); $$->addlabel($1); } ;
| label colon if_token lrb exp rrb code_statements else_token lrb code_statements rrb { $$ = new ASTif_statement($5,$7,$10); };

withoutlabelif_statement : if_token lrb exp rrb  code_statements  {$$ = new ASTif_statement($3,$5,NULL); } ;
| if_token lrb exp rrb code_statements else_token code_statements {$$ = new ASTif_statement($3,$5,$7); };

withoutlabelreadexp : read_token readexp              {$$=$2;};

withlabelreadexp : label colon read_token readexp     {$4->addlabel($1); $$=$4;};

withoutlabelassignment : variables eq exp {$$ = new ASTassignment($1,$3,"NULL");};

withlableassignment : label colon variables eq exp {cout<<$1<<' '<<' '<<$3<<endl; $$=new ASTassignment($3,$5,$1);};

withoutlabelprintexp : print printexp  {$$=$2;};

withlabelprintexp : label colon print printexp  {$4->addlabel($1);  $$=$4;  };

withoutlabelprintlnexp : println printexp  {$$=$2; $$->addprintln();};

withlabelprintlnexp : label colon println printexp  {$4->addlabel($1); $$=$4; $$->addprintln(); };

for_statement : for_token variables eq number comma number code_statements {$$ = new ASTfor_statement($2,$4,$6,1,$7) ;}
| for_token variables eq number comma number comma number code_statements {$$ = new ASTfor_statement($2,$4,$6,$8,$9) ;}  ;


goto_statement : goto_token label if_token exp { $$ = new ASTgoto_statement($2,$4);}
            | goto_token label { $$ = new ASTgoto_statement($2,NULL);} ;

variables : identifier {$$ = new ASTvariables("normal","none",$1,-1,"none"); }
| identifier lsb number rsb {$$ = new ASTvariables("array","integer",$1,$3,"none");   }; 
            | identifier lsb identifier rsb {$$ = new ASTvariables("array","identifier",$1,-1,$3) ;}


exp     :  exp pluss exp {$$ = new ASTexp("nonterminal",$1,$3,"plus",NULL) ;}
           | exp minuss exp {$$ = new ASTexp("nonterminal",$1,$3,"minus",NULL) ;}
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
           | term { $$ = new ASTexp("terminal",NULL,NULL,"NULL",$1);  }
           ;


term    : number { $$ = new ASTterm($1,NULL,"number");}
         | variables { $$ = new ASTterm(-1,$1,"variable") ;}
;

/* print expression after print key word,comma separated identifiers or strings  */

printexp :     printexp comma final_printexp { $$->push_back($3); }
               | final_printexp { $$ = new ASTprintexp($1,"NULL"); }
                ;


final_printexp : strings { $$=new ASTfinal_printexp($1,NULL); } 
               | variables { $$ = new ASTfinal_printexp("none",$1); }
               ;

readexp :      readexp comma variables { $$->push_back($3); cout<<"print vas"<<$3->name; }
              | variables { $$ = new ASTreadexp($1); cout<<"print vas"<<$1->name<<endl; }
                ;


%%       /* C code */

int main (int argc,char* argv[])
{
/* init symbol table */
  errors = 0;

  yyin = fopen(argv[1],"r");
    
  yyparse ();

  Interpretor* Interpr = new Interpretor();
  start->accept(Interpr);
  
  return 0;
  
}

void yyerror (char *s) {fprintf (stderr, "%s\n", s);}
