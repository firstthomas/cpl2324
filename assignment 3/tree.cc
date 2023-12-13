#include "tree.h"
#include <sstream>

// Gets the expression as input in prefix notation. Assumes the expression
// is valid.
void tree::readIn(std::string input){
    std::istringstream iss(input);
    std::string str;
    begin = new Node(":");
    begin->left = new Node();
    begin->right = new Node();
    iss >> str;
    createTree(begin->left, iss);
    // iss >> str;
    createTree(begin->right, iss);
}

// Builds the tree using recursion.
void tree::createTree(Node* child, std::istringstream &iss){
    std::string str;
    iss >> str;
    delete child;
    child = new Node(str);
    if (str == "-"){
        iss >> str;
    }
    if ((str[0] > 64 && str[0] < 91) || (str[0] > 96 && str[0] < 123)){
        return;
    }
    child->left = new Node();
    createTree(child->left, iss);
    if (str == "\\"){
        iss >> str;
        if (str == "^"){
            std::cout << "dakje" << std::endl;
            child->mid = new Node();
            createTree(child->mid, iss);
        }
        else if (str == "->"){
            std::cout << "dakje2 als het goed is nooit hier" << std::endl;
            child->mid = new Node("->");
            child->mid->left = new Node();
            child->mid->right = new Node();
            createTree(child->mid->left, iss);
            createTree(child->mid->right, iss);
        }
    }
    child->right = new Node();
    createTree(child->right, iss);
}

void tree::typeCheck(){
    
}












// Print function which will call another function that will configure the output string.
void tree::printTree() const{
    std::string output;
    printInfix(begin, output);
    std::cout << output << std::endl;
}

// Will recursively walk through the tree to determine the output. 
// Will check for certain situations to decide to add parentheses or not. 
void tree::printInfix(Node* child, std::string &output) const{
    if (child->T == SLASH){
        output += "\\";
        output += child->left->var;
        output += " ";
    }
    else if (child->T != APP){
        output += child->var;
        output += " ";
    }

    if (child->T != SLASH && child->left != nullptr){
        printInfix(child->left, output);
    }

    if (child->right != nullptr){
        if (child->right->T == APP){
            output += "(";
            printInfix(child->right, output);
            if (output.back() == ' '){
                output.pop_back();
            }
            output += ")";
        }
        else {
            printInfix(child->right, output);
        }
    }
}