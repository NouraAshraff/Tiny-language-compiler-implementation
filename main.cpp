#include<math.h>
#include <iostream>
#include <stack>
#include "scanner.h"
#include "parser.h"
#include "analyzer.h"
#include "codeGeneration.h"
using namespace std;
SymbolTable* symbolTable;

int main(){
    CompilerInfo* compilerInfo=new CompilerInfo("input.txt","output.txt", "debug.txt");
    TreeNode* parseTree= Parse(compilerInfo);
    PrintTree(parseTree);
    symbolTable=new SymbolTable();
    generateSymbolTable(parseTree);
    symbolTable->Print();
    simulateCode(parseTree);
    symbolTable->Print();
    symbolTable->Destroy();
    DestroyTree(parseTree);
}