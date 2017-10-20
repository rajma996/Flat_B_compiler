#include<bits/stdc++.h>
using namespace std;

union node
{
  int num;
  char* id;
  class ASTvariables* variables;
  class ASTfinal_printexp* final_printexp;
  class ASTprintexp* printexp;
  class ASTreadexp* readexp;
  class ASTterm* term;
  class ASTexp* exp ;
  class ASTassignment* assignment ;
  class ASTgoto_statement* goto_statement;
  class ASTfor_statement* for_statement ;
  class ASTif_statement* if_statement ;
  class ASTcode_line* code_line;
};

typedef union node YYSTYPE;
#define YYSTYPE_IS_DECLARED 1

class ASTnode
{
};

class ASTvariables : public ASTnode
{
 private :
  string var_type ; // array or normal;
  string size_type ; // size by identifier or integer
  string name ; // name of variable
  int int_size ; // int size of array
  string ide_size ; // identifier size
 public :
  ASTvariables(string var_type,string size_type, string name,int int_size,string ide_size ) ;
};

class ASTfinal_printexp: public ASTnode
{
 private:
  string str;
  class ASTvariables* var;
 public :
  ASTfinal_printexp(string str,class ASTvariables* var);
};


class ASTterm: public ASTnode
{
 private:
  int number;
  class ASTvariables* variable;
  string terminal_type; // type number or variable;
 public :
  ASTterm(int number,class ASTvariables* variable, string terminal_type);
};

class ASTexp :public ASTnode
{
 private:
  string exptype ; // terminal or nonterminal
  class ASTexp * lexp ;
  class ASTexp* rexp;
  string operator_type ;
  class ASTterm* term;
 public:
  ASTexp(string exptype, class ASTexp* lexp, class ASTexp* rexp,string operator_type, class ASTterm* term );
};


class ASTcode_line : public ASTnode
{
 private :
  vector<class ASTcode_line*> code_line;
 public :
  void push_back(class ASTcode_line* code_line);
};

class ASTfor_statement : public ASTcode_line
{
 private :
  string identifier;
  int lowerrange;
  int higherrange;
  class ASTcode_line* code_line;
 public:
  ASTfor_statement(string identifier,int lowerrange,int higherrange,class ASTcode_line* code_line);
};

class ASTif_statement : public ASTcode_line
{
 private :
  class ASTexp* exp;
  class ASTcode_line* code_line;
 public:
  ASTif_statement(class ASTexp* exp,class ASTcode_line* code_line);
};

class ASTgoto_statement : public ASTcode_line
{
 private :
  string label;
  class ASTexp* exp;
 public :
  ASTgoto_statement(string label, class ASTexp* exp);
};

class ASTassignment :public ASTcode_line
{
 private :
  class ASTvariables* variable;
  class ASTexp* exp ;
 public:
  ASTassignment(class ASTvariables* variable, class ASTexp* exp);
};

class ASTprintexp: public ASTcode_line
{
 private:
  vector<class ASTfinal_printexp*> printexp_vec;
 public :
  ASTprintexp(class ASTfinal_printexp * final_printexp);
  void push_back(class ASTfinal_printexp * final_printexp);
};

class ASTreadexp: public ASTcode_line
{
 private:
  vector<class ASTvariables*> variables;
 public:
  ASTreadexp(class ASTvariables* variables);
  void push_back(class ASTvariables* variables);
};


