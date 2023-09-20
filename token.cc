#include <iostream>
// #include <fstream>
using namespace std;

enum token_type { BRACKET_OPEN, BRACKET_CLOSE, VARIABLE, 
                  SLASH_LAMBDA, WHITESPACE};

struct Token{
    token_type x;
    std::string y = "-1";
};

void tokenizer(std::string input, struct Token tokenarray[]){
    for (int i = 0; i < input.size(); i++){
        if (input[i] == '(' ){
            tokenarray[i].x = BRACKET_OPEN;
        }
        else if (input[i] == ')' ){
            tokenarray[i].x = BRACKET_CLOSE;
        }
        else if (input[i] == 'λ' || input[i] == '\\'){
            tokenarray[i].x = SLASH_LAMBDA;
        }
        else if (input[i] == ' '){
            tokenarray[i].x = WHITESPACE;
        }
        else{
            tokenarray[i].x = VARIABLE;
            tokenarray[i].y = input[i];
            while (input[i] != '(' && input[i] != ')' && input[i] != 'λ' && input[i] == '\\' && input[i] != ' '){
                i++;
                tokenarray[i].y += input[i];
            }
        }
    }
}

int main(){
    std:string input;
    cin >> input;
    struct Token tokenArray[INT_MAX];
    tokenizer(input, tokenArray);
}