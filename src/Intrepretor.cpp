#include "ASTDefinitions.h"
#include <bits/stdc++.h>

using namespace std;

class Interpretor: public visitor
{
private:
  map<pair<string,int>,int>  symbol_table;
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
        string temp = literals->variables[i]->name;
        string newtemp = "";
        for (int j=0;j<temp.size();j++)
          {
            if ( (temp[j]>='a' && temp[j]<='z') || (temp[j]>='A' && temp[j]<='Z' ) )
            newtemp += temp[j];
          }
        literals->variables[i]->name = newtemp;
        
        class ASTvariables* temp_variable = literals->variables[i];
        if (temp_variable->var_type=="normal")
          {
            if (symbol_table.find(make_pair(temp_variable->name,0))!=symbol_table.end())
              {
                cout<<"variable previousley defined";
                return;
              }
            else
              symbol_table[make_pair(temp_variable->name,0)]=0;
          }
        else if (temp_variable->var_type=="array")
          {
            if (temp_variable->size_type=="integer")
              {
                int si = temp_variable->int_size;
                for (int i=0;i<si;i++)
                  {
                    symbol_table[make_pair(temp_variable->name,i)]=0;
                  }
              }
          }
      }
  }

  void visit(class ASTcode_statements* code_statements)
  {
    cout<<"code statement"<<endl;
    if (code_statements->code_line==NULL)
      {
        cout<<"no code statement"<<endl;
        return;
      }
    code_statements->code_line->accept(this);
  }

  void visit(class ASTcode_line* code_line)
  {
    ASTif_statement* v = dynamic_cast<ASTif_statement*>(code_line);
    if (v)
       {
         cout<<"if statementdetected";
       }
    return;
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
    return;
  }

  void visit(class ASTreadexp* readexp)
  {
    return;
  }

  void visit(class ASTfinal_printexp* final_printexp)
  {
    return;
  }

  
};
