#ifndef PARSER_H
#define PARSER_H
#include "token.h"


//Class used to pars the token string using recusive descent
class Parser{
    public:

    // Function that simulates the judgement part of the LL grammar
    void judge(Tokenizer &token);

    private:

    // Function that simulates the expr part of the LL grammar
    void expr(Tokenizer &token) const;
    
    // Function that simulates the lexpr part of the LL grammar
    void lexpr(Tokenizer &token) const;

    // Function that simulates the pexpr part of the LL grammar
    void pexpr(Tokenizer &token) const;
    
    // Function that simulates the exprprime part of the LL grammar
    void exprprime(Tokenizer &token) const;

    // Function that simulates the type part of the LL grammar
    void type(Tokenizer &token) const;

    // Function that simulates the ltype part of the LL grammar
    // void ltype(Tokenizer &token);

    // Function that simulates the ptype part of the LL grammar
    void ptype(Tokenizer &token) const;
    
    // Function that simulates the typeprime part of the LL grammar
    void typeprime(Tokenizer &token) const;

    // If we are on the right side of the colon the behaviour of the parser
    // is slightly different for the type part of the LL grammar
    bool colon = false;
};

#endif
