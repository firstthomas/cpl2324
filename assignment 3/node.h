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
        // A node with type SLASH has a middle child that contains the type
        // of its variable (left child).
        Node* mid = nullptr; 

    // Standaard constructor for a Node.
    Node(){
        this->var = "-1";
        this->left = nullptr;
        this->right = nullptr;
        this->mid = nullptr;
        this->type = nullptr;
    };
    
    // "Constructor" with input for a Node.
    void setNodeValues(std::string str){
            this->var = str;
            if (str == "\\"){this->T = SLASH;}
            else if (str == "@"){this->T = APP;}
            else if (str[0] == '-'){this->T = ARROW;}
            else if (str == "^"){this->T = EXP;}
            else if (str == ":"){this->T = COLON;}
            else{this->T = VARIABLE;}
            this->left = nullptr;
            this->right = nullptr;
    };
    
    ~Node(){};
};

#endif