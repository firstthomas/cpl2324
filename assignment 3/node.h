#ifndef NODE_H
#define NODE_H
#include "token.h"

class Node {

    public:
        std::string var; // variable string
        Node* type = nullptr; // Stores the type of this node if it is a variable
        token_type T; // Token Type
        Node* left = nullptr; // Pointer to left child in the tree.
        Node* right = nullptr; // Pointer to right child in the tree.
        Node* mid = nullptr;

    // Standaard constructor for a Node.
    Node(){
        this->var = "-1";
        this->left = NULL;
        this->right = NULL;
    };
    
    // Constructor with input for a Node.
    Node(std::string str){
            // std::cout << str << std::endl;
            this->var = str;
            if (str == "\\"){this->T = SLASH;}
            else if (str == "@"){this->T = APP;}
            else if (str == "-"){this->T = ARROW;}
            else if (str == "^"){this->T = EXP;}
            else if (str == ":"){this->T = COLON;}
            else{this->T = VARIABLE;}
            this->left = NULL;
            this->right = NULL;
    };

};

#endif