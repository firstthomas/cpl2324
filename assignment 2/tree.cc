#include "tree.h"

// tree::tree(Token tokenarray[], int array_size){

//     begin = new Node();
//     int i = 0;
//     createTree(tokenarray, i, begin);
// }

// void tree::createTree(Token tokenarray[], int &i, Node* child){
    
//     if (tokenarray[i].x == SLASH){
//         child->T->x = tokenarray[i].x;
//         // child->T->y = tokenarray[i].y;
//         i++;
//         if (tokenarray[i].x == WHITESPACE){
//             i++;
//         }
//         child->left = new Node();
//         child->left->T->x = tokenarray[i].x;
//         child->left->T->y = tokenarray[i].y;
//         if (tokenarray[i+1].x == WHITESPACE){
//             i += 2;
//         }
//         child->right = new Node();
//         createTree(tokenarray, i, child->right);
//     }
//     else if (tokenarray[i].x == VARIABLE){
//         child->T->x = tokenarray[i].x;
//         child->T->y = tokenarray[i].y;
//     }
//     else if (tokenarray[i].x == BRACKET_OPEN){
//         i++;
//         if (tokenarray[i].x == BRACKET_OPEN){
//             child->left = new Node();
//             i++;
//             createTree(tokenarray, i, child->left);
//         }
//         else if (tokenarray[i].x == SLASH){
//             child->T->x = SLASH;
//         }
//         else if (tokenarray[i].x == VARIABLE){
//             child->T->x = APP;
//         }
//     }
//     createTree(tokenarray, i, child);
// }

// // void tree::readIn(std::string input){
    
// // }

// void tree::makeNextNode(std::string str){
    
// }