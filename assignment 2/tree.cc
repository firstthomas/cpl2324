#include "tree.h"

bool tree::findAppLambda(Node* walker){
    if (walker->T == APP && walker->left->T == SLASH){
        return true;
    }
    else if(walker->left != nullptr){
        walker = walker->left;
        return findAppLambda(walker);
    }
    else if(walker->right != nullptr){
        walker = walker->right;
        return findAppLambda(walker);
    }
    return false;
}


bool tree::bound(Node* walker, std::string var){
    if (walker->T == SLASH && walker->left->var == var){
        return true;
    }
    else if(walker->right != nullptr){
        walker = walker->right;
        return bound(walker, var);
    }
    return false;
}
//
bool tree::alphaReduce(Node* walker){

}

void tree::reduce(){
    Node* walker = begin;
    Node* walker2 = begin;
    bool possibleB = findAppLambda(walker);
    bool alphaReduced = true;
    std::cout << "possibleB:" << possibleB << std::endl;
    while(possibleB && alphaReduced){
        walker2 = walker;
        if (bound(walker2->left->right, walker2->right->var)){
            alphaReduced = alphaReduce(walker);
        }
        walker = begin;
        possibleB = findAppLambda(walker);
    }
}