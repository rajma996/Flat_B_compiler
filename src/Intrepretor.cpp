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
    cout<<"visiting main node"<<endl;
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
    for (int i=0;i<code_statements->code_lines->size();i++)
      {
        ((*(code_statements->code_lines))[i])->accept(this);
      }
  }


  void visit(class ASTif_statement* if_statement)
  {
    cout<<"visigint if statemetne"<<endl;
    int exp_val = this->evaluateexpr(if_statement->exp);
    if (exp_val)
      if_statement->code_statements->accept(this);
    return ;
  }

  void visit(class ASTfor_statement* for_statement)
  {
    map<pair<string,int>,int>::iterator it;
    int lowerrange = for_statement->lowerrange;
    int higherrange = for_statement->higherrange;
    int diff = for_statement->difference;
    it = this->getmapiterator(for_statement->variable);
    for (it->second=lowerrange;it->second<=higherrange;it->second+=diff)
      {
        class ASTcode_statements* code_statements = for_statement->code_statements;
        for (int i=0;i<code_statements->code_lines->size();i++)
          {
            ((*(code_statements->code_lines))[i])->accept(this);
          }
      }
    return;
  }

  void visit(class ASTgoto_statement* goto_statement)
  {
    int expval = 1;
    if (goto_statement->exp!=NULL)
      {
        int expval = this->evaluateexpr(goto_statement->exp);
      }
    if (expval)
      {
        cout <<"now going to label "<<goto_statement->label<<endl;
        cout<<goto_statement->label<<endl;
      }
    return;
  }

  int evaluateexpr(class ASTexp* expr)
  {
    if (expr->exptype == "terminal")
      {
        if (expr->term->terminal_type=="number" )
            return expr->term->number;
        else if (expr->term->terminal_type=="variable")
            return this->getmapiterator(expr->term->variable)->second;
      }

    if (expr->operator_type=="plus")
        return evaluateexpr(expr->lexp)+evaluateexpr(expr->rexp);
    else if  (expr->operator_type=="mul")
        return evaluateexpr(expr->lexp)*evaluateexpr(expr->rexp);
    else if  (expr->operator_type=="divi")
        return evaluateexpr(expr->lexp)/evaluateexpr(expr->rexp);
    else if  (expr->operator_type=="lt")
        return evaluateexpr(expr->lexp)<evaluateexpr(expr->rexp);
    else if  (expr->operator_type=="gt")
        return evaluateexpr(expr->lexp)>evaluateexpr(expr->rexp);
    else if  (expr->operator_type=="lte")
        return evaluateexpr(expr->lexp)<=evaluateexpr(expr->rexp);
    else if  (expr->operator_type=="gte")
        return evaluateexpr(expr->lexp)>=evaluateexpr(expr->rexp);
    else if  (expr->operator_type=="oror")
        return (evaluateexpr(expr->lexp)||evaluateexpr(expr->rexp));
    else if  (expr->operator_type=="andand")
      return (evaluateexpr(expr->lexp)&&evaluateexpr(expr->rexp));
    else if  (expr->operator_type=="eqeq")
      return ((evaluateexpr(expr->lexp)==evaluateexpr(expr->rexp)));
    else if  (expr->operator_type=="neq")
        return (evaluateexpr(expr->lexp)!=evaluateexpr(expr->rexp));

  }

  void visit(class ASTassignment* assignment)
  {
    int expval = evaluateexpr(assignment->exp);
    this->getmapiterator(assignment->variable)->second = expval;
    return;
  }

  void visit(class ASTprintexp* printexp)
  {
    for (int i=0;i<printexp->printexp_vec.size();i++)
        printexp->printexp_vec[i]->accept(this);
    //print end of line after print statement;
    cout<<endl;
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


  map<pair<string,int>,int>::iterator getmapiterator(class ASTvariables* variable)
  {
    this->validatevar(variable);
    if (variable->var_type=="normal")
        return symbol_table.find(make_pair(variable->name,-1));
    return symbol_table.find(make_pair(variable->name,variable->int_size));
  }


  void visit(class ASTreadexp* readexp)
  {
    cout<<"inside readexp visit"<<endl;
    for (int i=0;i<readexp->variables.size();i++)
      {
        class ASTvariables* var = readexp->variables[i];
        this->validatevar(var);
        map<pair<string,int>,int>::iterator it = this->getmapiterator(var) ;
        cin>>it->second;
      }
    return;
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
