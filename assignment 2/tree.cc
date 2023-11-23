#include "tree.h"
#include "node.h"
#include <sstream>

void printTree2(Node* child){
    std::cout << child->var << std::endl;
    if (child->left != nullptr){
        printTree2(child->left);
    }
    if (child->right != nullptr){
        printTree2(child->right);
    }
}




// Gets the expression as input in prefix notation. Assumes the expression
// is valid.
void tree::readIn(std::string input){
    std::istringstream iss(input);
    begin = new Node();
    createTree(begin, iss);
}

// Builds the tree using recursion.
void tree::createTree(Node* child, std::istringstream &iss){
    std::string str;
    iss >> str;
    delete child;
    child = new Node(str);
    if ((str[0] > 64 && str[0] < 91) || (str[0] > 96 && str[0] < 123)){
        return;
    }
    child->left = new Node();
    createTree(child->left, iss);
    child->right = new Node();
    createTree(child->right, iss);
}

// Looks for an Application with Lambda as its left child.
Node* tree::findAppLambda(Node* walker, bool &found){
    // if (walker->T == APP && walker->left->T == SLASH){
    //     found = true;
    //     return walker;
    // }
    // else if(walker->left != nullptr){
    //     walker = walker->left;
    //     return findAppLambda(walker, found);
    // }
    // else if(walker->right != nullptr){
    //     walker = walker->right;
    //     return findAppLambda(walker, found);
    // }
    // found = false;
    // return walker;
    Node* walker2 = walker;
    if (walker->T == VARIABLE){
        found = false;
        return walker;
    }
    if (walker == begin && walker->T == APP && walker->left->T == SLASH){
        found = true;
        return walker;
    }
    if (walker->left->T == APP && walker->left->left->T == SLASH){
        found = true;
        return walker;
    }
    if (walker->right->T == APP && walker->right->left->T == SLASH){
        found = true;
        return walker;
    }
    if(walker->left != nullptr && walker->left->T != VARIABLE){
        walker = walker->left;
        walker = findAppLambda(walker, found);
        if (found){
            return walker;
        }
    }
    walker = walker2;
    if(walker->right != nullptr && walker->right->T != VARIABLE){
        walker = walker->right;
        return findAppLambda(walker, found);
    }
    found = false;
    return walker;
}

// Checks if there is a variable in the left side of the Application that
// is bound to a lambda.
Node* tree::Bound(Node* walker, std::string var, bool &bound){
    // std::cout << "bound walker type "<< walker->T << std::endl;
    if (walker->T == SLASH && walker->left->var == var){
        bound = true;
        return walker;
    }
    else if(walker->right != nullptr){
        walker = walker->right;
        return Bound(walker, var, bound);
    }
    return walker;
}
//
Node* tree::alphaConversion(Node* walker, bool &alphaConversed){
    walker->var = "w";
    alphaConversed = true;
    return walker;
}

void copySubboom2(Node* child, Node* temp){
    temp->T = child->T;
    temp->var = child->var;
    if (child->left != nullptr){
        temp->left = new Node();
        copySubboom2(child->left, temp->left);
    }
    else{
        temp->left = nullptr;
    }
    if (child->right != nullptr){
        temp->right = new Node();
        copySubboom2(child->right, temp->right);
    }
    else{
        temp->right = nullptr;
    }
}

void tree::replaceVarWithTree(Node* walker, std::string var, Node* replaceWithTree){
    // Booleans that are set to true if the left or right child were variables
    // before they were replaced.
    bool left = false;
    bool right = false;
    // std::cout << "error?" <<std::endl;
    if (walker->left->var == var){//verandert
        // Performs the subtitution on walker->left
        copySubboom2(replaceWithTree, walker->left);
        left = true;
    }
    if (walker->right->var == var){
        // Performs the subtitution on walker->right
        copySubboom2(replaceWithTree, walker->right);
        right = true;
        return;
    }
    if (walker->left->T != VARIABLE && !left){
        replaceVarWithTree(walker->left, var, replaceWithTree);
    }
    if (walker->right->T != VARIABLE && !right){
        replaceVarWithTree(walker->right, var, replaceWithTree);
    }
}

bool tree::betaReduce(Node* walker){
    if (walker == begin && begin->T == APP && begin->left->T == SLASH){
        Node* walker2 = walker->left;
        std::string replaceVar = walker2->left->var;
        Node* replaceWithTree = walker->right;

        if (walker->left->right->T != VARIABLE){
            walker = walker->left->right;
            replaceVarWithTree(walker, replaceVar, replaceWithTree);
            // std::cout << "error2?" <<std::endl;
        }
        // When lambda's right child is a var equal to replaceVar it can be
        // replaced without replaceVarWithTree().
        else if (walker->left->right->var == replaceVar){
            copySubboom2(replaceWithTree, walker->left);   
        }
        if (walker2->right != nullptr){
            begin = walker2->right;
        }
        else{
            begin = walker2;
        }
    }
    // Dit commentaar klopt nog niet:
    // Because the app lambda combination is not the begin we need to 
    // apply betaReduction in the middle of the tree and thus
    // either the left or right side of walker is the position of this combination.
    // To maintain the correct structure we need the rembemer the pointer to this node.
    else {
        bool left = false;
        bool right = false;
        Node* begin2 = walker;
        if (walker->left->T == APP && walker->left->left->T == SLASH){
            walker = walker->left;
            left = true;
        }
        else {
            walker = walker->right;
            right = true;
        }

        Node* walker2 = walker->left;
        std::string replaceVar = walker2->left->var;
        Node* replaceWithTree = walker->right;

        if (walker->left->right->T != VARIABLE){
            walker = walker->left->right;
            replaceVarWithTree(walker, replaceVar, replaceWithTree);
        }
        else if (walker->left->right->var == replaceVar){
            copySubboom2(replaceWithTree, walker->left);   
        }
        if (left){
            if (walker2->right != nullptr){
                begin2->left = walker2->right;
            }
            else{
                begin2->left = walker2;
            }
        }
        else {
            if (walker2->right != nullptr){
                begin2->right = walker2->right;
            }
            else{
                begin2->right = walker2;
            }
        }
    }
    return true;
}

void tree::reduce(){
    Node* walker = begin;
    bool possibleB = false;
    walker = findAppLambda(walker, possibleB);
    Node* begin2 = walker;
    // std::cout << "walker moet 5 zijn: " << walker->T << std::endl;
    // std::cout << "possibleB: " << possibleB << std::endl;
    bool alphaConversed = true;
    bool bound = false;
    bool betaReduced = true;
    int i = 0;
    while(possibleB && (alphaConversed || betaReduced) && i < 1000){
        i++;
        std::vector<std::string> alleVar;
        tree* temp;
        temp = new tree();
        temp->begin = new Node();
        if (walker != begin && walker->left->T == APP && walker->left->left->T == SLASH){
            walker = walker->left;
        }
        else if (walker != begin){
            walker = walker->right;
        }
        copyTree(begin, temp->begin);
        // std::cout << "waar1" <<std::endl;
        findVar(walker->right, alleVar);
        // std::cout << "waar2" <<std::endl;
        findFreeVar(walker->right, alleVar);
        // std::cout << "waar3" <<std::endl;
        // zoekVar(walker->left, alleVar);
        replaceFreeVar(walker->left, alleVar, walker->left->left->var);
        // std::cout << "waar4" <<std::endl;
        betaReduced = betaReduce(begin2);
        walker = begin;
        // std::cout << "waar5" <<std::endl;
        if (equal(begin, temp->begin)){
            std::cout << "equal" <<std::endl;
            return;
        }
        possibleB = false;
        // std::cout << "waar5" <<std::endl;
        walker = findAppLambda(walker, possibleB);
        begin2 = walker;
        delete temp;
    }
    if (possibleB && i > 1000){
        std::cout << "Over 1000 reduction steps" <<std::endl;
        exit(2);
    }
} 

bool tree::findReplaceVar(Node* walker, std::string replaceVar) const{
    if (walker->T == VARIABLE){
        if (walker->var == replaceVar){
            return true;
        }
        return false;
    }
    return (findReplaceVar(walker->left, replaceVar) || findReplaceVar(walker->right, replaceVar));
}

void tree::replaceFreeVar(Node* walker, std::vector<std::string> &alleVar, std::string replaceVar) const{
    if (walker->T == SLASH && findReplaceVar(walker->right, replaceVar)){
        for (long long unsigned int i = 0; i < alleVar.size(); i++){
            if (walker->left->var == alleVar[i]){
                walker->left->var = "w";
                break;
            }
        }
    }
    if (walker->left != nullptr && walker->left->T != VARIABLE){
        replaceFreeVar(walker->left, alleVar, replaceVar);
    }
    if (walker->right != nullptr && walker->right->T != VARIABLE){
        replaceFreeVar(walker->right, alleVar, replaceVar);
    }
}

void tree::findFreeVar(Node* walker, std::vector<std::string> &alleVar) const{
    if (walker->T == SLASH){
        for (long long unsigned int i = 0; i < alleVar.size(); i++){
            if (walker->left->var == alleVar[i]){
                alleVar[i] = "-1";
                break;
            }
        }
    }
    if (walker->left != nullptr && walker->left->T != VARIABLE){
        findFreeVar(walker->left, alleVar);
    }
    if (walker->right != nullptr && walker->right->T != VARIABLE){
        findFreeVar(walker->right, alleVar);
    }
}

void tree::findVar(Node* walker, std::vector<std::string> &freeVar) const{
    bool hulp = false;
    if (walker->T == VARIABLE){
        for (long long unsigned int i = 0; i < freeVar.size(); i++){
            if (freeVar[i] == walker->var){
                hulp = true;
                break;
            }
        }
        if (!hulp){
        freeVar.push_back(walker->var);
        }
    }
    else {
        findVar(walker->left, freeVar);
        findVar(walker->right, freeVar);
    }
}

// Copies the Node oldTree and all its children to the Node newTree.
void tree::copyTree(Node* oldTree, Node* newTree) const{
    newTree->T = oldTree->T;
    newTree->var = oldTree->var;
    if (oldTree->left != nullptr){
        newTree->left = new Node();
        copyTree(oldTree->left, newTree->left);
    }
    if (oldTree->right != nullptr){
        newTree->right = new Node();
        copyTree(oldTree->right, newTree->right);
    }
}

// Checks if both trees are equal.
bool tree::equal(Node* oldTree, Node* newTree) const{
    bool equalTrees = true;
    if (oldTree->T != newTree->T || oldTree->var != newTree->var){
        return false;
    }
    if (oldTree->left != nullptr){
        if (newTree->left != nullptr){
            equalTrees = equal(oldTree->left, newTree->left);
        }
        else{
            return false;
        }
    }
    if (oldTree->right != nullptr && equalTrees){
        if (newTree->right != nullptr){
            equalTrees = equal(oldTree->right, newTree->right);
        }
        else{
            return false;
        }
    }
    return equalTrees;
}