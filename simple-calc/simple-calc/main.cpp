#include <cstdio>

#include "global.h"
#include "lexer.h"
#include "parser.h"

void PrintCalcResult(Tok *AST) {
    if (AST == nullptr) return;
    fprintf(stderr, "result > %lf\n", AST->Calc());
    delete AST;
}

void MainLoop(Parser parser) {
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
                Print(" input > ");
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

int main(int argc, char *argv[]) {
    PrintLn("");
    PrintLn("a simple expression calculator by MaxXing");
    PrintLn("based on a recursive descent parser");
    PrintLn("");
    Print(" input > ");

    Lexer lexer;
    Parser parser(lexer);
    
    parser.GetNextToken();
    MainLoop(parser);
    
    return 0;
}
