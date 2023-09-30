#include <iostream>
#include <climits>
#include <string>

const int max_size = 5000;

enum token_type { BRACKET_OPEN, BRACKET_CLOSE, VARIABLE, 
                  SLASH, WHITESPACE, END};

struct Token{
    token_type x;
    std::string y = "-1";
};

class Tokenizer{

    public:

    // enum token_type { BRACKET_OPEN, BRACKET_CLOSE, VARIABLE, 
    //               SLASH, WHITESPACE};

    // struct Token{
    //     token_type x;
    //     std::string y = "-1";
    // };
    Tokenizer(std::string input);

    token_type peek();

    void consume();

    void create_output(std::string &output);

    Token tokenarray[max_size];
    int array_size;
    int j = 0;
    std::string input_copy;
};