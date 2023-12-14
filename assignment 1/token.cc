#include "token.h"
#include <stack>

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
                    std::cout << "Incorrect character input" << std::endl;
                    exit(1);
                }
            }
        }
        else if(input[i] != '\n' && input[i] != '\r'){ // False input.
            std::cout << "Incorrect character input" << std::endl;
            exit(1);
        }
        k++;
    }
    if (open_count != close_count){ // Bracket_open not equal to Bracket_close.
        std::cout << "Amount of open brackets not equal to amount of closed brackets " << std::endl;
        exit(1);
    }
    //Mark the end of the array
    tokenarray[k].x = END;
    k++;
    arraySize = k;
}

// Inserts application at the position pos.
void Tokenizer::insert_application(int pos){
    if (tokenarray[pos].x != END){
        for (int i = arraySize; i > pos; i--){
            tokenarray[i] = tokenarray[i - 1];
        }
        tokenarray[pos].x = APP;
        tokenarray[pos].y = "-1";
        arraySize++;
    }
}

// Adds application to the array.
void Tokenizer::add_application(){
    int varCounter = 0;
    bool slash = false;
    int i = 0;
    while (tokenarray[i].x == BRACKET_OPEN){
        i++;
    }
    while(tokenarray[i].x != END && tokenarray[i].x != BRACKET_OPEN){
        while (tokenarray[i].x == BRACKET_OPEN){
            i++;
        }
        if(!slash && tokenarray[i].x == VARIABLE && tokenarray[i+1].x != END){
            while (tokenarray[i+1].x == BRACKET_CLOSE){
                i++;
            }
            insert_application(i+1);
        }
        else if(varCounter == 1 && slash && tokenarray[i].x != SLASH && tokenarray[i+1].x != END){
            varCounter = 0;
            while (tokenarray[i+1].x == BRACKET_CLOSE){
                i++;
            }
            insert_application(i+1);
            slash = false;
        }
        else if(tokenarray[i].x == SLASH){
            varCounter = 0;
            slash = true;
        }
        else if(tokenarray[i].x == VARIABLE){
            varCounter++;
        }
        i++;
        while (tokenarray[i].x == BRACKET_OPEN){
            i++;
        }
    }
}   


// This function is used to skip over elements equal to whitespaces and 
// closing brackets, returns the first element which is neither.
token_type Tokenizer::peek(){
    while (tokenarray[j].x == WHITESPACE || tokenarray[j].x == BRACKET_CLOSE 
           || tokenarray[j].x == APP){
        j++;
    }
    return tokenarray[j].x;
}

// Consumes the next token by adding 1 to the index.
void Tokenizer::consume(){
    j++;
}

// Reverses the array tokenArr with size Size.
void Tokenizer::reverseArray(Token tokenArr[], int Size){
    int start = 0;
    int end = Size-1;
    while (start < end){
        Token temp = tokenArr[start];
        tokenArr[start] = tokenArr[end];
        tokenArr[end] = temp;
        start++;
        end--;
    }
    for (int i = 0; i < Size; i++){
        if (tokenArr[i].x == BRACKET_OPEN){
            tokenArr[i].x = BRACKET_CLOSE;
        }
        else if (tokenArr[i].x == BRACKET_CLOSE){
            tokenArr[i].x = BRACKET_OPEN;
        }
    }
}
// Converts the tokenarray (infix) to the postfix array(postfix), using a
// stack.
void Tokenizer::infixToPostfix(){
    std::stack<Token> st;
    std::string element;
    int k = 0;
    for(int i = 0; i < arraySize; i++){
        if(tokenarray[i].x == VARIABLE){
            postfix[k] = tokenarray[i];
            k++;
        }
        else if(tokenarray[i].x == BRACKET_OPEN){
            st.push(tokenarray[i]);
        }
        else if(tokenarray[i].x == BRACKET_CLOSE){
            while (st.top().x != BRACKET_OPEN){
                postfix[k] = st.top();
                k++;
                st.pop();
            }
            st.pop();
        }
        else if(tokenarray[i].x == END){
            continue;
        }
        else{
            while(!st.empty() && st.top().x != BRACKET_OPEN && (
            (st.top().x == SLASH && tokenarray[i].x == SLASH)
            || (st.top().x == SLASH && tokenarray[i].x == APP))){
                postfix[k] = st.top();
                k++;
                st.pop();
            }
            st.push(tokenarray[i]);
        }
    }
    
    while(!st.empty()){
        postfix[k] = st.top();
        k++;
        st.pop();
    }
    postfixSize = k;
}

// Swaps every slash and the var directly after it.
void Tokenizer::swapSlashVar(){
    for (int i = 0; i < arraySize; i++){
        if (tokenarray[i].x == SLASH){
            Token temp = tokenarray[i];
            tokenarray[i] = tokenarray[i+1];
            tokenarray[i+1] = temp;
            i++;
        }
    }
}

// Converts the array back to a string.
std::string Tokenizer::arrToStringForTree() const{
    std::string str = "";
    for (int i = 0; i < postfixSize; i++){
        if (postfix[i].x == VARIABLE){
            str += postfix[i].y;
        }
        else if (postfix[i].x == SLASH){
            str += "\\";
        }
        else if (postfix[i].x == APP){
            str += "@";
        }
        str += " ";
    }
    return str;
}