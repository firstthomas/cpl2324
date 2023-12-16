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
    void readIn(std::string input);

    // Reduces the abstract syntax tree with beta reduction(s) if possible.
    // Uses alpha conversions if necessary
    void reduce();

    // Print function which will call another function that will configure the output string.
    void printTree() const;
    
    private:

    Node* begin;// Root of the tree

    // Builds the tree using recursion.
    void createTree(Node* child, std::istringstream &iss);

    // Looks for an Application with Lambda as its left child in the subtree walker
    Node* findAppLambda(Node* walker, bool &found) const;

    // Reduces the abstract syntax tree with beta reduction(s) if possible.
    // Uses alpha conversions if necessary.
    bool betaReduce(Node* walker);

    // Copies the subtree with root child to the subtree with root temp.
    void copySubboom(Node* child, Node* temp) const;

    // Replaces every variable equal to var in the subtree with root walker by 
    // the subtree with root replaceWithTree.
    void replaceVarWithTree(Node* walker, std::string var, Node* replaceWithTree) const;

    // Returns true if replaceVar is somewhere in the subtree with root walker.
    void findFreeVar(Node* walker, std::vector<std::string> &alleVar) const;

    // Returns true if replaceVar is somewhere in the subtree with root walker.
    bool findReplaceVar(Node* walker, std::string replaceVar) const;

    // Applies alpha conversion if necessary
    void replaceFreeVar(Node* walker, std::vector<std::string> &alleVar, std::string replaceVar) const;

    // Stores all variables in the subtree with root walker into the vector freeVar.
    void findVar(Node* walker, std::vector<std::string> &freeVar) const;
    
    // Checks if both trees are equal.
    bool equal(Node* oldTree, Node* newTree) const;

    // Will recursively walk through the tree to determine the output. 
    // Will check for certain situations to decide to add parentheses or not. 
    void printInfix(Node* child, std::string &output) const;
};


#endif