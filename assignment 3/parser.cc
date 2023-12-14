#include "parser.h"

//Simulates the judgement part of the LL grammar by first calling expr and
// after that checking if the next token is : and calling type() if this is
// the case. Otherwise give an error.
void Parser::judge(Tokenizer &token){
    // std::cout << "judge " << std::endl;
    if (token.peek() == END){
        std::cout << "empty expression" << std::endl;
        exit(1);
    }
    expr(token);
    if (token.peek() == COLON){
        // std::cout << ": " << std::endl;
        colon = true;
        token.consume();
        type(token);
    }
    else{
        std::cout << "missing types" << std::endl;
        exit(1);
    }
}

// Calls the lexpr function and exprprime function.
void Parser::expr(Tokenizer &token) const{
    // std::cout << "expr" << std::endl;
    lexpr(token);
    exprprime(token);
}

// If the next element is a SLASH, use peek to check if the following element
// is a VARIABLE. Will fail if the element after the variable is END,
// otherwise call lexpr. Will also fail if theres no variable after the SLASH. 
// If no SLASH is found, call pexpr.
void Parser::lexpr(Tokenizer &token) const{
    // std::cout << "lexpr " << std::endl;
    if (token.peek() == SLASH){
        token.consume();
        if (token.peek() == VARIABLE){        
            token.consume();
            if (token.peek() == EXP){
                // std::cout << "voor ^ " << std::endl;
                token.consume();
                type(token);
                // std::cout << "na ^ " << std::endl;
            }
            else{
                std::cout << "missing ^ after lambda abstraction" << std::endl;
                exit(1);
            }
            if (token.peek() == END){
                std::cout << "missing expression after lambda abstraction" << std::endl;
                exit(1);
            }
            lexpr(token);
        }
        else{
            std::cout << "missing variable after slash" << std::endl;
            exit(1);
        }
    }
    else{   
        pexpr(token);
    }
}

// If next element is VARIABLE, consume. If next element is BRACKET_OPEN,
// consume and call expr. If the next element is neither of those, send
// error code.
void Parser::pexpr(Tokenizer &token) const{
    // std::cout << " pexpr " << std::endl;
    // std::cout << token.peek() << std::endl;
    if (token.peek() == VARIABLE){
        if (token.lowercase()){
            token.consume();
        }
        else{
            std::cout << "lvar does not start with a lowercase letter" << std::endl;
            exit(1);
        }
    }
    else if (token.peek() == BRACKET_OPEN){
        token.consume();
        expr(token);
    }
    else if (token.peek() == EXP || token.peek() == COLON || token.peek() == ARROW){
        std::cout << "invalid expression" << std::endl;
        exit(1);
    }
    else{
        std::cout << "missing expression after opening parenthesis" << std::endl;
        exit(1);
    }
}

// If at the end of the string return
// else call lexpr and expprime.
void Parser::exprprime(Tokenizer &token) const{
    // std::cout << "exprpime" << std::endl;
    if (token.peek() == END || token.peek() == COLON){
        return;
    }
    lexpr(token);
    exprprime(token);
}

void Parser::type(Tokenizer &token) const{
    // std::cout << "type " << std::endl;
    ptype(token);
    typeprime(token);
}

void Parser::ptype(Tokenizer &token) const{
    // std::cout << "ptype" << std::endl;
    if (token.peek() == VARIABLE){
        if (!token.lowercase()){
            token.consume();
        }
        else{
            std::cout << "uvar does not start with a uppercase letter" << std::endl;
            exit(1);
        }
    }
    else if (token.peek() == BRACKET_OPEN){
        token.consume();
        type(token);
    }
    else{
        std::cout << "Incorrect charachter after variable" << std::endl;
        exit(1);
    }
}

void Parser::typeprime(Tokenizer &token) const{
    // std::cout << "typeprime" << std::endl;
    if (token.peek() == END){
        return;
    }
    if (token.peek() == ARROW){
        token.consume();
        type(token);
    }
    else if (colon){
        std::cout << token.peek() << std::endl;
        std::cout << "Incorrect charachter after variable" << std::endl;
        exit(1);
    }
}