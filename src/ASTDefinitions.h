#include<bits/stdc++.h>
using namespace std;

union node
{
  int num;
  char* id;
  class ASTvariables* variables;
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



