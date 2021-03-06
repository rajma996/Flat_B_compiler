#include <bits/stdc++.h>
#include <stdint.h>
#include "ASTDefinitions.h"
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/Bitcode/ReaderWriter.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/Support/raw_ostream.h>

using namespace llvm;
using namespace std;

class Codegen
{

public:

  llvm::Module* module ;
  map<pair<string,int>,llvm::Value*> symbol_table_llvm;
  llvm::BasicBlock* block;
  llvm::Function* mainFunction;
 
public :
  void codegen(class ASTprogram* program)
  {
    module = new llvm::Module("main",llvm::getGlobalContext());
    this->module = module;

    cout<<"hello world"<<endl;
    codegen(program->decl_statements);
    FunctionType *ftype = FunctionType::get(Type::getVoidTy(llvm::getGlobalContext()), false);
    this->mainFunction = Function::Create(ftype, GlobalValue::InternalLinkage, "main",module);
    BasicBlock *bblock = BasicBlock::Create(getGlobalContext(), "entry", mainFunction, 0);
    this->block = bblock;
    // codegen( (*(program->code_statements->code_lines))[0] );
    this->module->dump();
    return ;
  }

  void codegen(class ASTdecl_statements* decl_statements)
  {
    codegen(decl_statements->decl_statement);
  }

  void codegen(class ASTdecl_statement* decl_statement)
  {
    for (int i=0;i<decl_statement->literals.size();i++)
      {
        codegen(decl_statement->literals[i]);
      }
  }

   void codegen(class ASTassignment* assignment)
   {
      llvm::Value* ans = evaluate_expr(assignment->exp);
     // map<pair<string,int>,llvm::Value*>::iterator it;
     // it = symbol_table_llvm.find(make_pair(assignment->variable->name,-1));
     // llvm::Value* location = it->second;
     // llvm::Value* existingvalue = new llvm::loadInst(location,"load",NULL);
   }


  llvm::Value* evaluate_expr(class ASTexp* exp)
   {
     if (exp->exptype=="terminal")
       {
         if (exp->term->terminal_type=="number")
           {
             return ConstantFP::get(getGlobalContext(), APFloat(0.0));
           }
       }
   }

  llvm::Value* get_new_global_variable(string name)
  {
    llvm::GlobalVariable * globalInteger = new llvm::GlobalVariable(*module, llvm::Type::getFP128Ty(llvm::getGlobalContext()) , false, llvm::GlobalValue::CommonLinkage, NULL,name);
    globalInteger->setInitializer(ConstantFP::get(getGlobalContext(), APFloat(0.0)));
    return globalInteger;
  }

  void codegen(class ASTliterals* literals)
  {
    for (int i=0;i<literals->variables.size();i++)
      {
        class ASTvariables* temp_variable = literals->variables[i];
        if (temp_variable->var_type=="normal")
          {
            if (symbol_table_llvm.find(make_pair(temp_variable->name,-1))!=symbol_table_llvm.end())
              {
                cout<<"variable previousley defined";
                exit(0);
              }
            else
              {
                llvm::Value* temp = get_new_global_variable(temp_variable->name);
                symbol_table_llvm[make_pair(temp_variable->name,-1)]=temp;
              }
          }
        else if (temp_variable->var_type=="array")
          {
            if (temp_variable->size_type=="integer")
              {
                int si = temp_variable->int_size;
                for (int i=0;i<si;i++)
                  {

                    symbol_table_llvm[make_pair(temp_variable->name,i)]=get_new_global_variable(temp_variable->name+"_"+std::to_string(i));
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
  
};
