#ifndef CODE_GENERATION_ANALYZER_H
#define CODE_GENERATION_ANALYZER_H

// Analyzer ////////////////////////////////////////////////////////////////////////

#include "parser.h"
const int SYMBOL_HASH_SIZE=10007;

struct LineLocation
{
    int line_num;
    LineLocation* next;
};
struct VariableInfo
{
    char* name;
    int memloc;
    int value=0;
    LineLocation* head_line; // the head of linked list of source line locations
    LineLocation* tail_line; // the tail of linked list of source line locations
    VariableInfo* next_var; // the next variable in the linked list in the same hash bucket of the symbol table
};

struct SymbolTable
{
    int num_vars;
    VariableInfo* var_info[SYMBOL_HASH_SIZE];

    SymbolTable();
    int Hash(const char* name);
    VariableInfo* Find(const char* name);
    void Insert(const char* name, int line_num);
    void updateValue(const char*var,int newValue);
    void Print();
    void Destroy();

};
extern SymbolTable* symbolTable;
void generateSymbolTable(TreeNode* node);
#endif //CODE_GENERATION_ANALYZER_H
