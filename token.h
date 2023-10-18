#ifndef TOKEN_H
#define TOKEN_H
#include <iostream>
#include <climits>
#include <string>

// maximum size of the array
const int max_size = 5000;

// enum to give Tokens a classification
enum token_type { BRACKET_OPEN, BRACKET_CLOSE, VARIABLE, 
                  SLASH, WHITESPACE, END};

// struct to store token type and if its a variable its contents
struct Token{
    token_type x;
    std::string y = "-1";
};

class Tokenizer{

    public:
    // Read the input string and stores it into the tokenarray as tokens
    Tokenizer(std::string input, bool file);
    // Peeks the next token
    token_type peek();
    // Consume the next token
    void consume();
    // Inserts two bracket, one at bracket_pos and one at pos
    void insert_bracket(int bracket_pos, int pos);
    // Converts the array back to a string
    void arrToString(std::string &output);
    // Helps with inserting brackets at the correct position for lambda expressions
    void hulpRecursie(int &i, int &var_counter);
    // Creates output by inserting brackets
    void create_output(std::string &output);

    // Array in which character are stored as tokens
    Token tokenarray[max_size];
    int array_size;// Stores the size of the token array
    // Interger used as index to store the current position in the array
    int j = 0; 
};
#endif