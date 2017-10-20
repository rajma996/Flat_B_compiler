#include "ASTDefinitions.h"
#include <bits/stdc++.h>

using namespace std;

extern int errors;

ASTprogram::ASTprogram (class ASTdecl_statements* decl_statements, class ASTcode_statements* code_statements)
{
  this->decl_statements = decl_statements;
  this->code_statements = code_statements;
}

void ASTprogram::traverse()
{
  cout<<"Stasrting program execution"<<endl;
  this->decl_statements->traverse();
  this->code_statements->traverse();
}

void ASTprogram::accept(visitor* v)
{
  v->visit(this);
}

ASTdecl_statements::ASTdecl_statements(class ASTdecl_statement*  decl_statement)
{
  this->decl_statement = decl_statement;
  this->decl_statement->traverse();
}

void ASTdecl_statements::traverse()
{
  this->decl_statement->traverse();
}

void ASTdecl_statements::accept(visitor* v)
{
  v->visit(this);
}


ASTdecl_statement::ASTdecl_statement(class ASTliterals* literals)
{
  this->literals.push_back(literals);
}

void ASTdecl_statement::push_back(class ASTliterals* literals)
{
  this->literals.push_back(literals);
}

void ASTdecl_statement::traverse()
{
  cout<<"entering decl block"<<endl;
  for (int i=0;i<this->literals.size();i++)
    {
      cout<<"literal "<<i<<endl;
      literals[i]->traverse();
    }
}

void ASTdecl_statement::accept(visitor* v)
{
  v->visit(this);
}

ASTcode_statements::ASTcode_statements( class ASTcode_line* code_line)
{
  cout<<"enterint code statements"<<endl;
  this->code_line=code_line;
}

void ASTcode_statements::traverse()
{
  cout<<"entering code statements"<<endl;
  return ;
}

void ASTcode_statements::accept(visitor* v)
{
  v->visit(this);
}

ASTliterals::ASTliterals(class ASTvariables* variables)
{
  this->variables.push_back(variables);
}

void ASTliterals::traverse()
{
  for(int i=0;i<this->variables.size();i++)
    cout<<variables[i]->name<<endl;;
}

void ASTliterals::push_back(class ASTvariables* variables)
{
  this->variables.push_back(variables);
}

void ASTliterals::accept(class visitor* v)
{
  v->visit(this);
}

void ASTcode_line::push_back(class ASTcode_line* code_line)
{
  this->code_line.push_back(code_line);
}

void ASTcode_line::accept(visitor* v)
{
  v->visit(this);
}

ASTif_statement::ASTif_statement(class ASTexp* exp,class ASTcode_line* code_line)
{
  this->exp = exp;
  this->code_line = code_line;
}

ASTfor_statement::ASTfor_statement(string identifier,int lowerrange,int higherrange,class ASTcode_line* code_line)
{
  this->identifier = identifier;
  this->lowerrange = lowerrange;
  this->higherrange = higherrange;
  this->code_line = code_line;
}


ASTgoto_statement::ASTgoto_statement(string label, class ASTexp* exp)
{
  this->label = label;
  this->exp = exp;
}

ASTassignment::ASTassignment(class ASTvariables* variable, class ASTexp* exp)
{
  this->variable = variable;
  this->exp = exp;
}

ASTvariables::ASTvariables(string var_type,string size_type, string name,int int_size,string ide_size )
{
  this->var_type=var_type;
  this->size_type=size_type;
  this->name=name;
  this->int_size=int_size;
  this->ide_size = ide_size;
}
ASTexp::ASTexp(string exptype, class ASTexp* lexp, class ASTexp* rexp,string operator_type, class ASTterm* term)
{
  this->exptype = exptype ;
  this->lexp = lexp;
  this->rexp = rexp;
  this->operator_type = operator_type;
  this->term = term;
}

ASTterm::ASTterm(int number,class ASTvariables * variable, string terminal_type)
{
  this->number = number;
  this->variable = variable;
  this->terminal_type = terminal_type;
}

ASTprintexp::ASTprintexp(class ASTfinal_printexp * final_printexp)
{
  this->printexp_vec.push_back(final_printexp);
}

void ASTprintexp::push_back(class ASTfinal_printexp * final_printexp)
{
  this->printexp_vec.push_back(final_printexp);
}


ASTfinal_printexp::ASTfinal_printexp(string str,class ASTvariables* var)
{
  this->str = str;
  this->var = var;
}


ASTreadexp::ASTreadexp(class ASTvariables* variables)
{
  this->variables.push_back(variables);
}

void ASTreadexp::push_back(class ASTvariables* variables)
{
  this->variables.push_back(variables);
}
