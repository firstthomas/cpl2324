#include <fstream>
#include <sstream>
#include "parser.h"
#include "tree.h"


void arraycheck(Token tokenArray[], int array_size){
    for (int i = 0; i < array_size; i++){
        if(tokenArray[i].x == SLASH){
            std::cout << "/";
        }
        else if(tokenArray[i].x == BRACKET_OPEN){
            std::cout << "(";
        }
        else if(tokenArray[i].x == BRACKET_CLOSE){
            std::cout << ")";
        }
        else if(tokenArray[i].x == VARIABLE){
            std::cout << tokenArray[i].y;
        }
        else if(tokenArray[i].x == APP){
            std::cout << "@";
        }
        else if(tokenArray[i].x == COLON){
            std::cout << ":";
        }
        else if(tokenArray[i].x == EXP){
            std::cout << "^";
        }
        else if(tokenArray[i].x == ARROW){
            std::cout << "->";
        }
        else if(tokenArray[i].x == END){
            std::cout << "END";
        }
        else{
            std::cout << "wrong" << std::endl;
        }
    }
    std::cout << std::endl;
}

void printTree(Node* child, std::string &finalTree, bool mid){
    finalTree += child->var;
    if (child->left != nullptr){
        printTree(child->left, finalTree, mid);
    }
    if (child->mid != nullptr && mid){
        printTree(child->mid, finalTree, mid);
    }
    if (child->right != nullptr){
        printTree(child->right, finalTree, mid);
    }
}

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
    Tokenizer *token = new Tokenizer(input, true);
    arraycheck(token->tokenarray, token->arraySize);
    token->add_application();
    arraycheck(token->tokenarray, token->arraySize);

    tree* Tree;
    Tree = new tree();

    // Pars the expression
    Parser *pars = new Parser();
    pars->judge(*token);

    // Create the postfix array from the tokenarray.
    token->swapSlashVar();
    token->reverseArray(token->tokenarray, token->arraySize-1);
    // std::cout << "infix reverse" << std::endl;
    // arraycheck(token.tokenarray, token.arraySize-1);
    token->infixToPostfix();
    // std::cout << "postfix" << std::endl;
    // arraycheck(token.postfix, token.postfixSize);
    token->reverseArray(token->postfix, token->postfixSize);
    // std::cout << "prefix" << std::endl;
    // arraycheck(token.postfix, token.postfixSize);

    // Builds the tree from the postfix array converted to a string
    Tree->readIn(token->arrToStringForTree());

    // Print the tree
    // std::cout << "tree" << std::endl;
    // std::string temp;
    // printTree(Tree->begin, temp, true);
    // std::cout << "tree: "<< temp;
    
    //print na typecheck moet zonder de mid
    // Tree->checkTypes();
    // std::cout << std::endl;
    std::string temp2;
    // printTree(Tree->begin, temp2, false);
    Tree->printTree(temp2);

    Tree->checkTypes();
    // Tree->typeCheck(Tree->begin, true);
    std::cout << temp2 << std::endl;
    myFile.close();
    delete token;
    delete pars;
    delete Tree;
    exit(0);
}



//README: student numbers, know defects or works correctly (defect is misschien dat er maximale grootte is ofzo)
//may include explanation of how the programs work

//tijd over:

//Assignment 2:

// makefile uit assignment 1
// An archive (positive.tar.gz) of the positive examples used for testing.
// • An archive (negative.tar.gz) of the negative examples used for testing.

//Assignment 3: missing types error, kan wss als er niks is na ^ ofzo
// typecheck functies enzo betere namen
// print functies
// ll grammar in readme
// type = ptype type'
// type' = -> type | empty
// ptype = uvar | (type)

// comments eruit