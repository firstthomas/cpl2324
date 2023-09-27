#include <iostream>
#include <climits>
#include <string>
using namespace std;

const int max_size = 5000;

enum token_type { BRACKET_OPEN, BRACKET_CLOSE, VARIABLE, 
                  SLASH, WHITESPACE};

struct Token{
    token_type x;
    std::string y = "-1";
};

void tokenizer(std::string input, Token tokenarray[], int &array_size){
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
            while (input[i+1] != '(' && input[i+1] != ')' && input[i+1] != '\\' && input[i+1] != ' '){
                if ((input[i] > 64 && input[i] < 91) || (input[i] > 47 && input[i] < 58) || (input[i] > 96 && input[i] < 123)){
                    // cout << "var2" << endl;
                    i++;
                    cout << input[i] << endl;
                    tokenarray[k].y += input[i];
                }
                else {
                    cout << "Incorrect charachter input" << endl;
                    exit(1);
                }
            }
        }
        else {
        cout << "Incorrect charachter input" << endl;
        exit(1);
        }
        k++;
    }
    if (open_count != close_count){
        cout << "Amount of open brackets not equal to amount of closed brackets " << endl;
        exit(1);
    }
    array_size = k;
}

// void arraycheck(Token tokenArray[], int array_size){
//     for (int i = 0; i < array_size; i++){
//         cout << "token_type" << tokenArray[i].x << endl;
//         cout << "y" <<tokenArray[i].y << endl;
//     }
// }

int main(){
    std::string input;
    int array_size;
	getline(cin, input);
    Token tokenArray[max_size];
    tokenizer(input, tokenArray, array_size); 
    // arraycheck(tokenArray, input.size());
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