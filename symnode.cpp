/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"


SymNode::SymNode(){
    
    key = "";
    height = 1;
    address = -1;
    par = NULL;
    left = NULL;
    right = NULL;
}

SymNode::SymNode(string k){
    key = k;
    height = 1 ;
    address = -1;
    par = NULL;
    left = NULL;
    right = NULL;

}

SymNode* SymNode::LeftLeftRotation(){
    return NULL ;
}

SymNode* SymNode::RightRightRotation(){
    return NULL ;
}

SymNode* SymNode::LeftRightRotation(){
    return NULL ;
}

SymNode* SymNode::RightLeftRotation(){
    return NULL ;
}

SymNode::~SymNode(){
    delete par;
    delete left ;
    delete right ;
    
}