#ifndef TREE_H
#define TREE_H
#include "node.h"
#include <vector>

class tree{
    public:

    // Constructor
    tree();

    // Destructor
    ~tree();

    // Help function for the destructor.
    void helpDestructor(Node* temp) const;

    // Gets the expression as input in prefix notation. Assumes the expression
    // is valid.
    void readIn(const std::string input);

    // Print function which will call another function that will configure the output string.
    void printTree() const;
    
    private:
    
    // Will recursively walk through the tree to determine the output. 
    // Will check for certain situations to decide to add parentheses or not. 
    void printInfix(Node* child, std::string &output) const;

    // Builds the tree using recursion.
    void createTree(Node* child, std::istringstream &iss);

    Node* begin;// Root of the tree
};


#endif