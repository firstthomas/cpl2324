#include <fstream>
#include <sstream>
#include "parser.h"
#include "tree.h"

// Asks the user for 1 or more input expressions and reads it into a
// a string of tokens. Then parses the token string and returns output to 
// the standard output. It then repeats these steps on its own output.
int main(int argc, char** argv){
    std::string input;
    std::string output;
    std::string filenaam;

    if (argc > 1){ // Checks if argument is given.
        filenaam = std::string(argv[1]);
    }
    else { // No argument.
        std::cerr << "No file name given" << std::endl;
        exit(1);
    }
   
    std::ifstream myFile (filenaam);
    std::getline(myFile, input);
    if (input == ""){
        std::cerr << "empty input" << std::endl;
        exit(1);
    }
    // Read the expression into a token array and add applications.
    Tokenizer token(input, true);
    token.add_application();

    // Pars the expression
    Parser *pars = new Parser();
    pars->expr(token);

    tree* Tree;
    Tree = new tree();

    // Create the postfix array from the tokenarray.
    token.createPostfixArray();

    // Builds the tree from the postfix array converted to a string
    Tree->readIn(token.arrToStringForTree());

    // Reduce the tree if possible
    Tree->reduce();

    // Print the tree
    Tree->printTree();

    myFile.close();
    delete pars;
    delete Tree;
    exit(0);
}