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
        // std::cout << "Enter file name." << std::endl;
        // std::cin >> filenaam;
        exit(1);
    }
   
    std::ifstream myFile (filenaam);
    std::getline(myFile, input);

    if (input == ""){
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
    token.swapSlashVar();
    token.reverseArray(token.tokenarray, token.arraySize-1);
    token.infixToPostfix();
    token.reverseArray(token.postfix, token.postfixSize);

    // Builds the tree from the postfix array converted to a string
    Tree->readIn(token.arrToStringForTree());

    Tree->reduce();
    // Print the tree
    Tree->printTree();
    
    myFile.close();
    delete pars;
    delete Tree;
    exit(0);
}



//README: student numbers, know defects or works correctly (defect is misschien dat er maximale grootte is ofzo)
//may include explanation of how the programs work

//may include positive.zip and negative.zip file

//tijd over:

//eigen output parsen werkt alleen de output moet nog () teoevoegen als nodig
//zoals hieronder staat uitgelegd
//If parsing is succesful, the output of the program must be again acceptable
// by the program to parse: the program then succesfully parses its own output and
// should produce the exact same result. The output should be an UNAMBIGUOUS
// expression, i.e. with sufficiently many parentheses inserted so the parser never
// applies any of the precedence rules. The output may use the least amount of
// whitespace and parentheses in its output.
// Geeft nu output alleen nog niet UNAMBIGUOUS
// outputs a character string in a standard format to standard output
// this format may be explained in the README
// dus x y z moet (x y) z als output en \x x y moet (\x x) y als output

// void arraycheck(Token tokenArray[], int array_size){
//     for (int i = 0; i < array_size; i++){
//         if(tokenArray[i].x == SLASH){
//             cout << "/";
//         }
//         else if(tokenArray[i].x == BRACKET_OPEN){
//             cout << "(";
//         }
//         else if(tokenArray[i].x == BRACKET_CLOSE){
//             cout << ")";
//         }
//         else if(tokenArray[i].x == VARIABLE){
//             cout << tokenArray[i].y;
//         }
//         else if(tokenArray[i].x == APP){
//             cout << "@";
//         }
//         else if(tokenArray[i].x == END){
//             cout << "END";
//         }
//     }
//     std::cout << std::endl;
// }

//Assignment 2:

// makefile uit assignment 1
// An archive (positive.tar.gz) of the positive examples used for testing.
// • An archive (negative.tar.gz) of the negative examples used for testing.

// vragen:
// destructor als ze memory leaks niet mogen zie tree.h

// // Deletes the Node temp and its childeren
// void Parser::helpDestructor(Node* temp) const{
//     if (temp->left != nullptr){ 
//         Node* left = temp->left;
//         helpDestructor(left);
//     }
//     if (temp->right != nullptr){
//         Node* right = temp->right;
//         helpDestructor(right);
//     }
//     delete temp; // delete node
// }

// met valgrind segfault? maar zonder niet

//readme!!!

// copy tree en copy subboom doen volgens mij hetzelfde

// mail over \x (\x (x x)) \x (\x (x x)) en hier memory leaks