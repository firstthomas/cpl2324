#ifndef PARSER_H
#define PARSER_H
#include "token.h"

class Parser{
    public:

    void expr(Tokenizer &token);
    void lexpr(Tokenizer &token);
    void pexpr(Tokenizer &token);
    void exprprime(Tokenizer &token);

};

#endif