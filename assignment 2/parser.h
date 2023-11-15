#ifndef PARSER_H
#define PARSER_H
#include "token.h"
#include "tree.h"


//Class used to pars the token string using recusive descent
class Parser{
    public:
    // Function that simulates the expr part of the LL grammar
    void expr(Tokenizer &token, Node* child);
    
    // Function that simulates the lexpr part of the LL grammar
    void lexpr(Tokenizer &token, Node* child);

    // Function that simulates the pexpr part of the LL grammar
    void pexpr(Tokenizer &token, Node* child);
    
    // Function that simulates the exprprime part of the LL grammar
    void exprprime(Tokenizer &token, Node* child);

    void copySubboom(Node* root, Node* temp);

    void insApp(Node* root);

    void helpDestructor(Node* temp) const;
};

#endif