#ifndef TREE_H
#define TREE_H
#include "node.h"

class tree{
    public:

    // Constructor
    tree();

    // Destructor, calls helpDestructor
    ~tree();

    // Help function for the destructor.
    void helpDestructor(Node* temp) const;

    // Gets the expression as input in prefix notation. Assumes the expression
    // is valid.
    void readIn(std::string input);

    // Builds the tree using recursion.
    void createTree(Node* child, std::istringstream &iss);

    // Copies the subtree with root child to the subtree with root temp.
    void copySubboom(Node* child, Node* temp) const;

    // Sets childs left vars type and childs Tokentype as arrow, child is a slash.
    void setTypes(Node* child);

    // Calls typeDerivCheck and checks if the left and right subtree are equal after
    // typeDerivCheck.
    void checkTypes();

    // Print function which will call another function that will configure the output string.
    void printTree();

    Node* begin;// Root of the tree

    std::string output; // Output string of the tree
    
    private:

    // checks if the judgement in the tree is derivable in the type system
    void typeDerivCheck(Node* child, bool left);

    // Checks if both trees are equal.
    bool equal(Node* oldTree, Node* newTree) const;

    // Returns if var is in child
    bool findVar(const std::string var, Node* child) const;

    // Finds and sets the type of node child which is a variable.
    bool setTypeVar(Node* child, Node* finder, const std::string var);

    // Will recursively walk through the tree to determine the output. 
    // Will check for certain situations to decide to add parentheses or not. 
    void printInfix(Node* child);
};


#endif