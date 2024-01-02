/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"


bool isVariable(const string& token) {
    // Implement your logic to check if 'token' is a variable here
    // Return true if it's a variable, false otherwise
    // You might check if the token matches a pattern, e.g., all uppercase letters, etc.
    // For simplicity, let's assume that a variable consists of uppercase letters only.
    for (char c : token) {
        if(c =='a'||c =='b'||c =='c'||c =='d'||c =='e'||c =='f'||c =='g'||c =='h'||
    c =='i'||c =='j'||c =='k'||c =='l'||c =='m'||c =='n'||c =='o'||c =='p'||c =='q'||
    c =='r'||c =='s'||c =='t'||c =='u'||c =='v'||c =='w'||c =='x'||c =='y'||c =='z'){
        return true;
    }
    else{return false;}
    }
    return false;
}


//Write your code below this line

ExprTreeNode::ExprTreeNode(){
    
    type= "";
    id = "";
    num = 00 ;
    left = NULL;
    right = NULL;
}

ExprTreeNode::ExprTreeNode(string t,int v){
    if (t == ":=") {
        type = "RUT";
        num = 00;
        left = NULL;
        right = NULL;
        id = "";
    } 
    else if (t == "*") {
        type = "MUL";
        num = 00 ;
        left = NULL;
        right = NULL;
        id = "";
    } 
    else if (t == "/") {
        type = "DIV";
        num = 00 ;
        left = NULL;
        right = NULL;
        id = "";
    } 
    else if (t == "-") {
        type = "SUB";
        num = 00 ;
        left = NULL;
        right = NULL;
        id = "";
    } 
    else if (t == "+") {
        type = "ADD";
        num = 00 ;
        left = NULL;
        right = NULL;
        id = "";
    } 
    else if (t == "del"){
        type = "DEL";
        num = 00 ;
        left = NULL;
        right = NULL;
        id = "";
    }
    else if (t == "ret"){
        type = "RET";
        num = 00 ;
        left = NULL;
        right = NULL;
        id = "";
    }
    else {
        if(isVariable(t)==true){
            type = "VAR";
            num = 00 ;
            left = NULL;
            right = NULL;
            id = t;   
        }
        else{
            type = "VAL";
            num = v ;
            left = NULL;
            right = NULL;
            id = ""; 
        }
        
    }

}

ExprTreeNode::~ExprTreeNode(){
    delete left;
    delete right;
}

