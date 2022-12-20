#ifndef CODE_GENERATION_SCANNER_H
#define CODE_GENERATION_SCANNER_H
#include <cstdio>
#include <cstring>
#include <string>



bool Equals(const char* a, const char* b);

bool StartsWith(const char* a, const char* b);

void Copy(char* a, const char* b, int n=0);

void AllocateAndCopy(char** a, const char* b);

#define MAX_LINE_LENGTH 10000

struct InFile
{
    FILE* file;
    int cur_line_num;
    char line_buf[MAX_LINE_LENGTH];
    int cur_ind, cur_line_size;

    InFile(const char* str);
    ~InFile();

    void SkipSpaces();

    bool SkipUpto(const char* str);

    bool GetNewLine();

    char* GetNextTokenStr();

    void Advance(int num);
};

struct OutFile
{
    FILE* file;
    OutFile(const char* str) ;
    ~OutFile();

    void Out(const char* s);
};


struct CompilerInfo
{
    InFile in_file;
    OutFile out_file;
    OutFile debug_file;

    CompilerInfo(const char* in_str, const char* out_str, const char* debug_str);
};

////////////////////////////////////////////////////////////////////////////////////
// Scanner /////////////////////////////////////////////////////////////////////////

#define MAX_TOKEN_LEN 40
extern const char* TokenTypeStr[];
enum TokenType{
    IF, THEN, ELSE, END, REPEAT, UNTIL, READ, WRITE,
    ASSIGN, EQUAL, LESS_THAN,
    PLUS, MINUS, TIMES, DIVIDE, POWER,
    SEMI_COLON,
    LEFT_PAREN, RIGHT_PAREN,
    LEFT_BRACE, RIGHT_BRACE,
    ID, NUM,
    ENDFILE, ERROR
};


struct Token
{
    TokenType type;
    char str[MAX_TOKEN_LEN+1];

    Token();
    Token(TokenType _type, const char* _str) ;
};

const Token reserved_words[]=
        {
                Token(IF, "if"),
                Token(THEN, "then"),
                Token(ELSE, "else"),
                Token(END, "end"),
                Token(REPEAT, "repeat"),
                Token(UNTIL, "until"),
                Token(READ, "read"),
                Token(WRITE, "write")
        };
const int num_reserved_words=sizeof(reserved_words)/sizeof(reserved_words[0]);

// if there is tokens like < <=, sort them such that sub-tokens come last: <= <
// the closing comment should come immediately after opening comment
const Token symbolic_tokens[]=
        {
                Token(ASSIGN, ":="),
                Token(EQUAL, "="),
                Token(LESS_THAN, "<"),
                Token(PLUS, "+"),
                Token(MINUS, "-"),
                Token(TIMES, "*"),
                Token(DIVIDE, "/"),
                Token(POWER, "^"),
                Token(SEMI_COLON, ";"),
                Token(LEFT_PAREN, "("),
                Token(RIGHT_PAREN, ")"),
                Token(LEFT_BRACE, "{"),
                Token(RIGHT_BRACE, "}")
        };
const int num_symbolic_tokens=sizeof(symbolic_tokens)/sizeof(symbolic_tokens[0]);

inline bool IsDigit(char ch);
inline bool IsLetter(char ch);
inline bool IsLetterOrUnderscore(char ch);

void GetNextToken(CompilerInfo* pci, Token* ptoken);

#endif //CODE_GENERATION_SCANNER_H
