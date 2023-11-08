#include <iostream>
#include "parser.h"

// Calls the lexpr function and exprprime function.
void Parser::expr(Tokenizer &token, Node* child){
    // Tree->makeNextNode("APP");
    child->T = APP;
    child->left = new Node();
    lexpr(token, child->left);
    child->right = new Node();
    exprprime(token, child->right);
    if (child->right->T == BRACKET_OPEN){
        child->right = nullptr;
        Node* temp = child;
        child = child->left;
        delete temp;
    }
}

// If the next element is a SLASH, use peek to check if the following element
// is a VARIABLE. Will fail if the element after the variable is END,
// otherwise call lexpr. Will also fail if theres no variable after the SLASH. 
// If no SLASH is found, call pexpr.
void Parser::lexpr(Tokenizer &token, Node* child){
    if (token.peek() == SLASH){
        // Tree->makeNextNode("SLASH");
        child->T = SLASH;
        token.consume();
        if (token.peek() == VARIABLE){
            // Tree->makeNextNode(token.tokenarray[token.j].y);
            child->left = new Node();
            child->left->T = VARIABLE;
            child->left->var = token.tokenarray[token.j].y;
            token.consume();
            if (token.peek() == END){
                std::cout << "missing expression after lambda abstraction" << std::endl;
                exit(1);
            }
            child->right = new Node();
            lexpr(token, child->right);
        }
        else{
            std::cout << "missing variable after slash" << std::endl;
            exit(1);
        }
    }
    else{   
        pexpr(token, child);
    }
}

// If next element is VARIABLE, consume. If next element is BRACKET_OPEN,
// consume and call expr. If the next element is neither of those, send
// error code.
void Parser::pexpr(Tokenizer &token, Node* child){
    if (token.peek() == VARIABLE){
        // Tree->makeNextNode(token.tokenarray[token.j].y);
        child->T = VARIABLE;
        child->var = token.tokenarray[token.j].y;
        token.consume();
    }
    else if(token.peek() == BRACKET_OPEN){
        token.consume();
        expr(token, child);
    }
    else{
        std::cout << "missing expression after opening parenthesis" << std::endl;
        exit(1);
    }
}

// If at the end of the string return
// else call lexpr and expprime.
void Parser::exprprime(Tokenizer &token, Node* child){
    if(token.peek() == END){
        delete child;
        return;
    }
    lexpr(token, child);
    if (child->left != nullptr){
        child->left = new Node();
        exprprime(token, child->left);
    }
    else if (child->right != nullptr){
        child->right = new Node();
        exprprime(token, child->right);
        if (child->right->T == BRACKET_OPEN){
            child->right = nullptr;
        }
    }
    return;
}
