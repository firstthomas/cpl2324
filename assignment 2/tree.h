#ifndef TREE_H
#define TREE_H
#include "node.h"

class tree{
    public:

    tree(Token tokenarray[], int array_size);

    ~tree();

    void createTree(Token tokenarray[], int &i, Node* child);

    private:

    // Token tokenarray[max_size];

    Node* begin;

};


#endif