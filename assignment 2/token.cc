#include "token.h"
using namespace std;

// Reads the string input and checks for each character's type to store the type in tokenarray.
// Also checks whether or not false input is given and if the amount of brackets-open are
// equal to the amount of brackets-close.
Tokenizer::Tokenizer(std::string input, bool file){
    int k = 0;
    int open_count = 0; //To keep count of bracket_open.
    int close_count = 0; // To keep count of bracket_close.
    int hulp;
    if (file){
        hulp = input.size() -1;
    }
    else {
        hulp = input.size();
    }
    for (int i = 0; i < hulp; i++){
        if (input[i] == '(' ){
            tokenarray[k].x = BRACKET_OPEN;
            open_count++;
        }
        else if (input[i] == ')' ){
            tokenarray[k].x = BRACKET_CLOSE;
            close_count++;
        }
        else if (input[i] == '\\'){
            tokenarray[k].x = SLASH;
        }
        else if (input[i] == ' '){
            k--;
            // If there is a space after another space it is not stored.
            // if (tokenarray[k-1].x != WHITESPACE){
            //     tokenarray[k].x = WHITESPACE;
            // }
            // else {
            //     k--;
            // }
        } // The following if statement checks if the characters is equal
          // to a-z or A-Z using ascii code. 
          // Here the variables of unknown length are tokenized.
        else if ((input[i] > 64 && input[i] < 91) || (input[i] > 96 && input[i] < 123)){
            tokenarray[k].x = VARIABLE;
            tokenarray[k].y = input[i];
            while (input[i+1] != '(' && input[i+1] != ')' && input[i+1] != '\\' && input[i+1] != ' ' && input[i+1] != '\n' && input[i+1] != '\r' && int(input[i+1] != 0)){
                if ((input[i+1] > 64 && input[i+1] < 91) || (input[i+1] > 47 && input[i+1] < 58) || (input[i+1] > 96 && input[i+1] < 123)){
                    i++;
                    tokenarray[k].y += input[i];
                }
                else { // False input.
                    cout << "Incorrect character1 input" << endl;
                    exit(1);
                }
            }
        }
        else if(input[i] != '\n' && input[i] != '\r'){ // False input.
            cout << "Incorrect character2 input" << endl;
            exit(1);
        }
        k++;
    }
    if (open_count != close_count){ // Bracket_open not equal to Bracket_close.
        cout << "Amount of open brackets not equal to amount of closed brackets " << endl;
        exit(1);
    }
    //Mark the end of the array
    tokenarray[k].x = END;
    k++;
    array_size = k;
}

void Tokenizer::insert_application(int pos){
    for (int i = array_size; i > pos; i--){
        tokenarray[i] = tokenarray[i - 1];
    }
    tokenarray[pos].x = APP;
    tokenarray[pos].y = "-1";
    array_size++;
}

void Tokenizer::add_application(){
    int varCounter = 0;
    bool slash = false;
    int i = 0;
    // for (int i = 0 < array_size; i++;){
    while(tokenarray[i].x != END){
        if(!slash && tokenarray[i].x == VARIABLE && tokenarray[i+1].x != END){//&&niet einde bv a
            if (tokenarray[i+1].x == BRACKET_CLOSE){
                insert_application(i+2);
            }
            else{
                insert_application(i+1);
            }
            // slash = false;
        }
        else if(tokenarray[i].x == SLASH){
            varCounter = 0;
            slash = true;
        }
        else if(varCounter == 1 && slash && tokenarray[i+1].x != SLASH && tokenarray[i+1].x != END){//&&niet einde bv \x a
            varCounter = 0;
            insert_application(i+1);
            slash = false;
        }
        else if(tokenarray[i].x == VARIABLE){
            varCounter++;
        }
        i++;
    }
}   


// This function is used to skip over elements equal to whitespaces and 
// closing brackets, returns the first element which is neither.
token_type Tokenizer::peek(){
    while (tokenarray[j].x == WHITESPACE || tokenarray[j].x == BRACKET_CLOSE){
        j++;
    }
    return tokenarray[j].x;
}

// Consumes the next token by adding 1 to the index.
void Tokenizer::consume(){
    j++;
}

// Inserts two brackets, one at bracket_pos and one at pos.
void Tokenizer::insert_bracket(int bracket_pos, int pos){
    // cout << array_size << endl;

    // This for-loop makes room for a bracket by placing all elements
    // after bracket_pos one place to the right.
    for (int i = array_size; i > bracket_pos; i--){
        // cout << i << endl;
        tokenarray[i] = tokenarray[i - 1];
    }
    tokenarray[bracket_pos].x = BRACKET_OPEN;
    tokenarray[pos].y = "-1";
    array_size++;

    // Same purpose as for-loop before this but bracket_pos is replaced
    // with pos.
    for (int i = array_size; i >= pos; i--){
        tokenarray[i] = tokenarray[i - 1];
    }
    tokenarray[pos].x = BRACKET_CLOSE;
    tokenarray[pos].y = "-1";
    array_size++;
}

// Converts the array back to a string.
void Tokenizer::arrToString(std::string &output){
    std::string previous = " "; // Used to remember the previous character.
    for (int i = 0; i < array_size; i++){
        if (tokenarray[i].x == WHITESPACE){
            // Don't print spaces when not necessary after brackets.
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
            // Space after \ not printed.
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

// Inserts brackets at the correct positions for lambda expressions.
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

// Decides where brackets need to be inserted by looking in the tokenarray.
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