#include<bits/stdc++.h>
using namespace std;

union node
{
  int num;
  char* id;
  class ASTterm* ter;
};
union termraj {int s1; int s2;};

typedef union node YYSTYPE;

class ASTnode
{
};

class ASTterm : public ASTnode
{
 private :
  termraj no;
 public :
  ASTterm(int ty,int s) {if (ty==1) no.s1=5; else no.s2=6;}
};



