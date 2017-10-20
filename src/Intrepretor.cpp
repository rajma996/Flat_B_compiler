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
  void visit(class ASTliterals* literals)
  {
    cout<<"visiting the literans"<<endl;
    for (int i=0;i<literals->variables.size();i++)
      {
        cout<<literals->variables[i]->name<<endl;
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
  
  // void visit(class ASTvariables* variables)
  // {
  //   if (var_type=="normal")
  //     {
  //       if (symbol_table.find(make_pair(variables->name,0))!=symbol_table.end())
  //         symbol_table[make_pair(variables->name,0)]=0;
  //       else
  //         {cout<<"error : variable previously definded "<<endl; return;}
  //     }
  //   else if (var_type=="array")
  //     {
  //       if (size_type)
  //     }
  // }
};
