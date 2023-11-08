#ifndef TREE_H
#define TREE_H
#include "node.h"

class tree{
    public:

    tree(){begin = new Node();}
    
    // tree(Token tokenarray[], int array_size);

    ~tree();

    // void createTree(Token tokenarray[], int &i, Node* child);

    // void makeNextNode(std::string str);

    Node* begin;

    private:

    // Token tokenarray[max_size];

};


#endif