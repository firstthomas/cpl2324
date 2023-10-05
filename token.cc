#include "token.h"
using namespace std;


Tokenizer::Tokenizer(std::string input){
    int k = 0;
    int open_count = 0;
    int close_count = 0;
    input_copy = input;
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
            //If there is a space after another space it is not stored
            if (tokenarray[k-1].x != WHITESPACE){
                tokenarray[k].x = WHITESPACE;
            }
            else {
                k--;
            }
        }
        else if ((input[i] > 64 && input[i] < 91) || (input[i] > 96 && input[i] < 123)){
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

void Tokenizer::insert_bracket(int bracket_pos, int pos){
    // cout << array_size << endl;
    for (int i = array_size; i > bracket_pos; i--){
        // cout << i << endl;
        tokenarray[i] = tokenarray[i - 1];
    }
    tokenarray[bracket_pos].x = BRACKET_OPEN;
    array_size++;
    for (int i = array_size; i >= pos; i--){
        tokenarray[i] = tokenarray[i - 1];
    }
    tokenarray[pos].x = BRACKET_CLOSE;
    array_size++;
}

void Tokenizer::arrToString(std::string &output){
    std::string previous = " ";
    for (int i = 0; i < array_size; i++){
        if (tokenarray[i].x == WHITESPACE){
            //hierdoor wordt er geen spatie geprint na ( en voor )
            //en geen spatie tussen )(
            if (previous != "(" && tokenarray[i+1].x != BRACKET_CLOSE && 
                previous != ")" && tokenarray[i+1].x != BRACKET_OPEN){
                output += " ";
            }
        }
        previous = " ";
        if (tokenarray[i].x == BRACKET_OPEN){
            output += "(";
            previous = "(";
        }
        else if (tokenarray[i].x == BRACKET_CLOSE){
            output += ")";
            previous = ")";
        }
        else if (tokenarray[i].x == VARIABLE){
            output += tokenarray[i].y;
        }
        else if (tokenarray[i].x == SLASH){
            output += "\\";
            //hierdoor wordt de evt spatie na een \ niet geprint
            if (tokenarray[i+1].x == WHITESPACE){
                i++;
            }
        }
        else if (tokenarray[i].x == END){
            break;
        }
    }
    output += "\n";
}

void Tokenizer::create_output(std::string &output){
    //brackets verwijderen nog
    //\x a \x b wordt ((\x a )\x) b moet dit niet (\x a)(\x b) worden?
    //application gaat goed
    //abstractoin totaal niet ^^
    //(a) (b) spatie weghalen
    int var_counter = 0;
    int bracket_pos = 0;
    for (int i = 0; i < array_size; i++){
        if (var_counter > 2){
            var_counter = 2;
            insert_bracket(bracket_pos, i-1);
            i++;
        }
        else if (tokenarray[i].x == WHITESPACE){
            continue;
        }
        else if (tokenarray[i].x == BRACKET_OPEN){
            var_counter = 0;
            bracket_pos = i;
        }
        else if (tokenarray[i].x == BRACKET_CLOSE){
            var_counter = 0;
            bracket_pos  = i+1;
        }
        else if (tokenarray[i].x == VARIABLE){
            var_counter++;
        }
        else if (tokenarray[i].x == SLASH){
            continue;
        }
        else if (tokenarray[i].x == END){
            break;
        }
    }
    arrToString(output);
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