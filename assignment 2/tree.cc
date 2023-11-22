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

// Looks for an Application with Lambda as its left child.
Node* tree::findAppLambda(Node* walker, bool &found){
    if (walker->T == APP && walker->left->T == SLASH){
        found = true;
        return walker;
    }
    else if(walker->left != nullptr){
        walker = walker->left;
        return findAppLambda(walker, found);
    }
    else if(walker->right != nullptr){
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
    if (walker->T != SLASH && walker->left->var == var){
        // zet op walker->left
        copySubboom2(replaceWithTree, walker->left);
    }
    if (walker->right->var == var){
        // zet op walker->right
        copySubboom2(replaceWithTree, walker->right);
        return;
    }
    if (walker->right->T != VARIABLE){
        replaceVarWithTree(walker->right, var, replaceWithTree);
    }
    // if (walker->right->right != nullptr){
    //     replaceVarWithTree(walker->right, var, replaceWithTree);
    // }
}

bool tree::betaReduce(Node* walker){
    Node* walker2 = walker->left;
    std::cout << "betaReduce" <<std::endl;
    std::string replaceVar = walker->left->left->var;
    Node* replaceWithTree = walker->right;
    walker = walker->left;
    while(walker->right->T == SLASH){
        walker = walker->right;
    }
    replaceVarWithTree(walker, replaceVar, replaceWithTree);
    // std::cout << "replaced" <<std::endl;
    begin = walker2->right;
    // std::cout << "error?" <<std::endl;
    return true;
}

void tree::reduce(){
    Node* walker = begin;
    Node* walker2 = begin;
    bool possibleB = false;
    walker = findAppLambda(walker, possibleB);
    std::cout << "walker moet 5 zijn: " << walker->T << std::endl;
    bool alphaConversed = true;
    bool bound = false;
    bool betaReduced = true;
    if (possibleB){
        std::vector<std::string> alleVar;
        std::vector<std::string> freeVar;

        zoekVar(walker->right, alleVar);

        zoekFreeVar(walker->right, alleVar, false);
        // zoekVar(walker->left, alleVar);
        zoekFreeVar(walker->left, alleVar, true);
    }
    // int i = 0;
    while(possibleB && (alphaConversed || betaReduced)){// && i < 5){
        // i++;
        walker2 = walker;
        std::cout << "walker2 var moet y zijn: " << walker2->right->var << std::endl;
        std::cout << "walker2 links rechts moet 3 zijn: " << walker2->left->right->T << std::endl;
        walker2 = Bound(walker2->left->right, walker2->right->var, bound);
        std::cout << "bound:" << bound << std::endl;
        if (bound){
            walker2 = alphaConversion(walker2->left, alphaConversed);
            std::cout << "walker2 na alpha" <<std::endl;
            bound = false;
        }
        else{
            betaReduced = betaReduce(walker);
        }
        possibleB = false;
        walker = begin;
        std::cout << "waar1" <<std::endl;
        walker = findAppLambda(walker, possibleB);
        std::cout << "waar2" <<std::endl;
    }
    std::cout << "waar3" <<std::endl;
} 

void tree::zoekFreeVar(Node* walker, std::vector<std::string> &alleVar, bool left) const{
    if (walker->T == SLASH){
        for (long long unsigned int i = 0; i < alleVar.size(); i++){
            if (walker->left->var == alleVar[i]){
                if (left){
                    walker->left->var = "w";
                    std::cout << "test" << std::endl;
                }
                else {
                    alleVar[i] = "-1";
                    std::cout << "test3" << std::endl;
                }
                break;
            }
        }
    }
    if (walker->left != nullptr && walker->left->T != VARIABLE){
        zoekFreeVar(walker->left, alleVar, left);
    }
    if (walker->right != nullptr && walker->right->T != VARIABLE){
        zoekFreeVar(walker->right, alleVar, left);
    }
    // return alleVar;
}

void tree::zoekVar(Node* walker, std::vector<std::string> &freeVar) const{
    bool hulp = false;
    std::cout << "test4" << std::endl;
    if (walker->T == VARIABLE){
        for (long long unsigned int i = 0; i < freeVar.size(); i++){
            if (freeVar[i] == walker->var){
                hulp = true;
                break;
            }
        }
        if (!hulp){
        freeVar.push_back(walker->var);
        std::cout << "test2" << std::endl;
        }
    }
    else {
        zoekVar(walker->left, freeVar);
        zoekVar(walker->right, freeVar);
    }
}

// Eerst rechts van de application kijken welke variabelen free zijn
// Dan links kijken voor voor alle free variables dat ze niet links zijn van de lambda.
// Als ze links zijn van een lambda dan moeten we ze vervangen.

// Alle variabelen rechts zoeken en slaan we op in vector. 
// Dan voor elk linkerkind van een lambda kijken of die voorkomt in de vector. 
// Als het linkerkind voorkomt in de vector dan haal je m eruit. 