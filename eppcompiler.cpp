/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
// #include <iostream>
#include "eppcompiler.h"




EPPCompiler::EPPCompiler() {
    memory_size = 2000;
    output_file = "";
    for (int i = 0; i < 2000; i++) {
        mem_loc[i] = i ;
    }
}



EPPCompiler::EPPCompiler(string out_file, int mem_limit) {

// targ.symtable = new SymbolTable();
    // targ.symtable->get_root()=NULL;

    memory_size = mem_limit;
    output_file = out_file;
    mem_loc.resize(memory_size);

    for (int i = 0; i < memory_size; i++) {
        mem_loc[i] = i ;
    }
}

vector<string> generate_H( ExprTreeNode* node , vector<int>& mem_loc , Parser& targ) {
    
        vector<string> commands;
        if(node==NULL){
            return commands ;
        }

        
        vector<string> rightCommands = generate_H(node->right,mem_loc,targ);
        vector<string> leftCommands = generate_H(node->left,mem_loc,targ);
        
        commands.insert(commands.end(), rightCommands.begin(), rightCommands.end());
        commands.insert(commands.end(), leftCommands.begin(), leftCommands.end());
        
        if (node->type == "VAL") {
        commands.push_back("PUSH " + to_string(node->num));
        } 
        else if (node->type == "VAR") {

                commands.push_back("PUSH mem[" + to_string(targ.symtable->search(node->id)) + "]");


        } 
        else if (node->type == "ADD") {
            // cout<<"came here"<<endl;
        commands.push_back("ADD");
        } else if (node->type == "SUB") {
        commands.push_back("SUB");
        } else if (node->type == "MUL") {
        commands.push_back("MUL");
        } else if (node->type == "DIV") {
        commands.push_back("DIV");
        } 
        
        

        return commands ;


}




vector<string> EPPCompiler::generate_targ_commands() {
    vector<string> commands;

    if (targ.expr_trees.empty()) {
        return commands;  
    }
    for (ExprTreeNode* root : targ.expr_trees) {
        if(root==NULL){
            continue;
        }

        if (root->type == "RUT" && root->left->type == "DEL") {    
            commands.push_back("DEL = mem[" + to_string(targ.symtable->search(root->right->id)) + "]"); // Store in variable

        } 

        else if(root->type=="RUT" && root->left->type == "VAR"){
                // int mem_index = mem_loc.back();
                
                // if(targ.symtable->search(root->left->id)== -1 ){
                //     targ.symtable->assign_address(root->left->id , mem_index);
                //     mem_loc.pop_back();
                // }
                
                
                
            vector<string> exprCommands = generate_H(root->right,mem_loc, targ);

            commands.insert(commands.end(), exprCommands.begin(), exprCommands.end());
            commands.push_back("mem[" + to_string(targ.symtable->search(root->left->id)) + "] = POP"); 

        }

        else if(root->type == "RUT" && root->left->type == "RET"){
            vector<string> exprCommands = generate_H(root->right,mem_loc , targ);

            commands.insert(commands.end(), exprCommands.begin(), exprCommands.end());
            commands.push_back("RET = POP");

        }

    }
    return commands;
}






void EPPCompiler::compile(vector<vector<string>> code) {

    for (int i = 0; i < code.size(); i++) {
        vector<string> expression = code[i];
        targ.parse(expression);
        for (int j = 0; j < targ.expr_trees.size(); j++)
        {
            if(targ.expr_trees[j]->left->type=="VAR"){
                int mem_index = mem_loc.back();
                if(targ.symtable->search(targ.expr_trees[j]->left->id)== -1 ){
                    targ.symtable->assign_address(targ.expr_trees[j]->left->id , mem_index);
                    mem_loc.pop_back();
                }

            }
            if(targ.expr_trees[j]->left->type=="DEL"){
                mem_loc.push_back(targ.expr_trees[j]->left->num);
            }
        }
        


        vector<string> commands = generate_targ_commands();


        write_to_file(commands);
    }
}








void EPPCompiler::write_to_file(vector<string> commands) {
    ofstream output(output_file);
    if (!output.is_open()) {
        
        return;
    }
    for (string command : commands) {
        output << command << endl;
    }

    output.close();
}

EPPCompiler::~EPPCompiler(){

}






