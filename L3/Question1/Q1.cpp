#include <iostream>
#include <cmath>
#include <bits/stdc++.h> 
using namespace std;

enum Color {RED, BLACK}; 
  
struct node
{ 
    int data; 
    bool color; 
    node *left, *right, *parent; 
}; 

static node * initializeNode(int item);
static node * initializeNodeRB(int item);
static node *leftRotation(struct node *x);
static node *rightRotation(struct node *y);
static int getHeight ( struct node * root );
static void storeBSTNodes(struct node* root, vector<struct node *> &nodes);
static node* convertToAVLUtil(vector<struct node*> &nodes, int start, int end);
static node*  convertToAVL(struct node* root);

void printTreeHelper( struct node * root,int level);
void inorderHelper(struct node *root) ;

void printPathsHelper (struct node * root);
void printTopToBottomPath(struct node* curr, map<struct node*, struct node*> parent); 
void printRootToLeaf(struct node* root);

class BST {
public:
    BST () { root = NULL; }
    bool insert(int item) { return insert(item,root); };
    void inorderTraversal() const { inorderTraversal(root);};
    int height() { return height(root); }
    void printTree() { printTree(root,0); }
    void printPaths();
    struct node* root;
     
protected:
    void inorderTraversal(const struct node* curr) const;
    bool insert(int item,struct node* curr);
    int height(struct node* curr);
    void printTree(struct node* curr, int level);
};

class RBTree 
{ 
private: 
    struct node *root; 
public: 
    void rotateLeft(struct node *&, struct node *&); 
    void rotateRight(struct node *&, struct node *&); 
    void setToRBTree(struct node *&, struct node *&);  
    RBTree() { root = NULL; } 
    void insert(int n); 
    void inorder(); 
    void printTree();
    void printPaths();
};



node *copy(node *root) {
     node *new_root;
     if(root!=NULL){
         new_root=initializeNode(root->data);
         new_root->left=copy(root->left);
         new_root->right=copy(root->right);
     } else return NULL;
     return new_root;
 }



int main() {
    BST bst;
    RBTree rbt;
    BST avl;

    int op;
    
    while(true){
        cout<<"\n-------------------------------------------------------------------"<<endl;
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
                        bst.insert(num);
                        rbt.insert(num);
                        cout<<num<<" inserted in both reb black and BST "<<endl;
                        break;

            case 2 :    
                        avl.root = copy(bst.root);
                        avl.root = convertToAVL(avl.root);
                        cout<<"Binary Search Tree converted to AVL"<<endl;
                        break;

            case 3 :    
                        cout<<"Inorder Traversal for Binary search Tree "<<endl;
                        bst.printPaths();
                        cout<<"\nInorder Traversal for AVL Tree\n";
                        if(avl.root == NULL)
                            cout<<"AVL tree is empty \n";
                        else 
                            avl.printPaths();
                        cout<<"\nInorder Traversal for Red Black Tree\n";
                        rbt.inorder();
                        cout<<"\n";
                        break;

            case 4 :    
                        cout<<"Paths for Binary search Tree "<<endl;
                        bst.printPaths();
                        cout<<"\nPaths for AVL Tree\n";
                        if(avl.root == NULL)
                            cout<<"AVL tree is empty \n";
                        else 
                            avl.inorderTraversal();
                        cout<<"\nPaths for Red Black Tree\n";
                        rbt.inorder();
                        cout<<"\n";
                        break;

            case 5 : 
                        cout<<"Level wise indentation printing for Binary search Tree "<<endl;
                        bst.printTree();
                        cout<<"\nLevel wise indentation printing for AVL Tree\n";
                        if(avl.root == NULL)
                            cout<<"AVL tree is empty \n";
                        else 
                            avl.printTree();    
                        cout<<"\nLevel wise indentation printing for Red Black Tree\n";
                        rbt.printTree();
                        cout<<"\n";
                        break;

            case 6 :
                        exit(0);

        }

    }

}

static  node * initializeNode(int item){
    struct node * new_node = new (struct node);
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->data = item;
    return new_node;
}

static node *leftRotation(struct node *x)  {  
    struct node *y = x->right;  
    struct node *T2 = y->left;  
  
    // Perform rotation  
    y->left = x;  
    x->right = T2;  

    return y;  
} 

static node *rightRotation(struct node *y) {  
    struct node *x = y->left;  
    struct node *T2 = x->right;  
  
    // Perform rotation  
    x->right = y;  
    y->left = T2;  
  
    return x;  
}  

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
        cout<<root -> data<<endl;
        inorderTraversal(root -> right);
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
        cout<<root -> data<<"["<<abs(getHeight(root->left)-getHeight(root->right))<<endl;
        else
        cout<<root -> data<<endl;
        printTreeHelper(root -> left,level+1);   
        printTreeHelper(root -> right,level+1);
    }
}

static void storeBSTNodes(struct node* root, vector<struct node *> &nodes) { 
	// Base case 
	if (root==NULL) 
		return; 

	// Store nodes in Inorder (which is sorted 
	// order for BST) 
	storeBSTNodes(root->left, nodes); 
	nodes.push_back(root); 
	storeBSTNodes(root->right, nodes); 
} 

static node* convertToAVLUtil(vector<struct node*> &nodes, int start, int end) { 
	// base case 
	if (start > end) 
		return NULL; 

	/* Get the middle element and make it root */
	int mid = ceil((start + end)/2.0); 
	struct node *root = nodes[mid]; 

	/* Using index in Inorder traversal, construct 
	left and right subtress */
	root->left = convertToAVLUtil(nodes, start, mid-1); 
	root->right = convertToAVLUtil(nodes, mid+1, end); 

	return root; 
} 


static node*  convertToAVL(struct node* root){ 
	// Store nodes of given BST in sorted order 
	vector<struct node *> nodes; 
	storeBSTNodes(root, nodes); 

	// Constucts BST from nodes[] 
	int n = nodes.size(); 
	return convertToAVLUtil(nodes, 0, n-1); 
} 

void BST:: printPaths(){
    printPathsHelper(root);
}


node* initializeNodeRB(int data){
    struct node* new_node = new (struct node);
    new_node->data = data; 
    new_node->left = new_node->right = new_node->parent = NULL; 
    new_node->color = RED;
    return new_node;
}

void inorderHelper(struct node *root) 
{ 
    if (root == NULL) 
        return; 
  
    inorderHelper(root->left); 
    cout << root->data << "  "; 
    inorderHelper(root->right); 
} 
  
/* A utility function to insert a new node with given key 
   in BST */
node* normalBSTInsert(struct node* root, struct node *new_node) 
{ 
    /* If the tree is empty, return a new node */
    if (root == NULL) 
       return new_node; 
  
    /* Otherwise, recur down the tree */
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
  
    /* return the (unchanged) node pointer */
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
  
        /*  Case : A 
            Parent of pt is left child of Grand-parent of pt */
        if (parent_node == grand_parent_node->left) 
        { 
  
            struct node *uncle_node = grand_parent_node->right; 
  
            /* Case : 1 
               The uncle of pt is also red 
               Only Recoloring required */
            if (uncle_node != NULL && uncle_node->color == RED) 
            { 
                grand_parent_node->color = RED; 
                parent_node->color = BLACK; 
                uncle_node->color = BLACK; 
                new_node = grand_parent_node; 
            } 
  
            else
            { 
                /* Case : 2 
                   pt is right child of its parent 
                   Left-rotation required */
                if (new_node == parent_node->right) 
                { 
                    rotateLeft(root, parent_node); 
                    new_node = parent_node; 
                    parent_node = new_node->parent; 
                } 
  
                /* Case : 3 
                   pt is left child of its parent 
                   Right-rotation required */
                rotateRight(root, grand_parent_node); 
                swap(parent_node->color, grand_parent_node->color); 
                new_node = parent_node; 
            } 
        } 
  
        /* Case : B 
           Parent of pt is right child of Grand-parent of pt */
        else
        { 
            struct node *uncle_node = grand_parent_node->left; 
  
            /*  Case : 1 
                The uncle of pt is also red 
                Only Recoloring required */
            if ((uncle_node != NULL) && (uncle_node->color == RED)) 
            { 
                grand_parent_node->color = RED; 
                parent_node->color = BLACK; 
                uncle_node->color = BLACK; 
                new_node = grand_parent_node; 
            } 
            else
            { 
                /* Case : 2 
                   pt is left child of its parent 
                   Right-rotation required */
                if (new_node == parent_node->left) 
                { 
                    rotateRight(root, parent_node); 
                    new_node = parent_node; 
                    parent_node = new_node->parent; 
                } 
  
                /* Case : 3 
                   pt is right child of its parent 
                   Left-rotation required */
                rotateLeft(root, grand_parent_node); 
                swap(parent_node->color, grand_parent_node->color); 
                new_node = parent_node; 
            } 
        } 
    } 
  
    root->color = BLACK; 
} 
  
// Function to insert a new node with given data 
void RBTree::insert(int data) 
{ 
    struct node *new_node = initializeNodeRB(data); 
  
    // Do a normal BST insert 
    root = normalBSTInsert(root, new_node); 
  
    // fix Red Black Tree violations 
    setToRBTree(root, new_node); 
} 
  
// Function to do inorder and level order traversals 
void RBTree:: inorder() {  
    inorderHelper(root);
} 

void printTreeHelper( struct node * root,int level) {
    if (root != NULL) {
       for(int i=0;i<level;i++){
        cout<<"\t";
        }
        if(root->left||root->right)
        cout<<root -> data<<"["<<abs(getHeight(root->left)-getHeight(root->right))<<"]"<<"["<<root->color<<"]"<<endl;
        else
        cout<<root -> data<<"["<<root->color<<"]"<<endl;
        printTreeHelper(root -> left,level+1);   
        printTreeHelper(root -> right,level+1);
    }
}

void RBTree :: printTree() {
    printTreeHelper(root,0);
}


/* Function to print root to leaf path for a leaf 
   using parent nodes stored in map */
void printTopToBottomPath(struct node* curr, map<struct node*, struct node*> parent) 
{ 
    stack<struct node*> stk; 
  
    // start from leaf node and keep on pushing 
    // nodes into stack till root node is reached 
    while (curr) 
    { 
        stk.push(curr); 
        curr = parent[curr]; 
    } 
  
    // Start popping nodes from stack and print them 
    while (!stk.empty()) 
    { 
        curr = stk.top(); 
        stk.pop(); 
        cout << curr->data << " "; 
    } 
    cout << endl; 
} 
  
/* An iterative function to do preorder traversal 
   of binary tree  and print root to leaf path 
   without using recursion */
void printRootToLeaf(struct node* root) { 
    // Corner Case 
    if (root == NULL) 
        return; 
  
    // Create an empty stack and push root to it 
    stack<struct node*> nodeStack; 
    nodeStack.push(root); 
  
    // Create a map to store parent pointers of binary 
    // tree nodes 
    map<struct node*, struct node*> parent; 
  
    // parent of root is NULL 
    parent[root] = NULL; 
  
    /* Pop all items one by one. Do following for 
       every popped item 
        a) push its right child and set its parent 
           pointer 
        b) push its left child and set its parent 
           pointer 
       Note that right child is pushed first so that 
       left is processed first */
    while (!nodeStack.empty()) 
    { 
        // Pop the top item from stack 
        struct node* current = nodeStack.top(); 
        nodeStack.pop(); 
  
        // If leaf node encountered, print Top To 
        // Bottom path 
        if (!(current->left) && !(current->right)) 
            printTopToBottomPath(current, parent); 
  
        // Push right & left children of the popped node 
        // to stack. Also set their parent pointer in 
        // the map 
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
    printPathsHelper(root->left);
}

void RBTree :: printPaths(){
    printPathsHelper(root);
}