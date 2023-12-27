#include "tree.h"
#include <sstream>

// Deletes the Node temp and its childeren
void tree::helpDestructor(Node* temp) const{
    if (temp->left != nullptr){ 
        helpDestructor(temp->left);
    }
    if (temp->right != nullptr){
        helpDestructor(temp->right);
    }
    delete temp; // delete node
}

// Destructor
tree::~tree(){
    if (begin->left != nullptr){
        helpDestructor(begin->left);
    }
    if (begin->right != nullptr){
        helpDestructor(begin->right);
    }
    delete begin; // delete begin
}

// Constructor
tree::tree(){
    begin = new Node();
}

// Gets the expression as input in prefix notation. Assumes the expression
// is valid.
void tree::readIn(const std::string input){
    std::istringstream iss(input);
    createTree(begin, iss);
}

// Builds the tree using recursion.
void tree::createTree(Node* child, std::istringstream &iss){
    std::string str;
    iss >> str;
    child->setNodeValues(str);
    if ((str[0] >= 'A' && str[0] <= 'Z') || (str[0] >= 'a' && str[0] <= 'z')){
        return;
    }
    child->left = new Node();
    createTree(child->left, iss);
    child->right = new Node();
    createTree(child->right, iss);
}

// Print function which will call another function that will configure the output string.
void tree::printTree() const{
    std::string output;
    printInfix(begin, output);
    if (output.size() > 1 && begin->T != VARIABLE){
        output.pop_back();
        output.erase(0, 1);
    }
    std::cout << output << std::endl;
}

// Will recursively walk through the tree to determine the output. 
// Will check for certain situations to decide to add parentheses or not. 
void tree::printInfix(Node* child, std::string &output) const{
    // if (child->T == SLASH){
    //     output += "(";
    //     output += "\\";
    //     output += child->left->var;
    //     output += " ";
    // }
    // else if (child->T != APP){
    //     output += child->var;
    //     output += " ";
    // }

    // if (child->T != SLASH && child->left != nullptr){
    //     output += "(";
    //     printInfix(child->left, output);
    //     if (child->left->T == SLASH && child->left->right != nullptr &&
    //     child->left->right->T == APP){
    //         output+= ")";
    //     }
    // }

    // if (child->right != nullptr){
    //     if (child->right->T == APP){
    //         output += "(";
    //         printInfix(child->right, output);
    //     }
    //     else {
    //         printInfix(child->right, output);
    //         if (child->right->T == SLASH && child->right->right != nullptr
    //         && child->right->right->T == APP || child != begin && 
    //         child->right->T == SLASH){
    //             output += ")";
    //         }
    //     }
    //     if (output.back() == ' '){
    //         output.pop_back();
    //     }
    //     output += ")";
    if (child->T == SLASH){
        output += "(";
        output += "\\";
        output += child->left->var;
        output += " ";
        printInfix(child->right, output);
        output += ")";
    }
    else if (child->T == APP){
        output += "(";
        printInfix(child->left, output);
        if (output.back() != ')'){
            output += " ";
        }
        printInfix(child->right, output);
        output += ")";
    }
    else {
        output += child->var;
        // output += " ";
    }

//     if (child->T != SLASH && child->left != nullptr){
//         output += "(";
//         printInfix(child->left, output);
//         if (child->left->T == SLASH && child->left->right != nullptr &&
//         child->left->right->T == APP){
//             output+= ")";
//         }
//     }

//     if (child->right != nullptr){
//         if (child->right->T == APP){
//             output += "(";
//             printInfix(child->right, output);
//         }
//         else {
//             printInfix(child->right, output);
//             if (child->right->T == SLASH && child->right->right != nullptr
//             && child->right->right->T == APP || child != begin && 
//             child->right->T == SLASH){
//                 output += ")";
//             }
//         }
//         if (output.back() == ' '){
//             output.pop_back();
//         }
//         output += ")";
//     }
}