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

// alle:
// practical assignment files testen zie brightspace

// Assingment 1
// outputs a character string in a standard format to standard output
// this format may be explained in the README ook in assignment 2 en 3
// output 3 is anders


// Veel haakjes?
//a ((((\x a)((b c))(\x d))
// a ((h (((\x a)((b c)))
// a ((((\x d)(\x a))((b c))

// assignment 3

// An archive (positive.tar.gz) of the positive examples used for testing.
// • An archive (negative.tar.gz) of the negative examples used for testing.

// The program may accept multiple expressions, one per line.

//make clean voor elke assignment

//cerr ipv cout

//Assignment 2:

// An archive (positive.tar.gz) of the positive examples used for testing.
// • An archive (negative.tar.gz) of the negative examples used for testing.

//print!!!!!!
// \x (\x (x x)) \x (\x (x x)) print fout

//the program chooses an arbitrary place where reduction is performed.
// dit zouden we nog kunnen doen
// waarschijnlijk met nog een findAppLambda en dan random kiezen welke van de twee het wordt.