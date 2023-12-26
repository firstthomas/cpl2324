#ifndef NODE_H
#define NODE_H
#include "token.h"

class Node {

    public:
        std::string var; // variable string
        token_type T; // Token Type
        Node* left = nullptr; // Pointer to left child in the tree.
        Node* right = nullptr; // Pointer to right child in the tree.

    // Standaard constructor for a Node.
    Node(){
        this->var = "-1";
        this->left = nullptr;
        this->right = nullptr;
    };
    
    // "Constructor function" with input for a Node.
    void setNodeValues(const std::string str){
            this->var = str;
            if (str == "\\"){this->T = SLASH;}
            else if (str == "@"){this->T = APP;}
            else {this->T = VARIABLE;}
            this->left = nullptr;
            this->right = nullptr;
    };

};

#endif