#include <fstream>
#include <sstream>
#include "parser.h"
#include "tree.h"

// Asks the user for 1 or more input expressions and reads it into a
// a string of tokens. Then parses the token string and returns output to 
// the standard output.
int main(int argc, char** argv){
    std::string input;
    std::string output;
    while (std::getline(std::cin, input)){
        Tokenizer token = Tokenizer();

        // Read the expression into a token array and add applications.
        if (input[input.size()-1] == '\n' || input[input.size()-1] == '\r'){
            token.createTokenizer(input, true);
        }
        else {
            token.createTokenizer(input, false);
        }
        token.add_application();

        // Parse the expression
        Parser *pars = new Parser();
        pars->expr(token);

        tree* Tree = new tree();

        // Create the postfix array from the tokenarray.
        token.createPostfixArray();

        // Builds the tree from the postfix array converted to a string
        Tree->readIn(token.arrToStringForTree());

        // Print the tree
        Tree->printTree();
        
        delete pars;
        delete Tree;
    }
    exit(0);
}