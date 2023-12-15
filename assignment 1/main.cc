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
        if (input[input.size()-1]== '\n' || input[input.size()-1] == '\r'){
            token.createTokenizer(input, true);
        }
        else {
            token.createTokenizer(input, false);
        }
        token.add_application();

        // Pars the expression
        Parser *pars = new Parser();
        pars->expr(token);

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
        Tree->printTree();
        
        delete pars;
        delete Tree;
    }
    exit(0);
}

// Assingment 1
// all de onnodig commentaar weghalen
// Create the postfix array from the tokenarray. kan in een functie evt en dan ook functies private maken
// outputs a character string in a standard format to standard output
// this format may be explained in the README


// Veel haakjes?
//a ((((\x a)((b c))(\x d))
// a ((h (((\x a)((b c)))
// a ((((\x d)(\x a))((b c))

//Assignment 2: en 3
// assignment 3
// The program may accept multiple expressions, one per line.

// makefile uit assignment 1
// An archive (positive.tar.gz) of the positive examples used for testing.
// • An archive (negative.tar.gz) of the negative examples used for testing.

// vragen:
// destructor als ze memory leaks niet mogen zie tree.h


//private functions in parser!!!!! elke assignment
//make clean voor elke assignment

//uitleg still reachable memory leaks omdat exit 0 vs return 0

//cerr ipv cout