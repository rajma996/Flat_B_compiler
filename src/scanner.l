%{
#include "ASTDefinitions.h"
#include "parser.tab.h"
extern union node yylval;
extern "C" int yylex();
using namespace std;
extern int errors;

%}

%%
"declblock"	 {return declblock;}
"codeblock"      {return codeblock;}
"int"            {return int_datatype;}
"println"        {return println;}
"print"          {return print;}
"read"           {return read_token;}
"exit"	         {return exit_command;}
"if"             {return if_token;}
"for"            {return for_token;}
"goto"           {return goto_token;}
"else"           {return else_token;}
\"[^\"]*\"       {yylval.id = yytext ; return strings ;}
"{"              {return lcb;}
"}"              {return rcb;}
"("              {return lrb;}
")"              {return rrb;}
","              {return comma;}
"+"              {return pluss;}
"-"              {return minuss;}
"*"              {return mul;}
"/"              {return divi;}
"<"              {return lt;}
"<="             {return lte;}
">"              {return gt;}
">="             {return gte;}
"="              {return eq;}
"=="             {return eqeq;}
"!="             {return neq;}
"&&"             {return andand;}
"||"             {return oror;}
"%"              {return mod;}
":"              {return colon;}
"["              {return lsb;}
"]"              {return rsb;}
[a-zA-Z]+	 {yylval.id = yytext; return identifier;}
[A-Z]+[0-9]+     {yylval.id = yytext; return label;}
[0-9]+           {yylval.num = atoi(yytext); return number;}
[ \t\n]                ;
[-f+!;]        	   {return yytext[0];}
.                { errors++ ; }
%%
int yywrap (void) {return 1;}

