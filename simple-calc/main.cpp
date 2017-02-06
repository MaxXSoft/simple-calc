#include <cstdio>

#include "global.h"
#include "lexer.h"
#include "parser.h"

const char *TipInput = " input > ";
const char *TipResult = "result > ";

void PrintCalcResult(Tok *AST) {
    if (AST == nullptr) return;
    fprintf(stderr, "%s%lf\n", TipResult, AST->Calc());
    delete AST;
}

void MainLoop(Parser &parser) {
    for (;;) {
        switch (parser.CurrentToken()) {
            case TokEOF: {
                PrintLn("end of file");
                return;
            }
            case TokNum: case '(': {
                PrintCalcResult(parser.ParseExpr());
                break;
            }
            case '?': {
                Print(TipInput);
                parser.GetNextToken();
                break;
            }
            default: {
                PrintLn("error(syntax): invalid input");
                parser.GetNextToken();
            }
        }
    }
}

int main(int argc, const char *argv[]) {
    PrintLn("");
    PrintLn("a simple expression calculator by MaxXing");
    PrintLn("based on a recursive descent parser");
    PrintLn("");
    Print(TipInput);

    Lexer lexer;
    Parser parser(lexer);
    
    parser.GetNextToken();
    MainLoop(parser);
    
    return 0;
}
