#include <iostream>
#include <climits>
#include <string>
#include "token.h"
using namespace std;

// (\x((a) (b)))


class Parser{
    public:

    void expr(Tokenizer &token);
    void lexpr(Tokenizer &token);
    void pexpr(Tokenizer &token);
    void exprprime(Tokenizer &token);

};

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
        cout << token.peek() << endl;
        cout << "missing expression after opening parenthesis" << endl; //geen idee of dit de goede error is
        exit(1);
    }
}

void Parser::lexpr(Tokenizer &token){
    if (token.peek() == SLASH){
        token.consume();
        if (token.peek() == VARIABLE){
            token.consume();
            if (token.peek() == END){
                cout << "missing expression after lambda abstraction" << endl;
                exit(1);
            }
            // cout << "lexpr" << endl;
            lexpr(token);
        }
        else{
            cout << "missing variable after slash" << endl;
            exit(1);
        }
    }
    else{
        // cout << "pexpr" << endl;
        pexpr(token);
    }
}

void Parser::exprprime(Tokenizer &token){
    if(token.peek() == END){
        cout << "End of string" << endl;
        return;
    }
    // cout << "lexpr" << endl;
    lexpr(token);
    // cout << "exprprime" << endl;
    exprprime(token);
}

void Parser::expr(Tokenizer &token){
    // cout << "lexpr" << endl;
    lexpr(token);
    // cout << "exprprime" << endl;
    exprprime(token);
}


void arraycheck(Tokenizer token){
    for (int i = 0; i < token.array_size; i++){
        cout << "token_type" << token.tokenarray[i].x << endl;
    }
}


int main(){
    std::string input;
    // int array_size;
	getline(cin, input);
    // Token tokenArray[max_size];
    Tokenizer token(input);
    arraycheck(token);
    Parser pars;
    pars.expr(token);
    // tokenizer(input, tokenArray, array_size); 
    // arraycheck(token);
}
// zijn er nog meer dingen die wel al kunnen controleren in de tokenizer zoals de brackets
// we kunnen hiervoor bij negative examples kijken // negative?
// denk dat dit grotendeels voor de parser is // denk het ook ja
// 1.3.2 Negative examples
// The following examples are not acceptable:
// • \ (missing variable after lambda)
// • \x (missing expression after lambda abstraction)
// • ((x (missing closing parenthesis)
// • () (missing expression after opening parenthesis)
// • a (b (missing closing parenthesis)
// • a (b c)) (input string not fully parsed)


// Java/C++ pseudocode
// void expr(){mexpr();expr1();}
// void expr1(){if(peek().tok == PLUS){consume();expr();}}
// void mexpr(){pexpr();mexpr1();}
// void mexpr1(){if(peek().tok == TIMES){consume();mexpr();}}
// void pexpr(){if(peek().tok == PAREN){...}else{...}}
