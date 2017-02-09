#include "lexer.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

#include "global.h"

const char *BinOps[] = {
    "**",
    // "!",
    "*", "/", "%",
    "+", "-",
    "<<", ">>",
    "&",
    "^", "|",
    "<=", "<", ">=", ">",
    "==", "!=" // , "="
};

const int BinOpPrec[] = {
    100,
    // 90,
    80, 80, 80,
    70, 70,
    60, 60,
    50,
    40, 40,
    30, 30, 30, 30,
    20, 20 // , 10
};

static bool IsBinOp(const char *TokTest) {
    for (const auto &CurBinOp : BinOps) {
        if (!strcmp(CurBinOp, TokTest)) {
            return true;
        }
    }
    return false;
}

static bool IsBinOp(int TokTest) {
    for (const auto &CurBinOp : BinOps) {
        if (CurBinOp[0] == TokTest) {
            return true;
        }
    }
    return false;
}

static int LexerError(const char *Description) {
    fprintf(stderr, "error(lexer): %s\n", Description);
    return TokErr;
}

int GetBinOpIndex(std::string Op) {
    int Len = GetArrayLength(BinOps);
    for (int i = 0; i < Len; ++i) {
        if (!strcmp(BinOps[i], Op.c_str())) {
            return i;
        }
    }
    return TokErr;
}

int Lexer::GetBinOpPrec() {
    int Len = GetArrayLength(BinOps);
    for (int i = 0; i < Len; ++i) {
        if (!strcmp(BinOps[i], BinOpStr.c_str())) {
            return BinOpPrec[i];
        }
    }
    return TokErr;
}

int Lexer::GetToken() {
    static int LastChar = ' ';     // static is important!!
    BinOpStr = "";
    
    while (isspace(LastChar)) LastChar = getchar();
    
    if (isdigit(LastChar) || LastChar == '.') {
        std::string NumStr;
        char *EndChar = nullptr;
        do {
            NumStr += LastChar;
            LastChar = getchar();
        } while (isdigit(LastChar) || LastChar == '.');
        NumVal = strtod(NumStr.c_str(), &EndChar);
        
        if (EndChar - NumStr.c_str() != NumStr.length())
            return LexerError("invalid floating constant");
        return TokNum;
    }
    
    if (IsBinOp(LastChar)) {
        BinOpStr = LastChar;
        do {
            LastChar = getchar();
            BinOpStr += LastChar;
        } while (IsBinOp(BinOpStr.c_str()));
        BinOpStr.pop_back();
        return TokOpr;
    }
    
    if (LastChar == EOF) return TokEOF;
    
    int CurChar = LastChar;
    LastChar = getchar();
    return CurChar;
}
