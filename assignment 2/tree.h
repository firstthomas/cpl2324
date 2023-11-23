#ifndef TREE_H
#define TREE_H
#include "node.h"
#include <vector>

class tree{
    public:

    tree(){}

    ~tree(){delete begin;};

    void readIn(std::string input);

    void createTree(Node* child, std::istringstream &iss);

    void reduce();

    Node* begin;
    
    private:

    Node* findAppLambda(Node* walker, bool &found);

    Node* Bound(Node* walker, std::string var, bool &bound);

    Node* alphaConversion(Node* walker, bool &alphaConversed);

    bool betaReduce(Node* walker);
    // bool betaReduce(Node* walker);

    void replaceVarWithTree(Node* walker, std::string var, Node* replaceWithTree);

    void findFreeVar(Node* walker, std::vector<std::string> &alleVar) const;

    bool findReplaceVar(Node* walker, std::string replaceVar) const;

    void replaceFreeVar(Node* walker, std::vector<std::string> &alleVar, std::string replaceVar) const;

    void findVar(Node* walker, std::vector<std::string> &freeVar) const;

    void copyTree(Node* oldTree, Node* newTree) const;

    bool equal(Node* oldTree, Node* newTree) const;
};


#endif