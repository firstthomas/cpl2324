#include "tree.h"
#include "node.h"
#include <sstream>

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

// Looks for an Application with Lambda as its left child in the subtree 
// with root walker and sets found to true when this is found.
// Returns a pointer to parent of the Application or to begin if begin is
// an Application and begin->left is a lambda.
Node* tree::findAppLambda(Node* walker, bool &found){
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

// Copies the subtree with root child to the subtree with root temp.
void tree::copySubboom(Node* child, Node* temp){
    temp->T = child->T;
    temp->var = child->var;
    if (child->left != nullptr){
        temp->left = new Node();
        copySubboom(child->left, temp->left);
    }
    else{
        temp->left = nullptr;
    }
    if (child->right != nullptr){
        temp->right = new Node();
        copySubboom(child->right, temp->right);
    }
    else{
        temp->right = nullptr;
    }
}

// Replaces every variable equal to var in the subtree with root walker by 
// the subtree with root replaceWithTree.
void tree::replaceVarWithTree(Node* walker, std::string var, Node* replaceWithTree){
    // Booleans that are set to true if the left or right child were variables
    // before they were replaced.
    bool left = false;
    bool right = false;

    if (walker->left->var == var){
        // Performs the subtitution on walker->left
        copySubboom(replaceWithTree, walker->left);
        left = true;
    }
    if (walker->right->var == var){
        // Performs the subtitution on walker->right
        copySubboom(replaceWithTree, walker->right);
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

// Performs beta reduction on the subtree with root walker using if statments
// to determine what exactly has to happen and using replaceVarWithTree to
// perform the actual substitution.
bool tree::betaReduce(Node* walker){
    if (walker == begin && begin->T == APP && begin->left->T == SLASH){
        Node* walker2 = walker->left;
        std::string replaceVar = walker2->left->var;
        Node* replaceWithTree = walker->right;

        if (walker->left->right->T != VARIABLE){
            walker = walker->left->right;
            replaceVarWithTree(walker, replaceVar, replaceWithTree);
        }
        // When lambda's right child is a var equal to replaceVar it can be
        // replaced without replaceVarWithTree().
        else if (walker->left->right->var == replaceVar){
            copySubboom(replaceWithTree, walker->left);   
        }
        if (walker2->right != nullptr){
            begin = walker2->right;
        }
        else{
            begin = walker2;
        }
    }
    // Because the app lambda combination is not the begin we need to 
    // apply betaReduction in the middle of the tree and thus either the
    // left or right side of walker is the position of this combination.
    // So we check were this combination is and based on that we set walker
    // at the correct position to perform the reduction.
    // To maintain the correct structure we need the rembemer the pointer to
    // the root node of this subtree so that its left or right chidl can be
    // set to the correct node after the reduction has been performed.
    else{
        bool left = false;
        Node* begin2 = walker;
        if (walker->left->T == APP && walker->left->left->T == SLASH){
            walker = walker->left;
            left = true;
        }
        else{
            walker = walker->right;
        }

        Node* walker2 = walker->left;
        std::string replaceVar = walker2->left->var;
        Node* replaceWithTree = walker->right;

        if (walker->left->right->T != VARIABLE){
            walker = walker->left->right;
            replaceVarWithTree(walker, replaceVar, replaceWithTree);
        }
        else if (walker->left->right->var == replaceVar){
            copySubboom(replaceWithTree, walker->left);   
        }
        if (left){
            if (walker2->right != nullptr){
                begin2->left = walker2->right;
            }
            else{
                begin2->left = walker2;
            }
        }
        else{
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

// Reduces the abstract syntax tree with beta reduction(s) if possible.
// Uses alpha conversions if necessary.
void tree::reduce(){
    Node* walker = begin;
    //This becomes either the parent of the application or begin.
    Node* begin2 = nullptr;
    bool possibleB = false;
    bool betaReduced = true;
    int i = 0;

    walker = findAppLambda(walker, possibleB);

    while(possibleB && betaReduced && i < 1000){
        begin2 = walker;

        std::vector<std::string> allVar; // Reset the vector by redeclaring
        tree* temp;
        temp = new tree(); // tree used to check if the tree changed later on
        temp->begin = new Node();
        copyTree(begin, temp->begin);
        // Set walker on the application of the beta reduction
        if (walker != begin && walker->left->T == APP && walker->left->left->T == SLASH){
            walker = walker->left;
        }
        else if (walker != begin){
            walker = walker->right;
        }

        // Find all free variables and replace them if necessary (alpha conversion).
        findVar(walker->right, allVar);
        findFreeVar(walker->right, allVar);
        replaceFreeVar(walker->left, allVar, walker->left->left->var);
        
        betaReduced = betaReduce(begin2);
        if (equal(begin, temp->begin)){
            std::cout << "equal" <<std::endl;
            return;
        }

        // Reset walker and check if beta reduction is still possible
        possibleB = false;
        walker = begin;
        walker = findAppLambda(walker, possibleB);
        i++;
        delete temp;// Delete the tree
    }
    if (possibleB && i > 1000){
        std::cout << "Over 1000 reduction steps" <<std::endl;
        exit(2);
    }
} 

// Returns true if replaceVar is somewhere in the subtree with root walker.
bool tree::findReplaceVar(Node* walker, std::string replaceVar) const{
    if (walker->T == VARIABLE){
        if (walker->var == replaceVar){
            return true;
        }
        return false;
    }
    return (findReplaceVar(walker->left, replaceVar) || findReplaceVar(walker->right, replaceVar));
}

// For all variables in allVar, check if they are the left child of a lambda
// somewere in the subtree were in the right child of this lambda the variable
// replaceVar occurs and if so add "!" to the variable.
// (So only replace variables that would cause a free variable to be bound after
// beta reduction)
// The first function call is with walker as a pointer to the right child of an
// lambda for which beta reduction is performed. 
void tree::replaceFreeVar(Node* walker, std::vector<std::string> &allVar, std::string replaceVar) const{
    if (walker->T == SLASH && findReplaceVar(walker->right, replaceVar)){
        for (long long unsigned int i = 0; i < allVar.size(); i++){
            if (walker->left->var == allVar[i]){
                // walker->left->var = "w";
                walker->left->var = walker->left->var + "!";
                break;
            }
        }
    }
    if (walker->left != nullptr && walker->left->T != VARIABLE){
        replaceFreeVar(walker->left, allVar, replaceVar);
    }
    if (walker->right != nullptr && walker->right->T != VARIABLE){
        replaceFreeVar(walker->right, allVar, replaceVar);
    }
}

// For all variables in allVar, checks if they are free variables in the
// subtree with root walker. If a variable is not free and thus bound it is
// set to "-1" in the vecotr.
// The first function call is with walker as a pointer to the right child of an
// application for which beta reduction is performed.
void tree::findFreeVar(Node* walker, std::vector<std::string> &allVar) const{
    if (walker->T == SLASH){
        for (long long unsigned int i = 0; i < allVar.size(); i++){
            if (walker->left->var == allVar[i]){
                allVar[i] = "-1";
                break;
            }
        }
    }
    if (walker->left != nullptr && walker->left->T != VARIABLE){
        findFreeVar(walker->left, allVar);
    }
    if (walker->right != nullptr && walker->right->T != VARIABLE){
        findFreeVar(walker->right, allVar);
    }
}

// Stores all variables in the subtree with root walker into the vector freeVar.
// Only stores unique variables.
// The first function call is with walker as a pointer to the right child of an
// application for which beta reduction is performed.
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
    else{
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