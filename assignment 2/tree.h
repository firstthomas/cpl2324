#ifndef TREE_H
#define TREE_H
#include "node.h"

class tree{
    public:

    tree(){}

    ~tree();

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
};


#endif