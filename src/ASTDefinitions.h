#include<bits/stdc++.h>
using namespace std;

union node
{
  int num;
  char* id;
  class ASTvariables* variables;
  class ASTcode_statements* code_statements;
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
  class ASTliterals* literals;
  class ASTdecl_statement* decl_statement;
  class ASTdecl_statements* decl_statements;
  class ASTprogram* program;
  vector<ASTcode_line*> *code_lines;
};

typedef union node YYSTYPE;
#define YYSTYPE_IS_DECLARED 1

class ASTnode
{
  
};

class visitor
{
 public:
  virtual void visit(class ASTprogram*)=0;;
  virtual void visit(class ASTdecl_statements*)=0;
  virtual void visit(class ASTdecl_statement*) =0;;
  virtual void visit(class ASTliterals*) =0;
  virtual void visit(class ASTcode_statements*) =0;
  virtual void visit(class ASTif_statement*) = 0;
  virtual void visit(class ASTfor_statement*) = 0;
  virtual void visit(class ASTgoto_statement*)=0;
  virtual void visit(class ASTassignment* )=0;
  virtual void visit(class ASTprintexp* )=0;
  virtual void visit(class ASTreadexp* )=0;
  virtual void visit(class ASTfinal_printexp*)=0;
};

class ASTprogram:public ASTnode
{
 public:
  class ASTdecl_statements* decl_statements;
  class ASTcode_statements* code_statements;
 public:
  ASTprogram(class ASTdecl_statements* ASTdecl_statements, class ASTcode_statements* ASTcode_statements);
  void traverse();
  void accept(visitor *);
};

class ASTdecl_statements:public ASTnode
{
public:
  class ASTdecl_statement* decl_statement;
 public:
  ASTdecl_statements(class ASTdecl_statement* decl_statement);
  void traverse();
  void accept(visitor*);
};


class ASTdecl_statement:public ASTnode
{
public:
  vector<class ASTliterals*> literals;
 public:
  ASTdecl_statement(class ASTliterals* literals);
  void push_back(class ASTliterals* literals);
  void traverse();
  void accept(visitor*);
};

class ASTcode_statements:public ASTnode
{
 public:
  vector<ASTcode_line*> *code_lines;
  
 public:
  ASTcode_statements(vector<ASTcode_line* > *code_lines);
  void traverse();
  void accept(visitor* v);
};

class ASTliterals:public ASTnode
{
 public:
  vector<class ASTvariables*> variables;
 public:
  ASTliterals(class ASTvariables* variables);
  void push_back(class ASTvariables* variables);
  void traverse();
  void accept(visitor* );
};

class ASTcode_line : public ASTnode
{
 public :
  virtual void accept(visitor*)=0;
};

class ASTif_statement : public ASTcode_line
{
 public :
  class ASTexp* exp;
  class ASTcode_statements* if_code_statements;
  class ASTcode_statements* else_code_statements;
  string label;
 public:
  ASTif_statement(class ASTexp* exp,class ASTcode_statements* if_code_statements,class ASTcode_statements* else_code_statements);
  void accept(visitor*);
  void addlabel(string );
};

class ASTfor_statement : public ASTcode_line
{
 public :
  class ASTvariables* variable;
  int lowerrange;
  int higherrange;
  int difference;
  class ASTcode_statements* code_statements;
  string label;
 public:
  ASTfor_statement(class ASTvariables* variables,int lowerrange,int higherrange,int difference,class ASTcode_statements* code_statements);
  void accept(visitor*);
  void addlabel(string label);
};


class ASTgoto_statement : public ASTcode_line
{
 public :
  string label;
  class ASTexp* exp;
 public :
  ASTgoto_statement(string label, class ASTexp* exp);
  void accept(visitor*);
};

class ASTassignment :public ASTcode_line
{
 public :
  class ASTvariables* variable;
  class ASTexp* exp ;
  string label;
 public:
  ASTassignment(class ASTvariables* variable, class ASTexp* exp,string label);
  void accept(visitor*);
};

class ASTvariables : public ASTnode
{
 public :
  string var_type ; // array or normal;
  string size_type ; // size by identifier or integer
  string name ; // name of variable
  int int_size ; // int size of array
  string ide_size ; // identifier size
 public :
  ASTvariables(string var_type,string size_type, string name,int int_size,string ide_size ) ;
};


class ASTexp :public ASTnode
{
 public:
  string exptype ; // terminal or nonterminal
  class ASTexp * lexp ;
  class ASTexp* rexp;
  string operator_type ;
  class ASTterm* term;
 public:
  ASTexp(string exptype, class ASTexp* lexp, class ASTexp* rexp,string operator_type, class ASTterm* term );
};

class ASTterm: public ASTnode
{
 public:
  int number;
  class ASTvariables* variable;
  string terminal_type; // type number or variable;
 public :
  ASTterm(int number,class ASTvariables* variable, string terminal_type);
};

class ASTprintexp: public ASTcode_line
{
 public:
  vector<class ASTfinal_printexp*> printexp_vec;
  string label;
  bool println;
 public :
  ASTprintexp(class ASTfinal_printexp * final_printexp,string label);
  void push_back(class ASTfinal_printexp * final_printexp);
  void accept(visitor* v);
  void addlabel(string s);
  void addprintln();
};


class ASTfinal_printexp: public ASTcode_line
{
 public:
  string str;
  class ASTvariables* var;
 public :
  ASTfinal_printexp(string str,class ASTvariables* var);
  void accept(visitor* v);
};


class ASTreadexp: public ASTcode_line
{
 public:
  vector<class ASTvariables*> variables;
  string label;
 public:
  ASTreadexp(class ASTvariables* variables);
  void push_back(class ASTvariables* variables);
  void accept(visitor*);
  void addlabel(string label);
};


