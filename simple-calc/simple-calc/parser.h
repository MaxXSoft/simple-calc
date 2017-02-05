#ifndef CALC_PARSER_H_
#define CALC_PARSER_H_

#include <string>

#include "lexer.h"

class Tok {
public:
    virtual ~Tok() {}
    virtual double Calc() = 0;
};

class NumberTok : public Tok {
public:
    NumberTok(double val) : Val(val) {}

    virtual double Calc();

private:
    double Val;
};

class BinTok : public Tok {
public:
    BinTok(std::string op, Tok *lhs, Tok *rhs) : Op(op), LHS(lhs), RHS(rhs) {}
    virtual ~BinTok() { delete LHS; delete RHS; }

    virtual double Calc();

private:
    std::string Op;
    Tok *LHS, *RHS;
};

class Parser {
public:
	Parser(Lexer theLexer) : TheLexer(theLexer) {}

	int GetNextToken();
	Tok *ParseExpr();

    int CurrentToken() { return CurTok; }

private:
	Tok *ParseNumber();
	Tok *ParseParen();
	Tok *ParsePrimary();
	Tok *ParseBinOpRHS(int OpPrec, Tok *LHS);

    Lexer TheLexer;
    int CurTok;
};

#endif