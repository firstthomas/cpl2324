#include "tree.h"
#include "node.h"
#include <sstream>

// gaan er vanuit dat input klopt
void tree::readIn(std::string input){
    std::istringstream iss(input);
    begin = new Node();
    createTree(begin, iss);
}

// Bouwt de tree recusief op vanuit de root door
void tree::createTree(Node* child, std::istringstream &iss){
    std::string str;
    iss >> str;
    // std::cout << str << std::endl;
    // if (str.empty()){
    //     std::cout << "empty" << std::endl;
    //     return;
    // }
    delete child;
    child = new Node(str);
    if ((str[0] > 64 && str[0] < 91) || (str[0] > 96 && str[0] < 123)){
        // std::cout << "var" << std::endl;
        return;
    }
    child->left = new Node();
    createTree(child->left, iss);
    // child->var = str;
    // if (str.empty()){
    //     return;
    // }
    child->right = new Node();
    createTree(child->right, iss);
    // Token* temp = nullptr;
    // if (B){
    //     delete begin;
    //     begin = new Token(str);
    //     temp = begin;
    // }
    // else{
// Token* temp = new Token(str);
    // }
    // // if (str.empty()){
    // //     std::cout << "Missend kind" << std::endl;
    // //     return false;
    // // }
    // if (temp->T == WRONG){
    //     std::cout << "Incorrecte input" << std::endl;
    //     return false;
    // }
    // if (T && !B){
    //     child->left = temp;
    //     if (child->T == EXP && temp->T == EXP){
    //         std::cout << "Exponent met expressie niet toegestaan";
    //         std::cout << std::endl;
    //         return false;
    //     }
    // }
    // else if (!B){
    //     child->right = temp;
    //     if (child->T == EXP && temp->T != NUMBER){
    //         std::cout << "Exponent met expressie niet toegestaan";
    //         std::cout << std::endl;
    //         return false;
    //     }
    // }
    // if (temp->T == NUMBER){
    //     if (str == "pi"){
    //         temp->number = M_PI;
    //     }
    //     else {
    //         for (long unsigned int i = 1; i < str.length(); i++){
    //             if ((str[i] < 48 || str[i] > 57) && str[i] != 45 
    //                 && str[i] != 46){
    //                 std::cout << "Geen geldige input" << std::endl;
    //                 return false;
    //             } 
    //         }
    //         temp->number = std::atof(str.c_str());
    //     }
    // }
    // else if (temp->T == VARIABLE){
    //     temp->variable = str[0];
    //     if (str.length() > 1){
    //         std::cout << "Variable groter dan 1 karakter" << std::endl;
    //         return false;
    //     }
    // }
    // else if (temp->T == SIN || temp->T == COS){
    //     if (!createTree(temp, iss, false, false)){
    //         return false;
    //     }
    // }
    // else {
    //     if (!createTree(temp, iss, true, false)){
    //         return false;
    //     }
    //     if (!createTree(temp, iss, false, false)){
    //         return false;
    //     }
    // }
    // return true;
}


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
    int i = 0;
    while(possibleB && (alphaConversed || betaReduced) && i < 5){
        i++;
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