#include "ASTDefinitions.h"
#include <bits/stdc++.h>

using namespace std;

class Interpretor: public visitor
{
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
        cout<<literals->variables[i]->name;
  }
};
