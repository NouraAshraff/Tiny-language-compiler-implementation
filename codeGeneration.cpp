#include <iostream>
#include "math.h"
#include "codeGeneration.h"
#include "parser.h"
#include "analyzer.h"
using namespace std;

void readSim(const char*x){//read variable value from user
    cout<<"Enter the value of "<<x<<" :";
    int n; cin>>n;
    symbolTable->updateValue(x,n);
}
int expSim(TreeNode* node){
    if(node->node_kind==ID_NODE){
        return symbolTable->Find(node->id)->value;
    }else if(node->node_kind==NUM_NODE){
        return node->num;
    }
    if(node->node_kind==OPER_NODE){
        if(node->oper==POWER){
            int num1= expSim(node->child[1]);
            int num2= expSim(node->child[0]);
            return (int)pow(num1,num2);
        }else{
            int num1= expSim(node->child[0]);
            int num2= expSim(node->child[1]);
            if(node->oper==PLUS) return num1+num2;
            else if(node->oper==MINUS)return num1-num2;
            else if(node->oper==LESS_THAN)return num1<num2;
            else if(node->oper==EQUAL)return num1==num2;
            else if(node->oper==DIVIDE)return num1/num2;
            else if(node->oper==TIMES)return num1*num2;
        }
    }
}
void writeSim(TreeNode* node){//get variable value from symbol table and write it
    cout << expSim(node->child[0]) << endl;
}
void assignSim(TreeNode* node){
    char *var=node->id; //fact
    int value= expSim(node->child[0]);
    symbolTable->updateValue(var,value);
}
void simulateCode(TreeNode* node);
void RepeatSim(TreeNode* node){//repeat all Lines inside repeat until expression exp is false
    do{
        simulateCode(node->child[0]);
    } while (!expSim(node->child[1]));
}
bool ifSim(TreeNode* node){//return true if condition is true or else part is Found
    int valid= expSim(node->child[0]);
    if(!valid){
        if(node->child[2]) {
            simulateCode(node->child[2]);
            return true;
        }
        else return false;
    }else {
        simulateCode(node->child[1]);
        return true;
    }
}
void simulateCode(TreeNode* node){//traverse Syntax tree
    int i=0;
    if(node->node_kind == IF_NODE) {
        int valid= ifSim(node);
        if(!valid)i=MAX_CHILDREN;
        else return;
    }
    else if(node->node_kind==READ_NODE) readSim(node->id);
    else if(node->node_kind==REPEAT_NODE) {
        RepeatSim(node);
        i=MAX_CHILDREN;
    }
    else if(node->node_kind==ASSIGN_NODE) assignSim(node);
    else if(node->node_kind==WRITE_NODE) writeSim(node);
    for(i;i<MAX_CHILDREN;i++) if(node->child[i]) simulateCode(node->child[i]);
    if(node->sibling) simulateCode(node->sibling);
}