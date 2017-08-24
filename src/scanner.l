%{
#include "y.tab.h"
%}

%%
"declblock"	 {return declblock;}
"codeblock"      {return codeblock;}
"int"            {return int_datatype;}
"println"        {return println;}
"print"          {return print;}
"read"           {return read_token;}
"exit"	         {return exit_command;}
\"[^\"]*\"       {yylval.id = yytext ; return string ;}
","              {return comma;}

\[[1-9][0-9]*\]  {yylval.id = yytext; return array_size ;}
[a-zA-Z]+	 {yylval.id = yytext; return identifier;}
[0-9]+           {yylval.num = atoi(yytext); return number;}
[ \t\n]                ;
[-f+={};]           	   {return yytext[0];}
.                      {ECHO; yyerror ("unexpected character");}

%%
int yywrap (void) {return 1;}

