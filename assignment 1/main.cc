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
    // std::string filenaam;
    std::string output2;
    // if (argc > 1){ // Checks if argument is given.
    //     filenaam = std::string(argv[1]);
    // }
    // else { // No argument.
    //     // std::cout << "Enter file name." << std::endl;
    //     // std::cin >> filenaam;
    //     exit(1);
    // }
   
    // std::ifstream myFile (filenaam);
    // std::getline(myFile, input);

    // if (input == ""){
    //     exit(1);
    // }
    std::getline(std::cin, input);
    
    // Read the expression into a token array and add applications.
    Tokenizer token(input, false);
    token.add_application();
    
    // Pars the expression
    Parser pars;
    pars.expr(token);

    tree* Tree;
    Tree = new tree();

    // Create the postfix array from the tokenarray.
    token.swapSlashVar();
    token.reverseArray(token.tokenarray, token.arraySize-1);
    token.infixToPostfix();
    token.reverseArray(token.postfix, token.postfixSize);

    // Builds the tree from the postfix array converted to a string
    Tree->readIn(token.arrToStringForTree());

    // Print the tree
    std::string outputPrint1;
    Tree->printTree(outputPrint1);


    // Parsers own ouput and produce the result again
    Tokenizer token2(outputPrint1, false);
    token2.add_application();
    
    // Pars the expression
    Parser pars2;
    pars2.expr(token2);

    tree* Tree2;
    Tree2 = new tree();

    // Create the postfix array from the tokenarray.
    token2.swapSlashVar();
    token2.reverseArray(token2.tokenarray, token2.arraySize-1);
    token2.infixToPostfix();
    token2.reverseArray(token2.postfix, token2.postfixSize);

    // Builds the tree from the postfix array converted to a string
    Tree2->readIn(token2.arrToStringForTree());

    // Print the tree
    std::string outputPrint2;
    Tree2->printTree(outputPrint2);

    // myFile.close();
    exit(0);
}

// Assignment 1: ook bij assignment 3
// The program may accept multiple expressions, one per line.::

// 1.3.1 Positive examples
// The following examples are acceptable (the program must work if the program
// is invoked separately and supplied each expression, the program should accept
// multiple expressions each on its own line):

//README: student numbers, know defects or works correctly (defect is misschien dat er maximale grootte is ofzo)
//may include explanation of how the programs work
//may include positive.zip and negative.zip file
// outputs a character string in a standard format to standard output
// this format may be explained in the README

//Assignment 2:

// makefile uit assignment 1
// An archive (positive.tar.gz) of the positive examples used for testing.
// • An archive (negative.tar.gz) of the negative examples used for testing.

// vragen:
// destructor als ze memory leaks niet mogen zie tree.h


//private functions in parser!!!!! elke assignment