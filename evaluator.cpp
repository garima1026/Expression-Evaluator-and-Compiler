/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "evaluator.h"

void postOrderTraversal(ExprTreeNode* node, vector<ExprTreeNode*>& resultStack) {
    if (node) {
        postOrderTraversal(node->left, resultStack);
        postOrderTraversal(node->right, resultStack);
        resultStack.push_back(node);
    }
}

Evaluator::Evaluator() {
    symtable = new SymbolTable();
}

Evaluator::~Evaluator() {
    // Clean up resources
    delete symtable;
    // for (ExprTreeNode* node : expr_trees) {
    //     delete node;
    // }
    expr_trees.clear();
}

void Evaluator::parse(vector<string> code) {
    vector<ExprTreeNode*> parseStack;

    for (string token : code) {
        ExprTreeNode* newNode = new ExprTreeNode();
        newNode->type = token;

        if (token == "(") {
          
            parseStack.push_back(newNode);
        } else if (token == ")") {
           
            while (!parseStack.empty() && parseStack.back()->type != "(") {
                ExprTreeNode* right = parseStack.back();
                parseStack.pop_back(); // Remove the right operand
                ExprTreeNode* op = parseStack.back();
                parseStack.pop_back(); // Remove the operator
                ExprTreeNode* left = parseStack.back();
                parseStack.pop_back(); // Remove the left operand

                op->left = left;
                op->right = right;
                parseStack.push_back(op); // Push the subtree back onto the stack
            }
            // Pop the opening parenthesis
            delete newNode;
        } else {
            // Operand or operator, push onto the stack
            parseStack.push_back(newNode);
        }
    }

    // The root of the parse tree should be the last element in the stack
    if (!parseStack.empty()) {
        
        ExprTreeNode* root = parseStack.back();
        expr_trees.push_back(root);
    }
}

void Evaluator::eval() {
    // Initialize your expression evaluation logic here
    // Use the internal vector as a stack for expression evaluation
    vector<ExprTreeNode*> evalStack;

    if (expr_trees.empty()) {
        // No expression to evaluate
        return;
    }

    ExprTreeNode* root = expr_trees.back();

    // Use the helper function for post-order traversal
    vector<ExprTreeNode*> postOrderStack;
    postOrderTraversal(root, postOrderStack);

    for (ExprTreeNode* node : postOrderStack) {
        if (node->type == "VAL") {
            // If it's a value node, push it onto the stack
            evalStack.push_back(node);
        } else if (node->type == "VAR") {
            // If it's a variable node, look up its value in the symbol table
            UnlimitedRational* value = symtable->search(node->id);
            if (value != nullptr) {
                node->val = value;
                evalStack.push_back(node);
            } else{ 
                return;
                }
            } 
            else if (node->type == "ADD") {
        // Addition operation
        if (evalStack.size() < 2) {
            // Handle insufficient operands error
            // You can set an appropriate value here
            return;
        }
        ExprTreeNode* right = evalStack.back();
        evalStack.pop_back();
        ExprTreeNode* left = evalStack.back();
        evalStack.pop_back();

        // Perform the addition operation and push the result back onto the stack
        UnlimitedRational* result = UnlimitedRational::add(left->val, right->val);
        node->val = result;
        evalStack.push_back(node);
    } else if (node->type == "SUB") {
        // Subtraction operation
        if (evalStack.size() < 2) {
            // Handle insufficient operands error
            // You can set an appropriate value here
            return;
        }
        ExprTreeNode* right = evalStack.back();
        evalStack.pop_back();
        ExprTreeNode* left = evalStack.back();
        evalStack.pop_back();

        // Perform the subtraction operation and push the result back onto the stack
        UnlimitedRational* result = UnlimitedRational::sub(left->val, right->val);
        node->val = result;
        evalStack.push_back(node);
    } else if (node->type == "MUL") {
        // Multiplication operation
        if (evalStack.size() < 2) {
            // Handle insufficient operands error
            // You can set an appropriate value here
            return;
        }
        ExprTreeNode* right = evalStack.back();
        evalStack.pop_back();
        ExprTreeNode* left = evalStack.back();
        evalStack.pop_back();

        // Perform the multiplication operation and push the result back onto the stack
        UnlimitedRational* result = UnlimitedRational::mul(left->val, right->val);
        node->val = result;
        evalStack.push_back(node);
    } else if (node->type == "DIV") {
        // Division operation
        if (evalStack.size() < 2) {
            // Handle insufficient operands error
            // You can set an appropriate value here
            return;
        }
        ExprTreeNode* right = evalStack.back();
        evalStack.pop_back();
        ExprTreeNode* left = evalStack.back();
        evalStack.pop_back();

        // Perform the division operation and push the result back onto the stack
        UnlimitedRational* result = UnlimitedRational::div(left->val, right->val);
        node->val = result;
        evalStack.push_back(node);
    }
}}


























