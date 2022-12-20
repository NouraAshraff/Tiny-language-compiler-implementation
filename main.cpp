#include "scanner.h"
#include "parser.h"
#include "analyzer.h"
#include "codeGeneration.h"
using namespace std;

int main(){
    //freopen ("output.txt","w",stdout);
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