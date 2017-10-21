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

ASTcode_statements::ASTcode_statements( vector<ASTcode_line*>* code_lines )
{
  this->code_lines=code_lines;
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


ASTif_statement::ASTif_statement(class ASTexp* exp,class ASTcode_statements* code_statements)
{
  this->exp = exp;
  this->code_statements = code_statements;
}

void ASTif_statement::accept(visitor* v)
{
  v->visit(this);
}

void ASTif_statement::addlabel(string label)
{
  if (label!="NULL")
    {
      int colonind = label.find(':');
      label =  label.substr(0,colonind);
    }
  this->label=label;
}

ASTfor_statement::ASTfor_statement(class ASTvariables* variable  ,int lowerrange,int higherrange,int difference,class ASTcode_statements* code_statements )
{
  this->variable = variable;
  this->lowerrange = lowerrange;
  this->higherrange = higherrange;
  this->difference = difference;
  this->code_statements = code_statements;
}

void ASTfor_statement::accept(visitor* v)
{
  v->visit(this);
}

void ASTfor_statement::addlabel(string label)
{
  if (label!="NULL")
    {
      int colonind = label.find(':');
      label =  label.substr(0,colonind);
    }
  this->label=label;
}

ASTgoto_statement::ASTgoto_statement(string label, class ASTexp* exp)
{
  string newlab = "";
  for (int i=0;i<label.size();i++)
    {
      if ( (label[i]>='A' && label[i]<='Z') || (label[i]>='0' && label[i]<='9') )
        newlab += label[i];
      else break;
    }
  this->label = newlab;
  this->exp = exp;
}

void ASTgoto_statement::accept(visitor* v)
{
  v->visit(this);
}

ASTassignment::ASTassignment(class ASTvariables* variable, class ASTexp* exp,string label)
{
  if (label!="NULL")
    {
      int colonind = label.find(':');
      label =  label.substr(0,colonind);
    }
  this->variable = variable;
  this->exp = exp;
  this->label = label;
}

void ASTassignment::accept(visitor* v)
{
  v->visit(this);
}

ASTvariables::ASTvariables(string var_type,string size_type, string name,int int_size,string ide_size )
{

  string newname = "";

  //for some unkown reasons extra stuff coming in varnames :( .
  for (int i=0;i<name.size();i++)
    {
      if ((name[i]>='A' && name[i]<='Z') || (name[i]>='a'&&name[i]<='z'))
        newname += name[i];
    }
  this->var_type=var_type;
  this->size_type=size_type;
  this->name=newname;
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

ASTprintexp::ASTprintexp(class ASTfinal_printexp * final_printexp,string label)
{
  this->printexp_vec.push_back(final_printexp);
  this->label = label;
}

void ASTprintexp::push_back(class ASTfinal_printexp * final_printexp)
{
  this->printexp_vec.push_back(final_printexp);
}

void ASTprintexp::accept(visitor* v)
{
  v->visit(this);
}

void ASTprintexp::addlabel(string label)
{
    if (label!="NULL")
    {
      int colonind = label.find(':');
      label =  label.substr(0,colonind);
    }
    this->label=label;
}

ASTfinal_printexp::ASTfinal_printexp(string str,class ASTvariables* var)
{
  if (var==NULL)
      str = str.substr(1,str.size()-2);
  this->str = str;
  this->var = var;
}

void ASTfinal_printexp::accept(visitor* v)
{
  v->visit(this);
}

ASTreadexp::ASTreadexp(class ASTvariables* variables)
{
  this->variables.push_back(variables);
}

void ASTreadexp::push_back(class ASTvariables* variables)
{
  this->variables.push_back(variables);
}

void ASTreadexp::accept(visitor* v)
{
  v->visit(this);
}

void ASTreadexp::addlabel(string label)
{
    if (label!="NULL")
    {
      int colonind = label.find(':');
      label =  label.substr(0,colonind);
    }
    this->label=label;
}
