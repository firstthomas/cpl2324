#ifndef PARSER_H
#define PARSER_H
#include "token.h"


//Class used to pars the token string using recusive descent
class Parser{
    public:
    // Function that simulates the expr part of the LL grammar
    void expr(Tokenizer &token);
    
    // Function that simulates the lexpr part of the LL grammar
    void lexpr(Tokenizer &token);

    // Function that simulates the pexpr part of the LL grammar
    void pexpr(Tokenizer &token);
    
    // Function that simulates the exprprime part of the LL grammar
    void exprprime(Tokenizer &token);

};

#endif