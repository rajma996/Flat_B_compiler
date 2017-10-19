#include "ASTDefinitions.h"
#include <bits/stdc++.h>

using namespace std;

extern int errors;

ASTvariables::ASTvariables(string var_type,string size_type, string name,int int_size,string ide_size )
{
  this->var_type=var_type;
  this->size_type=size_type;
  this->name=name;
  this->int_size=int_size;
  this->ide_size = ide_size;
}

ASTfinal_printexp::ASTfinal_printexp(string str,class ASTvariables* var)
{
  this->str = str;
  this->var = var;
}

ASTprintexp::ASTprintexp(class ASTfinal_printexp * final_printexp)
{
  this->printexp_vec.push_back(final_printexp);
}
void ASTprintexp::push_back(class ASTfinal_printexp * final_printexp)
{
  this->printexp_vec.push_back(final_printexp);
}

ASTterm::ASTterm(int number,class ASTvariables * variable, string terminal_type)
{
  this->number = number;
  this->variable = variable;
  this->terminal_type = terminal_type;
}

