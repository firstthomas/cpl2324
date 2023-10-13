#include <iostream>
#include "parser.h"

void Parser::expr(Tokenizer &token){
    // cout << "lexpr" << endl;
    lexpr(token);
    // cout << "exprprime" << endl;
    exprprime(token);
}

void Parser::lexpr(Tokenizer &token){
    if (token.peek() == SLASH){
        token.consume();
        if (token.peek() == VARIABLE){
            token.consume();
            if (token.peek() == END){
                std::cout << "missing expression after lambda abstraction" << std::endl;
                exit(1);
            }
            // cout << "lexpr" << endl;
            lexpr(token);
        }
        else{
            std::cout << "missing variable after slash" << std::endl;
            exit(1);
        }
    }
    else{
        // cout << "pexpr" << endl;
        pexpr(token);
    }
}

void Parser::pexpr(Tokenizer &token){
    if (token.peek() == VARIABLE){
        token.consume();
    }
    else if(token.peek() == BRACKET_OPEN){
        token.consume();
        // cout << "expr" << endl;
        expr(token);
    }
    else{
        // cout << token.peek() << endl;
        std::cout << "missing expression after opening parenthesis" << std::endl; //geen idee of dit de goede error is
        exit(1);
    }
}

void Parser::exprprime(Tokenizer &token){
    if(token.peek() == END){
        // cout << "End of string" << endl;
        return;
    }
    // cout << "lexpr" << endl;
    lexpr(token);
    // cout << "exprprime" << endl;
    exprprime(token);
}
