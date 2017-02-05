#include "parser.h"

#include <cstdio>
#include <string>
#include <cmath>

#include "lexer.h"

Tok *ParserError(const char *Description) {
    fprintf(stderr, "error(parser): %s\n", Description);
    return nullptr;
}

double NumberTok::Calc() {
    return Val;
}

double BinTok::Calc() {
    double LVal = LHS->Calc();
    double RVal = RHS->Calc();
    int index = GetBinOpIndex(Op);
    
    switch (index) {
        case BOPow: return pow(LVal, RVal);
        case BOMult: return LVal * RVal;
        case BODiv: return LVal / RVal;
        case BOMod: return fmod(LVal, RVal);
        case BOAdd: return LVal + RVal;
        case BOSub: return LVal - RVal;
        case BOShL: return (long long)LVal << (long long)RVal;
        case BOShR: return (long long)LVal >> (long long)RVal;
        case BOAnd: return (long long)LVal & (long long)RVal;
        case BOXor: return (long long)LVal ^ (long long)RVal;
        case BOOr: return (long long)LVal | (long long)RVal;
        case BOLE: return LVal <= RVal;
        case BOLt: return LVal < RVal;
        case BOGE: return LVal >= RVal;
        case BOGt: return LVal > RVal;
        case BOEql: return LVal == RVal;
        case BONEql: return LVal != RVal;
        default: return 0;
    }
}

Tok *Parser::ParseExpr() {
    Tok *LHS = ParsePrimary();
    if (LHS == nullptr) return nullptr;

    return ParseBinOpRHS(0, LHS);
}

int Parser::GetNextToken() {
    return CurTok = TheLexer.GetToken();
}

Tok *Parser::ParseNumber() {
    Tok *Result = new NumberTok(TheLexer.GetNumVal());
    GetNextToken();
    return Result;
}

Tok *Parser::ParseParen() {
    GetNextToken();

    Tok *Inner = ParseExpr();
    if (Inner == nullptr) return nullptr;

    if (CurTok != ')') return ParserError("expected ')'");
    GetNextToken();

    return Inner;
}

Tok *Parser::ParsePrimary() {
    switch (CurTok) {
        case TokNum:
            return ParseNumber();
        case '(':
            return ParseParen();
        default:
            return ParserError("unknown token");
    }
}

Tok *Parser::ParseBinOpRHS(int OpPrec, Tok *LHS) {
    for (;;) {
        int TokPrec = TheLexer.GetBinOpPrec();
        if (TokPrec < OpPrec) return LHS;
        
        std::string BinOp = TheLexer.GetBinOp();
        GetNextToken();
        
        Tok *RHS = ParsePrimary();
        if (RHS == nullptr) return nullptr;
        
        int NextPrec = TheLexer.GetBinOpPrec();
        if (TokPrec < NextPrec) {
            RHS = ParseBinOpRHS(TokPrec + 1, RHS);
            if (RHS == nullptr) return nullptr;
        }
        
        LHS = new BinTok(BinOp, LHS, RHS);
    }
}
