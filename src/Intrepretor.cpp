#include "ASTDefinitions.h"
#include <bits/stdc++.h>

using namespace std;

class Interpretor: public visitor
{
private:
  map<pair<string,int>,int>  symbol_table;
  map<string,int> array_size;
public :
  void visit(class ASTprogram* program)
  {
    cout<<"visiting main node everything is below you"<<endl;
    program->decl_statements->accept(this);
    program->code_statements->accept(this);
  }
  void visit(class ASTdecl_statements* decl_statements)
  {
    cout<<"visiting decl statements"<<endl;
    if (decl_statements->decl_statement==NULL)
      {
        cout<<"No declarations"<<endl;
        return ;
      }
    decl_statements->decl_statement->accept(this);
  }
  void visit(class ASTdecl_statement* decl_statement)
  {
    cout<<"visiting dec statement"<<endl;
    for (int i=0;i<decl_statement->literals.size();i++)
      decl_statement->literals[i]->accept(this);
  }
  
  // initializint all variables to zero.
  void visit(class ASTliterals* literals)
  {
    cout<<"visiting the literans"<<endl;
    for (int i=0;i<literals->variables.size();i++)
      {
        class ASTvariables* temp_variable = literals->variables[i];
        if (temp_variable->var_type=="normal")
          {
            if (symbol_table.find(make_pair(temp_variable->name,-1))!=symbol_table.end())
              {
                cout<<"variable previousley defined";
                return;
              }
            else
              symbol_table[make_pair(temp_variable->name,-1)]=0;
          }
        else if (temp_variable->var_type=="array")
          {
            if (temp_variable->size_type=="integer")
              {
                array_size[temp_variable->name] = temp_variable->int_size;
                int si = temp_variable->int_size;
                for (int i=0;i<si;i++)
                  {
                    symbol_table[make_pair(temp_variable->name,i)]=0;
                  }
              }
            else if (temp_variable->size_type=="identifier")
              {
                cout<<"identifier cannot be used while array declaration"<<endl;
                exit(0);
              }
          }
      }
  }

  void visit(class ASTcode_statements* code_statements)
  {
    cout<<"code statement"<<endl;
    if (code_statements->code_lines==NULL)
      {
        cout<<"no code statement"<<endl;
        return;
      }
    cout<<"outsize"<<endl;
    for (int i=0;i<code_statements->code_lines->size();i++)
      ((*(code_statements->code_lines))[i])->accept(this);
  }


  void visit(class ASTif_statement* if_statement)
  {
    return ;
  }

  void visit(class ASTfor_statement* for_statement)
  {
    return;
  }

  void visit(class ASTgoto_statement* goto_statement)
  {
    return;
  }

  void visit(class ASTassignment* assignment)
  {
    return ;
  }

  void visit(class ASTprintexp* printexp)
  {
    for (int i=0;i<printexp->printexp_vec.size();i++)
      {
        printexp->printexp_vec[i]->accept(this);
      }
    return;
  }

  void visit(class ASTreadexp* readexp)
  {
    for (int i=0;i<readexp->variables.size();i++)
      {
        class ASTvariables* var = readexp->variables[i];
        this->validatevar(var);
        if (var->var_type=="array")
          cin>>symbol_table[make_pair(var->name,var->int_size)];
        else if (var->var_type=="normal")
          cin>>symbol_table[make_pair(var->name,-1)];
      }
    return;
  }

  void validatevar(class ASTvariables* var)
  {
    if (var->var_type=="array")
      {
        // checking existance
        if (symbol_table.find(make_pair(var->name,0))==symbol_table.end())
          {
            cout<<"no variable foune"<<endl;
            exit(0);
          }
        // check size
        if (array_size[var->name]<var->int_size+1)
          {
            cout<<"array index out of bound"<<endl;
            exit(0);
          }
      }

    else if (var->var_type=="normal")
      {
        // check existance
        if (symbol_table.find(make_pair(var->name,-1))==symbol_table.end())
          {
            cout<<"variable not found"<<endl;
            exit(0);
          }
      }

  }

  void printvar(class ASTvariables* var)
  {
    validatevar(var);
    if (var->var_type=="array")
      cout<<symbol_table[make_pair(var->name,var->int_size)];
    else
      cout<<symbol_table[make_pair(var->name,-1)];
    return;
  }
  
  void visit(class ASTfinal_printexp* final_printexp)
  {
    if (final_printexp->var==NULL)
      {
        cout<<final_printexp->str;
      }
    if (final_printexp->var!=NULL)
      this->printvar(final_printexp->var);
    return;
  }
  
};
