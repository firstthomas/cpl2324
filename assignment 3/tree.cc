#include "tree.h"
#include <sstream>

// Deletes the Node temp and its childeren
void tree::helpDestructor(Node* temp) const{
    std::cout << "hulp" << std::endl;
    if (temp->left != nullptr){ 
        Node* left = temp->left;
        helpDestructor(left);
    }
    if (temp->type != nullptr){
        Node* type = temp->type;
        helpDestructor(type);
    }
    if (temp->mid != nullptr){
        Node* mid = temp->mid;
        helpDestructor(mid);
    }
    if (temp->right != nullptr){
        Node* right = temp->right;
        helpDestructor(right);
    }
    std::cout << "hulp2" << std::endl;
    delete temp; // delete node
}

// Destructor
tree::~tree(){
    std::cout << "destructor" << std::endl;
    if (begin->left != nullptr){
        Node* left = begin->left;
        helpDestructor(left);
    }
    if (begin->type != nullptr){
        Node* type = begin->type;
        helpDestructor(type);
    }
    if (begin->mid != nullptr){
        Node* mid = begin->mid;
        helpDestructor(mid);
    }
    if (begin->right != nullptr){
        Node* right = begin->right;
        helpDestructor(right);
    }
    std::cout << "destructor2" << std::endl;
    delete begin;
}



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
    createTree(begin->right, iss);
}

// Builds the tree using recursion.
void tree::createTree(Node* child, std::istringstream &iss){
    std::string str;
    iss >> str;
    delete child;
    // std::cout << "string in creatree" << str << std::endl;
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

// Calls typeCheck and checks if the left and right subtree are equal after
// typeCheck.
void tree::checkTypes(){
    typeCheck(begin, true);
    if (!equal(begin->left, begin->right)){
        std::cout << "types do not match" << std::endl;
        exit(1);
    }
}

// This function gets called with child->T == SLASH. It copies the left
// childs types to the left child and sets the SLASH as an arrow.
void tree::setTypes(Node* child){
    copySubboom(child->left->type, child->left);
    child->T = ARROW;
    child->var = "->";
}

// Applies typeChecking to the left side of the tree by using recursion.
// Replaces every var for its type starting at the bottom. Replaces slashes
// for arrows by appling rule 3 of the type system. Applies rule 2 on
// applications. If any of the rules cannot be applied or a variable does
// not have a type this functions reports an error and exits the program.
// Because we sometimes need the parent to change the tree we give the parent
// node as argument and a bool to determine if we should check the left or
// right child.
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
        // std::cout << "type mid " << child->mid->T << std::endl;
        // std::cout << "var mid " << child->mid->var << std::endl;
        copySubboom(child->mid, child->left->type);
        // std::cout << "child left type t na copy slash" << child->left->type->T << std::endl;
        typeCheck(child, false);
        setTypes(child);
    }
    else if (child->T == APP){
        // std::cout << "application" << std::endl;
        typeCheck(child, true);
        typeCheck(child, false);
        std::cout << child->left->T << std::endl;
        if (child->left->T == ARROW){
            if (equal(child->left->left, child->right)){
                Node* temp = new Node();
                copySubboom(child->left->right, temp);
                helpDestructor(child);
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
        // else if (child->right->T == ARROW){
        //     if (equal(child->right->left, child->left)){
        //         Node* temp = new Node();
        //         copySubboom(child->right->right, temp);
        //         //hulpdestructor(child);
        //         if (left){
        //             // parent->left = new Node();
        //             parent->left = temp;
        //         }
        //         else{
        //             // parent->right = new Node();
        //             parent->right = temp;
        //         }
        //     }
        //     else{
        //         std::cout << "types do not match" << std::endl;
        //         //destructor(begin);
        //         exit(1);
        //     }
        // }
        else{
            std::cout << "Unkown type?" << std::endl;
            //destructor(begin);
            exit(1);
        }
    }
    else if (child->T == VARIABLE){
        std::string var = child->var;
        child->var += "!";
        // std::cout << "setype met var " << var << std::endl;
        if (!setType(child, begin->left, var)){
            // std::cout << "var" << child->var << std::endl;
            // std::cout << "mid" << parent->mid->var << std::endl;
            std::cout << "Unkown type for variable " << var << std::endl;
            //destructor
            exit(1);
        }
        copySubboom(child->type, child);
        // std::cout << "type kind na copy van variable " << child->T << std::endl;
    }
}

// Checks if var is in the subtree with root child.
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

// Sets the type of a variable. Child is the variable, finder the root of
// the tree we are searching in and var is the var we want to find the type of
bool tree::setType(Node* child, Node* finder, std::string var){
    bool temp = false;
    bool temp2 = false;
    if (finder->T == SLASH && (finder->left->var == var)){
        if (findVar(child->var, finder->right)){
            child->type = new Node();
            // std::cout << finder->left->type->T << std::endl;
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
    // if (child->T == SLASH){
    //     output += "\\";
    //     output += child->left->var;
    //     output += " ";
    // }
    // else if (child->T != APP){
    //     output += child->var;
    //     output += " ";
    // }

    // if (child->T != SLASH && child->left != nullptr){
    //     printInfix(child->left, output);
    // }

    // if (child->right != nullptr){
    //     if (child->right->T == APP){
    //         output += "(";
    //         printInfix(child->right, output);
    //         if (output.back() == ' '){
    //             output.pop_back();
    //         }
    //         output += ")";
    //     }
    //     else {
    //         printInfix(child->right, output);
    //     }
    // }
    bool bracket = false;
    if (child->T == COLON || child->T == SLASH || child->T == APP ||
        child->T == ARROW){
        bracket = true;
        output += "(";
    }
    if (child->T == SLASH){
        output += "\\";
        output += child->left->var;
        output += " ";
    }
    else if (child->T == APP){
        output += " ";
        if (child->left != nullptr){
            printInfix(child->left, output);
        }
    }
    else{
        if (child->left != nullptr){
            printInfix(child->left, output);
        }
        output += child->var;
    }
    if (child->right != nullptr){
        printInfix(child->right, output);
    }
    if (bracket){
        output += ")";
    }
}