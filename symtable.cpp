/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"
// #include <iostream>
// #include "symnode.cpp"
//Write your code below this line


SymbolTable::SymbolTable(){
    size = 0;
    root = NULL ;
}


int balanceCoefficient1(SymNode * node){
    if(node==NULL){
// cout<<"....1  ...."<<endl;
        return 0;
    }
// cout<<"....2  ...."<<endl;
    if(node->left==NULL && node->right!=NULL){
        return  - (node->right->height);
    }
    else if(node->left==NULL && node->right==NULL){
        return 0;
    }
    else if(node->left!=NULL && node->right==NULL){
        return (node->left->height) ;
    }
    else{
        return (node->left->height) - (node->right->height);
    }
    
// cout<<"....3  ...."<<endl;
}





int getHeight(SymNode* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

SymNode* rightRotate(SymNode* y) {
    SymNode* x = y->left;
    SymNode* T2 = x->right;

    // Update parent pointers
    x->par = y->par;
    if (y->par) {
        if (y == y->par->left) {
            y->par->left = x;
        } else {
            y->par->right = x;
        }
    }

    x->right = y;
    y->par = x;
    y->left = T2;

    // Update heights
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

SymNode* leftRotate(SymNode* x) {
    SymNode* y = x->right;
    SymNode* T2 = y->left;

    // Update parent pointers
    y->par = x->par;
    if (x->par) {
        if (x == x->par->left) {
            x->par->left = y;
        } else {
            x->par->right = y;
        }
    }

    y->left = x;
    x->par = y;
    x->right = T2;

    // Update heights
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}


SymNode* insert_H(SymNode* node, string k, SymNode* par = NULL) {
    // cout<<"came to insert helper "<<endl;
    if (node == NULL) {
    // cout<<"inserting in null"<<endl;
        SymNode* temp = new SymNode(k);
    // cout<<"created a temp"<<endl;
        temp->par = par;
    // cout<<"assigned parent "<<endl;
        return temp;
    }



// cout<<"out of stage 1"<<endl;
    if (k < node->key) {
        // cout << "Inserting '" << k << "' to the left of '" << node->key << "'" << endl;
        node->left = insert_H(node->left, k, node);
    } 



// cout<<"out of stage 2"<<endl;    
     if (k > node->key) {
        // cout << "Inserting '" << k << "' to the right of '" << node->key << "'" << endl;
        node->right = insert_H(node->right, k, node);
    }



// cout<<"out of stage 3"<<endl;
    // Update height
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    // cout << "Updated height of node '" << node->key << "' to " << node->height << endl;

    // Calculate balance factor
    int bf = balanceCoefficient1(node);
    // cout << "Balance Factor of node '" << node->key << "' is " << bf << endl;

    // Perform rotations if needed
    if (bf > 1) {
        if (k < node->left->key) {
            // cout << "Performing rightRotate on node '" << node->key << "'" << endl;
            return rightRotate(node);
        } else if (k > node->left->key) {
            // cout << "Performing leftRotate on left child of node '" << node->key << "'" << endl;
            node->left = leftRotate(node->left);
            // cout << "Performing rightRotate on node '" << node->key << "'" << endl;
            return rightRotate(node);
        }
    }

    if (bf < -1) {
        if (k > node->right->key) {
            // cout << "Performing leftRotate on node '" << node->key << "'" << endl;
            return leftRotate(node);
        } else if (k < node->right->key) {
            // cout << "Performing rightRotate on right child of node '" << node->key << "'" << endl;
            node->right = rightRotate(node->right);
            // cout << "Performing leftRotate on node '" << node->key << "'" << endl;
            return leftRotate(node);
        }
    }

    return node;
}


SymNode* search_H(SymNode* node, string k) {
// cout<<"...1..."<<endl;
        if (node==NULL) {
// cout<<"...2..."<<endl;
            return NULL; // Key not found
// cout<<"...3..."<<endl;
        }
// cout<<"...4..."<<endl;

        if (k == node->key) {
// cout<<"...5..."<<endl;
            return node ; // Found the entry
// cout<<"...6..."<<endl;
        }
// cout<<" elelel1 "<<endl;  


        if (k < node->key) {
// cout<<"...7..."<<endl;
            return search_H(node->left, k); // Search left subtree
// cout<<"...8..."<<endl;
        } 

// cout<<" elelel2 "<<endl;  
        if(k > node->key) {
// cout<<"...9..."<<endl;
            return search_H(node->right, k); // Search right subtree
// cout<<"...10..."<<endl;
        }
// cout<<" elelel3 "<<endl; 
    return node;
    }


SymNode* minValueNodeH(SymNode* node) {
        SymNode* current = node;
        while (current && current->left) {
            current = current->left;
        }
        return current;
    }

SymNode* remove_H(SymNode* node, string k) {
    if (node == NULL) {
        return node; // Key not found
    }

    if (k < node->key) {
        node->left = remove_H(node->left, k);
    } else if (k > node->key) {
        node->right = remove_H(node->right, k);
    } else {
        if (!node->left || !node->right) {
            SymNode* temp = node->left ? node->left : node->right;

            if (!temp) {
                temp = node;
                node = NULL;
            } else {
                node = temp;
                temp=NULL;
            }
        } else {
            SymNode* minNode = minValueNodeH(node->right);
            node->key = minNode->key;
            node->address = minNode->address;
            node->right = remove_H(node->right, minNode->key);
        }
    }

    if (node == NULL) {
        return node;
    }

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    int bf = balanceCoefficient1(node);

    // Check balance factor and perform rotations if needed
    if (bf > 1) {
        if (balanceCoefficient1(node->left) >= 0) {
            return rightRotate(node);
        } else {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    }

    if (bf < -1) {
        if (balanceCoefficient1(node->right) <= 0) {
            return leftRotate(node);
        } else {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }

    return node;
}



void deleteTree(SymNode* node){
    if (node) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

}






void SymbolTable::insert(string k){
// cout<<"insert began "<<endl;

if(size==0){
// cout<<"came to if"<<endl;
    SymNode* temp = new SymNode(k);
    root = temp;
    root->par=NULL;
    // cout<<" job done "<<endl;
}
else{
    // cout<<"inbuilt "<<size<<endl;
    // cout<<"came to else"<<endl;
    root = insert_H(root , k);
}
    
    
// cout<<"inserted"<<endl;
// cout<<"finished"<<endl;
    size++;
}

void SymbolTable::remove(string k){
    // cout<<k<<endl;
// cout<<"remove began"<<endl;
    if(search(k)!= -2){
        root = remove_H(root, k);
        size--;
    }
    
}

int SymbolTable::search(string k){

    SymNode * node = search_H(root , k);
    if(node==NULL){

        return -2;
    }
    else{

        return node->address;
    }
}

void SymbolTable::assign_address(string k, int idx){
    SymNode* node = search_H(root, k);
    if (node!=NULL) {
        node->address = idx;
    } 
}

int SymbolTable::get_size(){
    return size;
}

SymNode* SymbolTable::get_root(){
    return root;
}

SymbolTable::~SymbolTable(){
    // deleteTree(root);
}

void print_tree(SymNode* node) {
    if (node == NULL) {
        return;  // Base case: stop recursion if node is NULL
    }

    print_tree(node->left);
    // cout << "Key: " << node->key << ", Height: " << node->height << endl;
    print_tree(node->right);
}


