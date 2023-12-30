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
   
    std::ifstream myFile(filenaam);

   
    while (std::getline(myFile, input)){
        if (input == ""){
            std::cerr << "empty input" << std::endl;
            exit(1);
        }
        Tokenizer token = Tokenizer();
        // Read the expression into a token array and add applications.
        if (input[input.size()-1]== '\n' || input[input.size()-1] == '\r'){
            token.createTokenizer(input, true);
        }
        else {
            token.createTokenizer(input, false);
        }

        token.add_application();

        // Pars the expression
        Parser *pars = new Parser();
        pars->judge(token);

        tree* Tree = new tree();

        // Create the postfix array from the tokenarray.
        token.createPostfixArray();

        // Builds the tree from the postfix array converted to a string
        Tree->readIn(token.arrToStringForTree());

        // call printTree() before changing the tree with checkTypes()
        Tree->printTree();

        // Check if types are correct
        Tree->checkTypes();
        // Print the tree
        std::cout << Tree->output << std::endl;

        delete pars;
        delete Tree;
    }
    myFile.close();
    exit(0);
}