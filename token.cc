#include <iostream>
#include <climits>
#include <string>
#include "token.h"
using namespace std;


Tokenizer::Tokenizer(std::string input){
    int k = 0;
    int open_count = 0;
    int close_count = 0;
    for (int i = 0; i < input.size(); i++){
        // cout << input[i] << endl;
        if (input[i] == '(' ){
            // cout << "open bracket" << endl;
            tokenarray[k].x = BRACKET_OPEN;
            open_count++;
        }
        else if (input[i] == ')' ){
            // cout << "close bracket" << endl;
            tokenarray[k].x = BRACKET_CLOSE;
            close_count++;
        }
        else if (input[i] == '\\'){
            // cout << "slash" << endl;
            tokenarray[k].x = SLASH;
        }
        else if (input[i] == ' '){
            // cout << "space" << endl;
            tokenarray[k].x = WHITESPACE;
        }
        else if ((input[i] > 64 && input[i] < 91) || (input[i] > 47 && input[i] < 58) || (input[i] > 96 && input[i] < 123)){
            // cout << "var" << endl;
            tokenarray[k].x = VARIABLE;
            tokenarray[k].y = input[i];
            while (input[i+1] != '(' && input[i+1] != ')' && input[i+1] != '\\' && input[i+1] != ' ' && int(input[i+1]) != 0){
                if ((input[i+1] > 64 && input[i+1] < 91) || (input[i+1] > 47 && input[i+1] < 58) || (input[i+1] > 96 && input[i+1] < 123)){
                    // cout << "var2" << endl;
                    i++;
                    // cout << input[i] << endl;
                    tokenarray[k].y += input[i];
                }
                else {
                    // cout << input[i+1] << endl;
                    cout << "Incorrect charachter input" << endl;
                    exit(1);
                }
            }
        }
        else {
        cout << "Incorrect character input" << endl;
        exit(1);
        }
        k++;
    }
    if (open_count != close_count){
        cout << "Amount of open brackets not equal to amount of closed brackets " << endl;
        exit(1);
    }
    tokenarray[k].x = END;
    k++;
    array_size = k;
}

token_type Tokenizer::peek(){
    while (tokenarray[j].x == WHITESPACE || tokenarray[j].x == BRACKET_CLOSE){
        // cout << "Peek iteratie: " << j << endl;
        // cout << tokenarray[j].x << endl;
        j++;
    }
    // cout << "type: " << tokenarray[j].x << endl;
    return tokenarray[j].x;
}

void Tokenizer::consume(){//en hier ook spaties gelijk consumen?
    // while (tokenarray[j].x == WHITESPACE || tokenarray[j].x == BRACKET_CLOSE){
    //     cout << "Peek iteratie: " << j << endl;
    //     cout << tokenarray[j].x << endl;
    //     j++;
    // }
    j++;
}

// void arraycheck(Tokenizer token){
//     for (int i = 0; i < token.array_size; i++){
//         cout << "token_type" << token.tokenarray[i].x << endl;
//         cout << "y" <<token.tokenarray[i].y << endl;
//     }
// }


// int main(){
//     std::string input;
//     // int array_size;
// 	getline(cin, input);
//     // Token tokenArray[max_size];
//     Tokenizer token(input);
//     // token.consume();
//     // token.consume();
//     // cout << "hier" << endl;
//     // cout << token.peek() << endl;
//     // tokenizer(input, tokenArray, array_size); 
//     // arraycheck(token);
// }
// // zijn er nog meer dingen die wel al kunnen controleren in de tokenizer zoals de brackets
// // we kunnen hiervoor bij negative examples kijken // negative?
// // denk dat dit grotendeels voor de parser is // denk het ook ja
// // 1.3.2 Negative examples
// // The following examples are not acceptable:
// // • \ (missing variable after lambda)
// // • \x (missing expression after lambda abstraction)
// // • ((x (missing closing parenthesis)
// // • () (missing expression after opening parenthesis)
// // • a (b (missing closing parenthesis)
// // • a (b c)) (input string not fully parsed)


// // Java/C++ pseudocode
// // void expr(){mexpr();expr1();}
// // void expr1(){if(peek().tok == PLUS){consume();expr();}}
// // void mexpr(){pexpr();mexpr1();}
// // void mexpr1(){if(peek().tok == TIMES){consume();mexpr();}}
// // void pexpr(){if(peek().tok == PAREN){...}else{...}}