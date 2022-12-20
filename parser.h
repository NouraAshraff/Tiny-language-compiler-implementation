
#ifndef CODE_GENERATION_PARSER_H
#define CODE_GENERATION_PARSER_H
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "scanner.h"
using namespace std;

////////////////////////////////////////////////////////////////////////////////////
// Parser //////////////////////////////////////////////////////////////////////////

// program -> stmtseq
// stmtseq -> stmt { ; stmt }
// stmt -> ifstmt | repeatstmt | assignstmt | readstmt | writestmt
// ifstmt -> if exp then stmtseq [ else stmtseq ] end
// repeatstmt -> repeat stmtseq until expr
// assignstmt -> identifier := expr
// readstmt -> read identifier
// writestmt -> write expr
// expr -> mathexpr [ (<|=) mathexpr ]
// mathexpr -> term { (+|-) term }    left associative
// term -> factor { (*|/) factor }    left associative
// factor -> newexpr { ^ newexpr }    right associative
// newexpr -> ( mathexpr ) | number | identifier


// Used for debugging only /////////////////////////////////////////////////////////
extern const char* ExprDataTypeStr[];
extern const char* NodeKindStr[];


enum NodeKind{
    IF_NODE, REPEAT_NODE, ASSIGN_NODE, READ_NODE, WRITE_NODE,
    OPER_NODE, NUM_NODE, ID_NODE
};
enum ExprDataType {VOID, INTEGER, BOOLEAN};

#define MAX_CHILDREN 3
struct TreeNode
{
    TreeNode* child[MAX_CHILDREN];
    TreeNode* sibling; // used for sibling statements only
    NodeKind node_kind;

    union{TokenType oper; int num; char* id;}; // defined for expression/int/identifier only
    ExprDataType expr_data_type; // defined for expression/int/identifier only
    int line_num;

    TreeNode() ;
};
void throwError(CompilerInfo* compilerInfo ,string errorMessage);
struct ParseInfo
{
    Token next_token;
};

void Match(CompilerInfo* pci, ParseInfo* ppi, TokenType expected_token_type);

TreeNode* MathExpr(CompilerInfo*, ParseInfo*);

// newexpr -> ( mathexpr ) | number | identifier
TreeNode* NewExpr(CompilerInfo* pci, ParseInfo* ppi);

// factor -> newexpr { ^ newexpr }    right associative
TreeNode* Factor(CompilerInfo* pci, ParseInfo* ppi);

// term -> factor { (*|/) factor }    left associative
TreeNode* Term(CompilerInfo* pci, ParseInfo* ppi);

// mathexpr -> term { (+|-) term }    left associative
TreeNode* MathExpr(CompilerInfo* pci, ParseInfo* ppi);

// expr -> mathexpr [ (<|=) mathexpr ]
TreeNode* Expr(CompilerInfo* pci, ParseInfo* ppi);

// writestmt -> write expr
TreeNode* WriteStmt(CompilerInfo* pci, ParseInfo* ppi);

// readstmt -> read identifier
TreeNode* ReadStmt(CompilerInfo* pci, ParseInfo* ppi);

// assignstmt -> identifier := expr
TreeNode* AssignStmt(CompilerInfo* pci, ParseInfo* ppi);
TreeNode* StmtSeq(CompilerInfo*, ParseInfo*);

// repeatstmt -> repeat stmtseq until expr
TreeNode* RepeatStmt(CompilerInfo* pci, ParseInfo* ppi);

// ifstmt -> if exp then stmtseq [ else stmtseq ] end
TreeNode* IfStmt(CompilerInfo* pci, ParseInfo* ppi);

// stmt -> ifstmt | repeatstmt | assignstmt | readstmt | writestmt
TreeNode* Stmt(CompilerInfo* pci, ParseInfo* ppi);

// stmtseq -> stmt { ; stmt }
TreeNode* StmtSeq(CompilerInfo* pci, ParseInfo* ppi);

// program -> stmtseq
TreeNode* Parse(CompilerInfo* pci);

void PrintTree(TreeNode* node, int sh=0);
void DestroyTree(TreeNode* node);




#endif //CODE_GENERATION_PARSER_H
