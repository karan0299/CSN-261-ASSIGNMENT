/** 
*@file Q2.cpp
*@brief this  file will contain all required 
*definitions and basic utilities functions.
*
*@author Karanpreet Singh
*
*@date 04/08/19
*/

#include <iostream>
#include <cmath>
#include <bits/stdc++.h> 
#include <chrono>
using namespace std;
using namespace std::chrono; 

/// Enumeration containing constants
enum Color {RED, BLACK};

/// array fro storing the inorder traversal of BST
int arr[1000];

/// store the number of nodes in tree
int size = 0;
  
/// structure representing the node of the tree
struct node
{ 
    /// real data element for the node
    int data; 
    /// bool representing the color of node on red Black tree
    bool color;
    /// links to the left child , right child and the parent node 
    node *left, *right, *parent; 
}; 


node *insertInAvl(node * root,int key); 
int getBalance(node *N); 
static node * initializeNode(int item);
static node * initializeNodeRB(int item);
static node *leftRotation(struct node *x);
static node *rightRotation(struct node *y);
static int getHeight ( struct node * root );

void printTreeHelper( struct node * root,int level);
void inorderHelper(struct node *root) ;

void printPathsHelper (struct node * root);
void printPathToLeaf(struct node* curr, map<struct node*, struct node*> parent); 
void printRootToLeaf(struct node* root);


//!  class fro BST structure. 
/*!
  A more elaborate class description.
*/
class BST {
public:
    //! A class construction to initialize the root of tree
    /*!
    */
    BST () { root = NULL; }
    //! A membr function to insert the node/ new data into the tree
    /*!
      \param item an integer argument that is data to be stored new node.
      \return bool whether inserted successfully or not
    */
    bool insert(int item) { return insert(item,root); };
    //! A public member function the return the protected member function for inorder traversal
    /*!
        \return private inoderTraversal function
    */
    void inorderTraversal() const { inorderTraversal(root);};
     //! A public member functionto dtore the inoder travelsal of the BST
    /*!
        \return protected function inoderTravel
    */
    void inorderTravel() const { inorderTravel(root);};
     //! A public member function  that to get height of particular node  
    /*!
        \return the integer value of height
    */
    int height() { return height(root); }
     //! A public member function to print tree in levelwise indentation
    /*!
    */
    void printTree() { printTree(root,0); }
     //! Function to print all paths to leaf node
    /*!
    */
    void printPaths();
    /// pointer to root node of tree
    struct node* root;
     
protected:
    //! A protedted member function to print  inorderTraversal of tree
    /*!
        \param curr pointer to the current node
    */
    void inorderTraversal(const struct node* curr) const;
    //! A public member function to get th inorder traversal array 
    /*!
        \param curr pointer to the current node
    */
    void inorderTravel(const struct node* curr) const;
    //! A membr function to insert the node/ new data into the tree
    /*!
      \param item an integer argument that is data to be stored new node.
      \param curr pointer to the current node
      \return bool whether inserted successfully or not
    */
    bool insert(int item,struct node* curr);
    //! A public member function  that to get height of particular node  
    /*!
        \param curr pointer to the current node
        \return the integer value of height
    */
    int height(struct node* curr);
     //! A public member function to print tree in levelwise indentation
    /*!
    */
    void printTree(struct node* curr, int level);
};

//!  class for RebBlack Tree data structure. 
/*!
  A more elaborate class description.
*/
class RBTree 
{ 
private: 
    /// pointer to root node of tree
    struct node *root; 
public: 
    void rotateLeft(struct node *&, struct node *&); 
    void rotateRight(struct node *&, struct node *&); 
    void setToRBTree(struct node *&, struct node *&);  
    RBTree() { root = NULL; } 
     //! A membr function to insert the node/ new data into the tree
    /*!
      \param n an integer argument that is data to be stored new node.
    */
    void insert(int n); 
    //! A protedted member function to print  inorderTraversal of tree
    /*!
        \param curr pointer to the current node
    */
    void inorder(); 
     //! A public member function to print tree in levelwise indentation
    /*!
    */
    void printRBTree();
    //! Function to print all paths to leaf node
    /*!
    */
    void printPaths();
};


int main() {
    BST bst;
    RBTree rbt;
    BST avl;

    int op;
    auto start = high_resolution_clock::now();
    auto stop = high_resolution_clock::now();
    auto duration =duration_cast<microseconds>(stop - start);
    
    while(true){
        cout<<"\n------------------------------------------------------------------------------"<<endl;
        cout<<"1.To insert a node in the BST and in the red-black tree \n";
        cout<<"2.To create AVL tree from the inorder traversal of the BST\n";
        cout<<"3.To print the inorder traversal of the BST/AVL/red-black tree\n";
        cout<<"4.To display all the paths in the BST/AVL tree/red-black tree \n";
        cout<<"5.To print the BST/AVL tree/red-black Tree in the terminal using level-wise indentation\n";
        cout<<"6.exit\n";
        cout<<"Enter your choice"<<endl;
        cin>>op;    
        switch(op) {
            case 1 : 
                        cout<<"Enter number"<<endl;
                        int num;
                        cin>>num;
                        start = high_resolution_clock::now(); 
                        bst.insert(num);
                        rbt.insert(num);
                        stop = high_resolution_clock::now();
                        duration = duration_cast<microseconds>(stop - start); 
                        size++;
                        cout<<num<<" inserted in both reb black and BST "<<endl;
                        cout << "CPU Time taken for insertion: "<< duration.count() << " microseconds" << endl;
                        break;

            case 2 :    
                        start = high_resolution_clock::now(); 
                        bst.inorderTravel();
                        avl.root = NULL;
                        for(int i =0 ;i<size;i++){
                           avl.root = insertInAvl(avl.root,arr[i]);
                        }
                        stop = high_resolution_clock::now();
                        duration = duration_cast<microseconds>(stop - start);
                        cout<<"Binary Search Tree converted to AVL"<<endl;
                        cout << "CPU Time taken AVL tree creation "<< duration.count() << " microseconds" << endl;
                        break;

            case 3 :    
                        start = high_resolution_clock::now(); 
                        cout<<"Inorder Traversal for Binary search Tree "<<endl;
                        bst.inorderTraversal();
                        cout<<"\nInorder Traversal for AVL Tree\n";
                        if(avl.root == NULL)
                            cout<<"AVL tree is empty \n";
                        else 
                            avl.inorderTraversal();
                        cout<<"\nInorder Traversal for Red Black Tree\n";
                        rbt.inorder();
                        cout<<"\n\n";
                        stop = high_resolution_clock::now();
                        duration = duration_cast<microseconds>(stop - start);
                        cout << "CPU Time taken : "<< duration.count() << " microseconds" << endl;
                        break;

            case 4 :    
                        start = high_resolution_clock::now(); 
                        cout<<"Paths for Binary search Tree "<<endl;
                        bst.printPaths();
                        cout<<"\nPaths for AVL Tree\n";
                        if(avl.root == NULL)
                            cout<<"AVL tree is empty \n";
                        else 
                            avl.printPaths();
                        cout<<"\nPaths for Red Black Tree\n";
                        rbt.printPaths();
                        cout<<"\n";
                        stop = high_resolution_clock::now();
                        duration = duration_cast<microseconds>(stop - start);
                        cout << "CPU Time taken : "<< duration.count() << " microseconds" << endl;
                        break;

            case 5 : 
                        start = high_resolution_clock::now(); 
                        cout<<"Level wise indentation printing for Binary search Tree "<<endl;
                        bst.printTree();
                        cout<<"\nLevel wise indentation printing for AVL Tree\n";
                        if(avl.root == NULL)
                            cout<<"AVL tree is empty \n";
                        else 
                            avl.printTree();    
                        cout<<"\nLevel wise indentation printing for Red Black Tree\n";
                        rbt.printRBTree();
                        cout<<"\n";
                        stop = high_resolution_clock::now();
                        duration = duration_cast<microseconds>(stop - start);
                        cout << "CPU Time taken : "<< duration.count() << " microseconds" << endl;
                        break;

            case 6 :
                        exit(0);

        }

    }

}

/**
*This method will be used initialize the node with the given data
*@author Karanpreet Singh
*@param item data to be inserted into the node
*@date 04/08/19
*/
static  node * initializeNode(int item){
    struct node * new_node = new (struct node);
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->data = item;
    return new_node;
}

/**
*This method will be used to apply the left rotation
*@author Karanpreet Singh
*@param x root node aroud which rotation is to be done
*@date 04/08/19
*/
static node *leftRotation(struct node *x)  {  
    struct node *y = x->right;  
    struct node *T2 = y->left;  
  
    // Perform rotation  
    y->left = x;  
    x->right = T2;  

    return y;  
} 

/**
*This method will be used to apply the right rotation
*@author Karanpreet Singh
*@param y root node aroud which rotation is to be done
*@date 04/08/19
*/
static node *rightRotation(struct node *y) {  
    struct node *x = y->left;  
    struct node *T2 = x->right;  
  
    // Perform rotation  
    x->right = y;  
    y->left = T2;  
  
    return x;  
}  

/**
*This method will be used to get the height of the node
*@author Karanpreet Singh
*@param root node to get the height of 
*@date 04/08/19
*/
static int getHeight ( struct node * root ){
   if(!root)
        return 0;
    return 1 + max(getHeight(root->left),getHeight(root->right));
}  

bool BST :: insert(int item, struct node * currentNode) {
    if (root == NULL) {
        root = initializeNode(item);
        return true;
    }
    else if (item < currentNode->data) {
        if (currentNode->left == NULL) {
            currentNode->left = initializeNode(item);
            return true;
        }
        else {
            return insert(item, currentNode->left);
        }
    }
    else if (item > currentNode->data) {
        if (currentNode->right == NULL) {
            currentNode->right = initializeNode(item);
            return true;
        }
        else {
            return insert(item, currentNode->right);
        }
    }
    else // item == currentNode->data
        return false; // duplicate; do not insert
}

void BST :: inorderTraversal(const struct node * root) const {
    if (root != NULL) {
        inorderTraversal(root -> left);
  
        cout<<root -> data<<" ";
        inorderTraversal(root -> right);
    }
}

void BST :: inorderTravel(const struct node * root) const {
    static int l=0;
    if (root != NULL) {
        inorderTravel(root -> left);
        arr[l++] = root->data;
        inorderTravel(root -> right);
    }
}

int BST :: height( struct node * root){
    if(!root)
        return 0;
    return 1 + max(height(root->left),height(root->right));
}

void BST :: printTree( struct node * root,int level) {
    if (root != NULL) {
       for(int i=0;i<level;i++){
        cout<<"\t";
        }
        if(root->left||root->right)
        cout<<root -> data<<"["<<abs(getHeight(root->left)-getHeight(root->right))<<"]"<<endl;
        else
        cout<<root -> data<<endl;
        printTree(root -> left,level+1);   
        printTree(root -> right,level+1);
    }
}


void BST:: printPaths(){
    printPathsHelper(root);
}

/**
*This method will be used initialize the node for the Red Black tree with the given data
*@author Karanpreet Singh
*@param data data to be inserted into the node
*@date 04/08/19
*/
node* initializeNodeRB(int data){
    struct node* new_node = new (struct node);
    new_node->data = data; 
    new_node->left = new_node->right = new_node->parent = NULL; 
    new_node->color = RED;
    return new_node;
}

/**
*This method is helper function to print inorder traversal for 
*@author Karanpreet Singh
*@param item data to be inserted into the node
*@date 04/08/19
*/
void inorderHelper(struct node *root) 
{ 
    if (root == NULL) 
        return; 
  
    inorderHelper(root->left); 
    cout << root->data << "  "; 
    inorderHelper(root->right); 
} 
  
/**
*This method A utility function to insert a new node with given key in BST  
*@author Karanpreet Singh
*@param root pointer to the root node of the tree
*@param new_node pointer to the new node
*@date 04/08/19
*/
node* normalBSTInsert(struct node* root, struct node *new_node) 
{ 
    if (root == NULL) 
       return new_node; 
  
    if (new_node->data < root->data) 
    { 
        root->left  = normalBSTInsert(root->left, new_node); 
        root->left->parent = root; 
    } 
    else if (new_node->data > root->data) 
    { 
        root->right = normalBSTInsert(root->right, new_node); 
        root->right->parent = root; 
    } 
  
    return root; 
} 
  
void RBTree::rotateLeft(struct node *&root, struct node *&node) 
{ 
    struct node *node_right = node->right; 
  
    node->right = node_right->left; 
  
    if (node->right != NULL) 
        node->right->parent = node; 
  
    node_right->parent = node->parent; 
  
    if (node->parent == NULL) 
        root = node_right; 
  
    else if (node == node->parent->left) 
        node->parent->left = node_right; 
  
    else
        node->parent->right = node_right; 
  
    node_right->left = node; 
    node->parent = node_right; 
} 
  
void RBTree::rotateRight(struct node *&root, struct node *&node) 
{ 
    struct node *node_left = node->left; 
  
    node->left = node_left->right; 
  
    if (node->left != NULL) 
        node->left->parent = node; 
  
    node_left->parent = node->parent; 
  
    if (node->parent == NULL) 
        root = node_left; 
  
    else if (node == node->parent->left) 
        node->parent->left = node_left; 
  
    else
        node->parent->right = node_left; 
  
    node_left->right = node; 
    node->parent = node_left; 
} 
  
// This function fixes violations caused by BST insertion 
void RBTree::setToRBTree(struct node *&root, struct node *&new_node) 
{ 
    struct node *parent_node = NULL; 
    struct node *grand_parent_node = NULL; 
  
    while ((new_node != root) && (new_node->color != BLACK) && 
           (new_node->parent->color == RED)) 
    { 
  
        parent_node = new_node->parent; 
        grand_parent_node = new_node->parent->parent; 
  
        if (parent_node == grand_parent_node->left) 
        { 
  
            struct node *uncle_node = grand_parent_node->right; 
  
            if (uncle_node != NULL && uncle_node->color == RED) 
            { 
                grand_parent_node->color = RED; 
                parent_node->color = BLACK; 
                uncle_node->color = BLACK; 
                new_node = grand_parent_node; 
            } 
  
            else
            { 
                if (new_node == parent_node->right) 
                { 
                    rotateLeft(root, parent_node); 
                    new_node = parent_node; 
                    parent_node = new_node->parent; 
                } 
  
                rotateRight(root, grand_parent_node); 
                swap(parent_node->color, grand_parent_node->color); 
                new_node = parent_node; 
            } 
        } 
  
        else
        { 
            struct node *uncle_node = grand_parent_node->left; 
  
            if ((uncle_node != NULL) && (uncle_node->color == RED)) 
            { 
                grand_parent_node->color = RED; 
                parent_node->color = BLACK; 
                uncle_node->color = BLACK; 
                new_node = grand_parent_node; 
            } 
            else
            { 
                if (new_node == parent_node->left) 
                { 
                    rotateRight(root, parent_node); 
                    new_node = parent_node; 
                    parent_node = new_node->parent; 
                } 
  
                rotateLeft(root, grand_parent_node); 
                swap(parent_node->color, grand_parent_node->color); 
                new_node = parent_node; 
            } 
        } 
    } 
  
    root->color = BLACK; 
} 
  
void RBTree::insert(int data) 
{ 
    struct node *new_node = initializeNodeRB(data); 
  
    root = normalBSTInsert(root, new_node); 
  
    setToRBTree(root, new_node); 
} 
  
void RBTree:: inorder() {  
    inorderHelper(root);
} 


/**
*This helper method to print the paths to leaf
*@author Karanpreet Singh
*@param root pointer to the root node of the tree
*@param level level of the current node
*@date 04/08/19
*/
void printTreeHelper( struct node * root,int level) {
    if (root != NULL) {
       for(int i=0;i<level;i++){
        cout<<"\t";
        }
        if(root->left||root->right){
        cout<<root -> data<<"["<<abs(getHeight(root->left)-getHeight(root->right))<<"]";
            if(root->color==0){
                cout<<"["<<"RED"<<"]"<<endl;
            }
            else{
                cout<<"["<<"Black"<<"]"<<endl;
            }
        }
        else {
            cout<<root -> data;
            if(root->color==0){
                cout<<"["<<"RED"<<"]"<<endl;
            }
            else{
                cout<<"["<<"Black"<<"]"<<endl;
            }
        }
        printTreeHelper(root -> left,level+1);   
        printTreeHelper(root -> right,level+1);
    }
}

void RBTree :: printRBTree() {
    printTreeHelper(root,0);
}


/**
*Function to print root to leaf path for a leaf using parent nodes stored in map
*@author Karanpreet Singh
*@param curr pointer to the current node of the tree
*@param parent a map haing parent of the current node
*@date 04/08/19
*/
void printPathToLeaf(struct node* current, map<struct node*, struct node*> parent) 
{ 
    stack<struct node*> nodeStack; 

    while (current) 
    { 
        nodeStack.push(current); 
        current = parent[current]; 
    } 
  
    while (!nodeStack.empty()) 
    { 
        current = nodeStack.top(); 
        nodeStack.pop(); 
        cout << current->data << " "; 
    } 
    cout << endl; 
} 
  

/**
*An iterative function to do preorder traversal of binary tree  and print root to leaf path without using recursion
*@author Karanpreet Singh
*@param root pointer to the rootnode of the tree
*@date 04/08/19
*/
void printRootToLeaf(struct node* root) { 
    if (root == NULL) 
        return; 
  
    stack<struct node*> nodeStack; 
    nodeStack.push(root); 

    map<struct node*, struct node*> parent; 
  
    parent[root] = NULL; 
  

    while (!nodeStack.empty()) 
    { 

        struct node* current = nodeStack.top(); 
        nodeStack.pop(); 

        if (!(current->left) && !(current->right)) 
            printPathToLeaf(current, parent); 
 
        if (current->right) 
        { 
            parent[current->right] = current; 
            nodeStack.push(current->right); 
        } 
        if (current->left) 
        { 
            parent[current->left] = current; 
            nodeStack.push(current->left); 
        } 
    } 
} 

void printPathsHelper (struct node * root){
    if(root==NULL)
    return;
    printRootToLeaf(root);
    printPathsHelper(root->left);
    printPathsHelper(root->right);
}

void RBTree :: printPaths(){
    printPathsHelper(root);
}


int getBalance(node *N)  {  
    if (N == NULL)  
        return 0;  
    return getHeight(N->left) - getHeight(N->right);  
}  

/**
*Function to insert the node in the AVL tree
*@author Karanpreet Singh
*@param Node pointer to the root of the tree
*@param data to be inserted into the new node
*@date 04/08/19
*/
node* insertInAvl(node* Node, int data) {  
    if (Node == NULL)  
        return(initializeNode(data));  
  
    if (data < Node->data)  
        Node->left = insertInAvl(Node->left, data);  
    else if (data > Node->data)  
        Node->right = insertInAvl(Node->right, data);  
    else 
        return Node;  
  
    int balance = getBalance(Node);  
   
    if (balance > 1 && data < Node->left->data)  
        return rightRotation(Node);  
  
    if (balance < -1 && data > Node->right->data)  
        return leftRotation(Node);  
  
    if (balance > 1 && data > Node->left->data)  
    {  
        Node->left = leftRotation(Node->left);  
        return rightRotation(Node);  
    }  
  
    if (balance < -1 && data < Node->right->data)  
    {  
        Node->right = rightRotation(Node->right);  
        return leftRotation(Node);  
    }  
  
    return Node;  
}  