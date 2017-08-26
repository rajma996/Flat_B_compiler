%{
#include "parser.tab.h"
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

\"[^\"]*\"       {yylval.id = yytext ; return string ;}
"{"              {return lcb;}
"}"              {return rcb;}
"("              {return lrb;}
")"              {return rrb;}
","              {return comma;}
"+"              {return plus;}
"-"              {return minus;}
"*"              {return mul;}
"/"              {return divi;}
"<"              {return lt;}
"<="             {return lte;}
">"              {return gt;}
">="             {return gte;}
"="              {return eq;}
"=="             {return eqeq;}
"!="             {return neq;}
"&&"             {return and;}
"||"             {return or;}
"%"              {return mod;}
":"              {return colon;}
\[[1-9][0-9]*\]  {yylval.id = yytext; return array_num_index ;}
\[[a-zA-Z]+\]    {yylval.id = yytext; return array_identi_index ;}
[a-zA-Z]+	 {yylval.id = yytext; return identifier;}
[A-Z]+[0-9]+     {yylval.id = yytext; return label;}
[0-9]+           {yylval.num = atoi(yytext); return number;}
[ \t\n]                ;
[-f+!;]           	   {return yytext[0];}
.                      {ECHO; yyerror ("unexpected character");}
%%
int yywrap (void) {return 1;}

