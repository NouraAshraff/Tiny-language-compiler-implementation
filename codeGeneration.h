#ifndef CODE_GENERATION_CODEGENERATION_H
#define CODE_GENERATION_CODEGENERATION_H
#include "parser.h"
void readSim(const char*x);
int expSim(TreeNode* node);
void writeSim(TreeNode* node);
void assignSim(TreeNode* node);
void simulateCode(TreeNode* node);
void RepeatSim(TreeNode* node);
bool ifSim(TreeNode* node);
void simulateCode(TreeNode* node);
#endif //CODE_GENERATION_CODEGENERATION_H
