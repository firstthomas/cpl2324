#ifndef TREE_H
#define TREE_H
#include "node.h"

class tree{
    public:

    tree(){begin = new Node();}

    ~tree();

    void reduce();

    Node* begin;
    
    private:

    bool findAppLambda(Node* walker);

    bool bound(Node* walker, std::string var);

    bool alphaReduce(Node* walker);
};


#endif