#include "ASTDefinitions.h"
#include <bits/stdc++.h>

using namespace std;

extern int errors;


ASTprogram::ASTprogram (class ASTdecl_statements* ASTdecl_statements, class ASTcode_statements* ASTcode_statements)
{
  this->decl_statements = decl_statements;
  this->code_statements = code_statements;
}

ASTdecl_statement::ASTdecl_statement(class ASTliterals* literals)
{
  this->literals.push_back(literals);
}

ASTdecl_statements::ASTdecl_statements(class ASTdecl_statement*  decl_statement )
{
  this->decl_statement = decl_statement;
}


void ASTdecl_statement::push_back(class ASTliterals* literals)
{
  this->literals.push_back(literals);
}

ASTliterals::ASTliterals(class ASTvariables* variables)
{
  this->variables.push_back(variables);
}

void ASTliterals::push_back(class ASTvariables* variables)
{
  this->variables.push_back(variables);
}

ASTcode_statements::ASTcode_statements( class ASTcode_line* code_line)
{
  this->code_line=code_line;
}


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

ASTexp::ASTexp(string exptype, class ASTexp* lexp, class ASTexp* rexp,string operator_type, class ASTterm* term)
{
  this->exptype = exptype ;
  this->lexp = lexp;
  this->rexp = rexp;
  this->operator_type = operator_type;
  this->term = term;
}

ASTassignment::ASTassignment(class ASTvariables* variable, class ASTexp* exp)
{
  this->variable = variable;
  this->exp = exp;
}

ASTgoto_statement::ASTgoto_statement(string label, class ASTexp* exp)
{
  this->label = label;
  this->exp = exp;
}

void ASTcode_line::push_back(class ASTcode_line* code_line)
{
  this->code_line.push_back(code_line);
}

ASTfor_statement::ASTfor_statement(string identifier,int lowerrange,int higherrange,class ASTcode_line* code_line)
{
  this->identifier = identifier;
  this->lowerrange = lowerrange;
  this->higherrange = higherrange;
  this->code_line = code_line;
}

ASTif_statement::ASTif_statement(class ASTexp* exp,class ASTcode_line* code_line)
{
  this->exp = exp;
  this->code_line = code_line;
}


ASTreadexp::ASTreadexp(class ASTvariables* variables)
{
  this->variables.push_back(variables);
}

void ASTreadexp::push_back(class ASTvariables* variables)
{
  this->variables.push_back(variables);
}
