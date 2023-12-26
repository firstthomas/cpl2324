#include "parser.h"

// Calls the lexpr function and exprprime function.
void Parser::expr(Tokenizer &token) const{
    lexpr(token);
    exprprime(token);
}

// If the next element is a SLASH, use peek to check if the following element
// is a VARIABLE. Will fail if the element after the variable is END,
// otherwise call lexpr. Will also fail if theres no variable after the SLASH. 
// If no SLASH is found, call pexpr.
void Parser::lexpr(Tokenizer &token) const{
    if (token.peek() == SLASH){
        token.consume();
        if (token.peek() == VARIABLE){        
            token.consume();
            if (token.peek() == END){
                std::cerr << "missing expression after lambda abstraction" << std::endl;
                exit(1);
            }
            lexpr(token);
        }
        else {
            std::cerr << "missing variable after slash" << std::endl;
            exit(1);
        }
    }
    else {   
        pexpr(token);
    }
}

// If next element is VARIABLE, consume. If next element is BRACKET_OPEN,
// consume and call expr. If the next element is neither of those, send
// error code.
void Parser::pexpr(Tokenizer &token) const{
    if (token.peek() == VARIABLE){
        token.consume();
    }
    else if (token.peek() == BRACKET_OPEN){
        token.consume();
        expr(token);
    }
    else {
        std::cerr << "missing expression after opening parenthesis" << std::endl;
        exit(1);
    }
}

// If at the end of the string return
// else call lexpr and expprime.
void Parser::exprprime(Tokenizer &token) const{
    if (token.peek() == END){
        return;
    }
    lexpr(token);
    exprprime(token);
}