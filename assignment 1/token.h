#ifndef TOKEN_H
#define TOKEN_H
#include <iostream>
#include <climits>
#include <string>

// maximum size of the array
const int maxSize = 5000;

// enum to give Tokens a classification
enum token_type { BRACKET_OPEN, BRACKET_CLOSE, VARIABLE, 
                  SLASH, WHITESPACE, APP, END};

// struct to store token type and if its a variable its contents
struct Token{
    token_type x;
    std::string y = "-1";
};

class Tokenizer{

    public:

    // Constructor
    Tokenizer(){};

    // Read the input string and stores it into the tokenarray as tokens
    void createTokenizer(std::string input, bool lastLine);
    
    // Peeks the next token
    token_type peek();

    // Consume the next token
    void consume();

    // Adds application to the array.
    void add_application();    

    // Reverses the array tokenArr with size Size.
    void reverseArray(Token tokenArr[], int Size);

    // Converts the tokenarray (infix) to the postfix array(postfix), using
    // a stack.
    void infixToPostfix();

    // Swaps every slash and the var directly after it.
    void swapSlashVar();

    // Converts the array back to a string.
    std::string arrToStringForTree() const;

    // Array in which characters are stored as tokens
    Token tokenarray[maxSize];

    // Array to store the postfix expression as tokens
    Token postfix[maxSize];

    int arraySize;// Stores the size of the token array

    int postfixSize;// Stores the size of the postfix array
    
    private:

    // Inserts application at the position pos.
    void insert_application(int pos);

    // Interger used for parsing as index to store the current position in 
    // the array
    int j = 0; 
};
#endif