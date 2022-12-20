#include "analyzer.h"


////////////////////////////////////////////////////////////////////////////////////
// Analyzer ////////////////////////////////////////////////////////////////////////

    SymbolTable::SymbolTable() { num_vars=0; int i; for(i=0; i < SYMBOL_HASH_SIZE; i++) var_info[i]=0;}
    int SymbolTable::Hash(const char* name)
    {
        int i, len=strlen(name);
        int hash_val=11;
        for(i=0;i<len;i++) hash_val=(hash_val*17+(int)name[i])%SYMBOL_HASH_SIZE;
        return hash_val;
    }
    VariableInfo* SymbolTable:: Find(const char* name)
    {   //search in the hash bucket
        int h=Hash(name);
        VariableInfo* cur=var_info[h];
        while(cur)
        {
            if(Equals(name, cur->name)) return cur;
            cur=cur->next_var;
        }
        return 0;
    }
    void SymbolTable::Insert(const char* name, int line_num)
    {
        LineLocation* lineloc=new LineLocation;
        lineloc->line_num=line_num;
        lineloc->next=nullptr;

        int h=Hash(name);//set hash value to name
        VariableInfo* prev=nullptr;
        VariableInfo* cur=var_info[h];

        while(cur)
        {
            if(Equals(name, cur->name))
            {
                // just add this line location to the list of line locations of the existing var
                cur->tail_line->next=lineloc;
                cur->tail_line=lineloc;
                return;
            }
            prev=cur;
            cur=cur->next_var;
        }

        VariableInfo* vi=new VariableInfo;
        vi->head_line=vi->tail_line=lineloc;
        vi->next_var=0;
        vi->memloc=num_vars++;
        AllocateAndCopy(&vi->name,name);
        if(!prev) var_info[h]=vi;
        else prev->next_var=vi;
    }
    void SymbolTable:: updateValue(const char*var,int newValue){
        int i;
        for(i=0;i<SYMBOL_HASH_SIZE;i++)
        {
            VariableInfo* curv=var_info[i];
            while(curv)
            {
                if(Equals(var, curv->name)){
                    curv->value=newValue;
                    var_info[i]=curv;
                    return;
                }
                curv=curv->next_var;
            }
        }
    }
    void SymbolTable:: Print()
    {
        int i;
        for(i=0;i<SYMBOL_HASH_SIZE;i++)
        {
            VariableInfo* curv=var_info[i];
            while(curv)
            {
                printf("[Var=%s][Mem=%d][value=%d]", curv->name, curv->memloc,curv->value);
                LineLocation* curl=curv->head_line;
                while(curl)
                {
                    printf("[Line=%d]", curl->line_num);
                    curl=curl->next;
                }
                printf("\n");
                curv=curv->next_var;
            }
        }
    }
    void SymbolTable:: Destroy()
    {
        int i;
        for(i=0;i<SYMBOL_HASH_SIZE;i++)
        {
            VariableInfo* curv=var_info[i];
            while(curv)
            {
                LineLocation* curl=curv->head_line;
                while(curl)
                {
                    LineLocation* pl=curl;
                    curl=curl->next;
                    delete pl;
                }
                VariableInfo* p=curv;
                curv=curv->next_var;
                delete p;
            }
            var_info[i]=0;
        }
    }


void generateSymbolTable(TreeNode* node)//if node is id or Assign or Read insert variable into symbol table
{
    int i;
    if(node->node_kind==ID_NODE || node->node_kind==ASSIGN_NODE || node->node_kind==READ_NODE)
    {
        symbolTable->Insert(node->id,node->line_num);
    }
    for(i=0;i<MAX_CHILDREN;i++) if(node->child[i]) generateSymbolTable(node->child[i]);
    if(node->sibling) generateSymbolTable(node->sibling);
}