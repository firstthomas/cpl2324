#ifndef NODE_H
#define NODE_H
#include "token.h"
#include <iostream>

class Node {

    public:
    std::string var = "-1";
    Token* T; // Type van de token
    Node* left = nullptr; // Pointer naar de linker token in de tree.
    Node* right = nullptr; // Pointer naar de rechter token in de tree.

    Node(){};

    Node(Token* t){T = t;}

};

#endif