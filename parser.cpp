/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"
// #include <iostream>
//Write your code below this line
bool isVariable2(const string& token) {
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





Parser::Parser(){ 
    symtable = new SymbolTable();
 }

void Parser::parse(vector<string> expression){
    vector<ExprTreeNode*> parseStack;


    for (size_t i = 0; i < expression.size(); i++) {
        string token = expression[i];
        if (token == "(") {
            parseStack.push_back(NULL);
        } else if (token == ")") {
            if (!parseStack.empty() && parseStack.back() != NULL) {
                ExprTreeNode* right = parseStack.back();
                parseStack.pop_back();  // Remove the right operand
                ExprTreeNode* op = parseStack.back();
                parseStack.pop_back(); // Remove the operator
                ExprTreeNode* left = parseStack.back();
                parseStack.pop_back(); // Remove the left operand

                op->left = left;
                op->right = right;

                if (!parseStack.empty() && parseStack.back() == NULL) {
                parseStack.pop_back();

                }

                parseStack.push_back(op); // Push the subtree back onto the stack

            }

        } else {
            // Operand or operator, push onto the stack as a new node
            
            if (token == ":=") {
                ExprTreeNode* newNode = new ExprTreeNode();
                newNode->type = "RUT";
                parseStack.push_back(newNode);
            } 
            else if (token== "*") {
                ExprTreeNode* newNode = new ExprTreeNode();
                newNode->type = "MUL";
                parseStack.push_back(newNode);
                
            } 
            else if (token== "/") {
                ExprTreeNode* newNode = new ExprTreeNode();
                newNode->type= "DIV";
                parseStack.push_back(newNode);
                
            } 
            else if (token == "-") {
                ExprTreeNode* newNode = new ExprTreeNode();
                newNode->type = "SUB";
                parseStack.push_back(newNode);
                
            } 
            else if (token == "+") {
                ExprTreeNode* newNode = new ExprTreeNode();
                newNode->type = "ADD";
                parseStack.push_back(newNode);
                
            } 
            else if (token == "del") {
                    ExprTreeNode* newNode = new ExprTreeNode();
                    newNode->type="DEL";
                    parseStack.push_back(newNode);

                    ExprTreeNode* newNode1 = new ExprTreeNode();
                    newNode1->type="RET";
                    parseStack.push_back(newNode1);

                    ExprTreeNode* newNode2 = new ExprTreeNode();
                    newNode2->type="VAR";
                    newNode2->id = token;
                    
                    newNode->num = symtable->search(expression[i+2]);
                    symtable->remove(token);
                    // expression[i+2]->address = -4 ;
                    parseStack.push_back(newNode);
                    continue;
                     
            }
            else if (token == "ret"){
                ExprTreeNode* newNode = new ExprTreeNode();
                newNode->type = "RET";
                parseStack.push_back(newNode);
            }
            else if(isVariable2(token)==true){
                        ExprTreeNode* newNode = new ExprTreeNode();
                        newNode->type="VAR";
                        newNode->id = token;
                        parseStack.push_back(newNode);

                        if(symtable->search(token)== -2 ){
                        symtable->insert(token);
                        }
                        // if(symtable->search(token)== -4 ){
                        
                        // }


                    }
                    

            
            else{
                // cout<<"token"<<token<<endl;
                int myint = stoi(token);

                ExprTreeNode* newNode = new ExprTreeNode();
                    newNode->type="VAL";
                    newNode->num = myint;
                    parseStack.push_back(newNode);

                    }
            }
            
        }
    

    // The root of the parse tree should be the last element in the stack
    if (!parseStack.empty()) {

        ExprTreeNode* right = parseStack.back();
        parseStack.pop_back();

        ExprTreeNode* root = parseStack.back();
        parseStack.pop_back();

        ExprTreeNode* left = parseStack.back();
        parseStack.pop_back();

        root->left = left;
        root->right = right;
        expr_trees.push_back(root);

    }
}

Parser::~Parser(){
    // expr_trees.clear();
}

