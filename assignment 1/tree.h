#ifndef TREE_H
#define TREE_H
#include "node.h"
#include <vector>

class tree{
    public:

    tree(){}

    ~tree(){delete begin;};

    // Gets the expression as input in prefix notation. Assumes the expression
    // is valid.
    void readIn(std::string input);

    // Builds the tree using recursion.
    void createTree(Node* child, std::istringstream &iss);

    // Print function which will call another function that will configure the output string.
    void printTree(std::string &output) const;

    Node* begin;// Root of the tree
    
    private:
    
    // Will recursively walk through the tree to determine the output. 
    // Will check for certain situations to decide to add parentheses or not. 
    void printInfix(Node* child, std::string &output) const;
};


#endif