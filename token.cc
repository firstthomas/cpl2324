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

void Tokenizer::hulpRecursie(int &i, int &var_counter){
    int j = i;
    do{
        i++;
    }
    while(tokenarray[i].x != VARIABLE);
    do{
        if (tokenarray[i].x == SLASH){
            hulpRecursie(i, var_counter);
            // cout << "1:" << i << endl;
            i--;
        }
        i++;
    }
    while(tokenarray[i].x != VARIABLE);
    i++;
    // cout << "2:" << i << endl;
    insert_bracket(j,i+1);
    // var_counter++;
    // cout << "3:" << i << endl;
}

void Tokenizer::create_output(std::string &output){
    //brackets verwijderen nog
    //(a) (b) spatie weghalen
    int var_counter = 0;
    int bracket_pos = 0;
    int j;
    for (int i = 0; i < array_size; i++){
        // cout << var_counter << "begin" << endl;
        if (var_counter > 2){
            var_counter = 2;
            if (tokenarray[i].x == BRACKET_CLOSE){
                insert_bracket(bracket_pos, i+1);
            }
            else{
                insert_bracket(bracket_pos, i-1); 
            }
            i++;
        }
        else if (tokenarray[i].x == WHITESPACE){
            continue;
        }
        // else if (tokenarray[i].x == BRACKET_OPEN && i == 0){
        //     var_counter = 0;
        //     bracket_pos = i;
        // }
        else if (tokenarray[i].x == BRACKET_CLOSE){
            var_counter--;
            // bracket_pos  = i+1;
        }
        else if (tokenarray[i].x == VARIABLE){
            var_counter++;
            // cout << "var " << var_counter << endl;
        }
        else if (tokenarray[i].x == SLASH){
            hulpRecursie(i, var_counter);
            // var_counter++;
            // j = i;
            // do{
            //     i++;
            // }
            // while(tokenarray[i].x != VARIABLE);
            // do{
            //     i++;
            // }
            // while(tokenarray[i].x != VARIABLE);
            // i++;
            // insert_bracket(j,i+1);
            // var_counter++;
            // continue;
        }
        else if (tokenarray[i].x == END){
            break;
        }
        // cout << "brackpos" << bracket_pos << endl;
        // cout << var_counter << endl;
    }
    arrToString(output);
}