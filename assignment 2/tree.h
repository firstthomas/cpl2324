#ifndef TREE_H
#define TREE_H
#include "node.h"
#include <vector>

class tree{
    public:

    tree(){}

    // Nog goeide destructor maken zie ds of parser.cc
    ~tree(){delete begin;};

    void readIn(std::string input);

    void createTree(Node* child, std::istringstream &iss);

    void reduce();

    void printTree();

    void printInfix(Node* child, std::string &output);

    Node* begin;
    
    private:

    Node* findAppLambda(Node* walker, bool &found);

    Node* Bound(Node* walker, std::string var, bool &bound);

    bool betaReduce(Node* walker);

    void copySubboom(Node* child, Node* temp);

    void replaceVarWithTree(Node* walker, std::string var, Node* replaceWithTree);

    void findFreeVar(Node* walker, std::vector<std::string> &alleVar) const;

    bool findReplaceVar(Node* walker, std::string replaceVar) const;

    void replaceFreeVar(Node* walker, std::vector<std::string> &alleVar, std::string replaceVar) const;

    void findVar(Node* walker, std::vector<std::string> &freeVar) const;

    void copyTree(Node* oldTree, Node* newTree) const;

    bool equal(Node* oldTree, Node* newTree) const;
};


#endif