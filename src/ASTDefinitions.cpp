#include "ASTDefinitions.h"
#include <bits/stdc++.h>

using namespace std;

extern int errors;

ASTvariables::ASTvariables(string var_type,string size_type, string name,int int_size,string ide_size )
{
  this->var_type=var_type;
  this->size_type=size_type;
  this->name=name;
  this->int_size=int_size;
  this->ide_size = ide_size;
}

