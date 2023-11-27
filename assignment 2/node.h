#ifndef NODE_H
#define NODE_H
#include "token.h"

class Node {

    public:
        std::string var;
        token_type T; // Type van de token
        Node* left = nullptr; // Pointer naar de linker token in de tree.
        Node* right = nullptr; // Pointer naar de rechter token in de tree.

    Node(){
        this->var = "-1";
        this->left = NULL;
        this->right = NULL;
    };
    
    Node(std::string str){
            this->var = str;
            if (str == "\\"){this->T = SLASH;}
            else if (str == "@"){this->T = APP;}
            else{this->T = VARIABLE;}
            this->left = NULL;
            this->right = NULL;
    };

};

#endif