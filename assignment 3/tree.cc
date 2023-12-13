#include "tree.h"
#include <sstream>

// Gets the expression as input in prefix notation. Assumes the expression
// is valid.
void tree::readIn(std::string input){
    std::istringstream iss(input);
    std::string str;
    begin = new Node(":");
    begin->left = new Node();
    begin->right = new Node();
    iss >> str;
    createTree(begin->left, iss);
    // iss >> str;
    createTree(begin->right, iss);
}

// Builds the tree using recursion.
void tree::createTree(Node* child, std::istringstream &iss){
    std::string str;
    iss >> str;
    delete child;
    std::cout << "string in creatree" << str << std::endl;
    child = new Node(str);
    if (str == "-"){
        iss >> str;
    }
    if ((str[0] > 64 && str[0] < 91) || (str[0] > 96 && str[0] < 123)){
        return;
    }
    child->left = new Node();
    createTree(child->left, iss);
    if (str == "\\"){
        iss >> str;
        if (str == "^"){
            std::cout << "dakje" << std::endl;
            child->mid = new Node();
            createTree(child->mid, iss);
        }
        else if (str == "->"){
            std::cout << "dakje2 als het goed is nooit hier" << std::endl;
            child->mid = new Node("->");
            child->mid->left = new Node();
            child->mid->right = new Node();
            createTree(child->mid->left, iss);
            createTree(child->mid->right, iss);
        }
    }
    child->right = new Node();
    createTree(child->right, iss);
}

// Copies the subtree with root child to the subtree with root temp.
void tree::copySubboom(Node* child, Node* temp) const{
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

void tree::setTypes(Node* child){
    copySubboom(child->left->type, child->left);
    child->T = ARROW;
    child->var = "-";
}

void tree::typeCheck(Node* child, bool left){
    Node* parent;
    parent = child;
    if (left){
        child = child->left;
    }
    else{
        child = child->right;
    }
    if (child->T == SLASH){
        child->left->type = new Node();
        std::cout << "type mid " << child->mid->T << std::endl;
        copySubboom(child->mid, child->left->type);
        typeCheck(child, false);
        setTypes(child);
    }
    else if (child->T == APP){
        typeCheck(child, true);
        typeCheck(child, false);
        std::cout << child->left->T << std::endl;
        if (child->left->T == ARROW){
            if (equal(child->left->left, child->right)){
                Node* temp = new Node();
                copySubboom(child->left->right, temp);
                //hulpdestructor(child);
                if (left){
                    // parent->left = new Node();
                    parent->left = temp;
                }
                else{
                    // parent->right = new Node();
                    parent->right = temp;
                }
            }
            else{
                std::cout << "types do not match" << std::endl;
                //destructor(begin);
                exit(1);
            }
        }
        else if (child->right->T == ARROW){
            if (equal(child->right->left, child->left)){
                Node* temp = new Node();
                copySubboom(child->right->right, temp);
                //hulpdestructor(child);
                if (left){
                    // parent->left = new Node();
                    parent->left = temp;
                }
                else{
                    // parent->right = new Node();
                    parent->right = temp;
                }
            }
            else{
                std::cout << "types do not match" << std::endl;
                //destructor(begin);
                exit(1);
            }
        }
        // else{
        //     std::cout << "Unkown type?" << std::endl;
        //     //destructor(begin);
        //     exit(1);
        // }
    }
    else if (child->T == VARIABLE){
        std::string var = child->var;
        child->var += "!";
        if (!setType(child, begin->left, var)){
            // std::cout << "var" << child->var << std::endl;
            // std::cout << "mid" << parent->mid->var << std::endl;
            // std::cout << "Unkown type" << std::endl;
            //destructor
            exit(1);
        }
        copySubboom(child->type, child);
        std::cout << "type kind na copy van variable " << child->T << std::endl;
    }
}

bool tree::findVar(std::string var, Node* child) const{
    // std::cout << "findvar met var: " << var << "en child var" << child->var << std::endl;
    bool temp = false;
    if (child->T == VARIABLE){
        if (child->var == var){
            return true;
        }
        return false;
    }
    if (child->left != nullptr){
        temp = findVar(var, child->left);
    }
    if (!temp && child->right != nullptr){
        return findVar(var, child->right);
    }
    return temp;
}

bool tree::setType(Node* child, Node* finder, std::string var){
    bool temp = false;
    bool temp2 = false;
    if (finder->T == SLASH && (finder->left->var == var)){
        if (findVar(child->var, finder->right)){
            child->type = new Node();
            std::cout << finder->left->T << std::endl;
            copySubboom(finder->left->type, child->type);
            temp = true;
        }
        else{
            // std::cout << "false" << std::endl;
            return false;
        }
    }
    if (finder->left != nullptr){
        temp2 = setType(child, finder->left, var);
        // std::cout << "temp2 false?" << temp2 << std::endl;
        if (!temp2){
            temp2 = setType(child, finder->right, var);
        }
    }
    return (temp || temp2);
}


// Checks if both trees are equal.
// Uses recursion to walk through both trees.
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











// Print function which will call another function that will configure the output string.
void tree::printTree() const{
    std::string output;
    printInfix(begin, output);
    std::cout << output << std::endl;
}

// Will recursively walk through the tree to determine the output. 
// Will check for certain situations to decide to add parentheses or not. 
void tree::printInfix(Node* child, std::string &output) const{
    if (child->T == SLASH){
        output += "\\";
        output += child->left->var;
        output += " ";
    }
    else if (child->T != APP){
        output += child->var;
        output += " ";
    }

    if (child->T != SLASH && child->left != nullptr){
        printInfix(child->left, output);
    }

    if (child->right != nullptr){
        if (child->right->T == APP){
            output += "(";
            printInfix(child->right, output);
            if (output.back() == ' '){
                output.pop_back();
            }
            output += ")";
        }
        else {
            printInfix(child->right, output);
        }
    }
}