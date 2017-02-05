#ifndef CALC_LEXER_H_
#define CALC_LEXER_H_

#include <string>

enum BinOpName {
    BOPow,
    // BONot,
    BOMult, BODiv, BOMod,
    BOAdd, BOSub,
    BOShL, BOShR,
    BOAnd,
    BOXor, BOOr,
    BOLE, BOLt, BOGE, BOGt,
    BOEql, BONEql // , BOLet
};

enum Token {
    TokErr = -1,
    TokEOF = -2,
    TokNum = -3,
    TokOpr = -4
};

int GetBinOpIndex(std::string Op);

class Lexer {
public:
	int GetBinOpPrec();
	int GetToken();

    double GetNumVal() { return NumVal; }
    std::string GetBinOp() { return BinOpStr; }

private:
	double NumVal;
	std::string BinOpStr;
};

#endif // CALC_LEXER_H_