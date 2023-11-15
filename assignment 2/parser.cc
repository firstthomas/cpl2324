#include <iostream>
#include "parser.h"


// Deletes the Node temp and its childeren
void Parser::helpDestructor(Node* temp) const{
    if (temp->left != nullptr){ 
        Node* left = temp->left;
        helpDestructor(left);
    }
    if (temp->right != nullptr){
        Node* right = temp->right;
        helpDestructor(right);
    }
    delete temp; // delete node
}


// Copies child to temp
void Parser::copySubboom(Node* child, Node* temp){
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

// Inserts an appllication above the root
void Parser::insApp(Node* root){
    Node* temp = new Node();
    temp->T = APP;
    temp->left = new Node();
    copySubboom(root, temp->left);
    // std::cout << "hier2" << std::endl;
    helpDestructor(root->left);
    helpDestructor(root->right);
    copySubboom(temp, root);
    // root = temp;
    //nog destructor hier?
}

// Calls the lexpr function and exprprime function.
void Parser::expr(Tokenizer &token, Node* child){
    // std::cout << "expr" << std::endl;
    // Tree->makeNextNode("APP");
    child->T = APP;
    child->left = new Node();
    lexpr(token, child->left);
    child->right = new Node();
    exprprime(token, child->right);
    if(token.peek() != END){
        insApp(child);
        child->right = new Node();
        // std::cout << "voorexprprime" << std::endl;
        exprprime(token, child->right);
    }
    if (child->right->T == BRACKET_OPEN && token.peek() != END){
        // std::cout << "niet hier" << std::endl;
        token_type temp1 = token.peek();
        // std::cout << "x: " << temp1 << "y: " << temp1 <<std::endl;
        Node* temp = new Node();
        copySubboom(child->left, temp);
        //nog destructor maken
        // helpDestructor(child->left);
        // helpDestructor(child->right);
        copySubboom(temp, child);
    }
}

// If the next element is a SLASH, use peek to check if the following element
// is a VARIABLE. Will fail if the element after the variable is END,
// otherwise call lexpr. Will also fail if theres no variable after the SLASH. 
// If no SLASH is found, call pexpr.
void Parser::lexpr(Tokenizer &token, Node* child){
    // std::cout << "lexpr" << std::endl;
    if (token.peek() == SLASH){
        child->T = SLASH;
        token.consume();
        if (token.peek() == VARIABLE){
            child->left = new Node();
            child->left->T = VARIABLE;
            child->left->var = token.tokenarray[token.j].y;
            token.consume();
            if (token.peek() == END){
                std::cout << "missing expression after lambda abstraction" << std::endl;
                exit(1);
            }
            child->right = new Node();
            lexpr(token, child->right);
        }
        else{
            std::cout << "missing variable after slash" << std::endl;
            exit(1);
        }
    }
    else{   
        pexpr(token, child);
    }
}

// If next element is VARIABLE, consume. If next element is BRACKET_OPEN,
// consume and call expr. If the next element is neither of those, send
// error code.
void Parser::pexpr(Tokenizer &token, Node* child){
    // std::cout << "pexpr" << std::endl;
    if (token.peek() == VARIABLE){
        // Tree->makeNextNode(token.tokenarray[token.j].y);
        child->T = VARIABLE;
        child->var = token.tokenarray[token.j].y;
        token.consume();
    }
    else if(token.peek() == BRACKET_OPEN){
        token.consume();
        expr(token, child);
    }
    else{
        std::cout << "missing expression after opening parenthesis" << std::endl;
        exit(1);
    }
}

// If at the end of the string return
// else call lexpr and expprime.
void Parser::exprprime(Tokenizer &token, Node* child){
    // std::cout << "exprprime" << std::endl;
    if(token.peek() == END){
        std::cout << "end" << std::endl;
        delete child;
        return;
    }
    lexpr(token, child);
    if (child->left == nullptr && child->T != VARIABLE){
        // std::cout << "niet exprpime" << std::endl;
        child->left = new Node();
        exprprime(token, child->left);
    }
    else if (child->right == nullptr && child->T != VARIABLE){
        // std::cout << "niet exprpime" << std::endl;
        child->right = new Node();
        exprprime(token, child->right);
        if (child->right->T == BRACKET_OPEN){
            child->right = nullptr;
        }
    }
    // if(token.peek() != END){
    //     insApp(child);
    //     child->right = new Node();
    //     std::cout << "inexpprime niet end" << std::endl;
    //     exprprime(token, child->right);
    // }
    return;
}
