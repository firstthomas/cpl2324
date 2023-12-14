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

    // Copies the subtree with root child to the subtree with root temp.
    void copySubboom(Node* child, Node* temp) const;

    // Sets childs left vars type and childs Tokentype as arrow, child is a slash.
    void setTypes(Node* child);

    void checkTypes();

    // checks if the judgement in the tree is derivable in the type system
    void typeCheck(Node* child, bool left);

    // Checks if both trees are equal.
    bool equal(Node* oldTree, Node* newTree) const;

    // Returns if var is in child
    bool findVar(std::string var, Node* child) const;

    // Finds and sets the type of node child which is a variable.
    bool setType(Node* child, Node* finder, std::string var);

    // Print function which will call another function that will configure the output string.
    void printTree() const;

    Node* begin;// Root of the tree
    
    private:

    // Will recursively walk through the tree to determine the output. 
    // Will check for certain situations to decide to add parentheses or not. 
    void printInfix(Node* child, std::string &output) const;
};


#endif