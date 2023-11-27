#include <fstream>
#include <sstream>
#include "parser.h"
#include "node.h"
#include "tree.h"
using namespace std;

void arraycheck(Token tokenArray[], int array_size){
    for (int i = 0; i < array_size; i++){
        if(tokenArray[i].x == SLASH){
            cout << "/";
        }
        else if(tokenArray[i].x == BRACKET_OPEN){
            cout << "(";
        }
        else if(tokenArray[i].x == BRACKET_CLOSE){
            cout << ")";
        }
        else if(tokenArray[i].x == VARIABLE){
            cout << tokenArray[i].y;
        }
        else if(tokenArray[i].x == APP){
            cout << "@";
        }
        else if(tokenArray[i].x == END){
            cout << "END";
        }
    }
    std::cout << std::endl;
}

// void printTree(Node* child, std::string &finalTree){
//     finalTree += child->var;
//     if (child->left != nullptr){
//         printTree(child->left, finalTree);
//     }
//     if (child->right != nullptr){
//         printTree(child->right, finalTree);
//     }
// }


// Asks the user for 1 or more input expressions and reads it into a
// a string of tokens. Then parses the token string and returns output to 
// the standard output. It then repeats these steps on its own output.
int main(int argc, char** argv){
    std::string input;
    std::string output;
    std::string filenaam;
    std::string output2; // For parsing own output

    if (argc > 1){ // Checks if argument is given.
        filenaam = std::string(argv[1]);
    }
    else { // No argument.
        cout << "Enter file name." << endl;
        cin >> filenaam;
    }

    ifstream myFile (filenaam);
    getline(myFile, input);
    
    Tokenizer token(input, true);
    token.add_application();

    tree* Tree;
    Tree = new tree();

    Parser pars;
    pars.expr(token);

    token.swapSlashVar();
    token.reverseArray(token.tokenarray, token.array_size-1);
    token.infixToPostfix();
    token.reverseArray(token.postfix, token.postfixSize);

    Tree->readIn(token.arrToStringForTree());

    std::cout << "print1 :" <<std::endl;
    Tree->printTree();
    Tree->reduce();
    std:: cout << std::endl;

    std::cout << "print2 :" <<std::endl;
    Tree->printTree();
    // token.create_output(output);
    
    myFile.close();
    cout << output << endl;
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

//dit vindt ik teveel moeite:
//may support inernational variable names(unicode with lambda instead of \)


// void arraycheck(Tokenizer token){
//     for (int i = 0; i < token.array_size; i++){
//         cout << "token_type" << token.tokenarray[i].x << endl;
//     }
// }