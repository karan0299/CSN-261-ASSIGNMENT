/** 
*@file MAT.c
*@brief this header file will contain all required 
*definitions and basic utilities functions.
*
*@author Karanpreet Singh
*
*@date 04/08/19
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

/// Stores the height of quad tree
int t_height;

/// Static variable to store value of current node while traversing
static int nv=1;

/// Static to store value of current level in quad tree while traversing
static int lev=0;

/// Static variable to store value of current node while traversing
static int node_value = 1;

/// Structure to encapsulate the point of a array
struct Point {
    int x;
    int y;
};

/// Structure to encapulate each node of quad tree
struct Node {
    /// to mark the topleft and bottom right points ,the area this node is pointing to
    struct Point topleft, btmright;
    /// whether whether region is there or not
    int bit_value;
    /// pointing to north east quad of given node
    struct Node* ne;
    /// pointing to north west quad of given node
    struct Node* nw;
    /// pointing to south east quad of given node
    struct Node* se;
    /// pointing to south west quad of given node
    struct Node* sw;
};

/**
*This method will be used to create individual node of a quad tree
*@author Karanpreet Singh
*@param topL to mark the topleft point of the area , generating node will be pointing to 
*@param btmR to mark the bottom right point of the area , generating node will be pointing to 
*@date 04/08/19
*/
struct Node * new_node(struct Point topL,struct  Point btmR);

/**
*This method will be used to generate the quad tree recursively
*@author Karanpreet Singh
*@param  arr 2D array depicting region to be mapped to quad tree
*@param  p1 to mark the topleft point of the  area for which fuction is called,
*@param  p2 bottom right to mark the topleft point of the  area for which fuction is called,
*@param  root Node point to parent node of the node if created
*@date 04/08/19
*/

void buildTree(int** arr,struct  Point p1,struct Point p2,struct Node* root);

/**
*This method will be used to return maximum of Four numbers
*@author Karanpreet Singh
*@param num1 number1
*@param num2 number2
*@param num3 number3
*@param num4 number4
*@date 04/08/19
*/

int maximum(int num1,int num2,int num3,int num4);

/**
*This helper method will be used to give the height of the quad tree recursively
*@author Karanpreet Singh
*@param node  The parent node from which height is calculated
*@date 04/08/19
*/

int height(struct Node* node);

/** 
*This helper method will be used to mark the node value of in the form of maximal square array
*@author Karanpreet Singh
*@param array Array which is to be marked
*@param node Node which is going to be marked in array 
*@date 04/08/19
*/
void mark(int** array, int n,struct Node * node);

/**
*This method will be used to print quad Tree in form (node value, bit value, level)
*@author Karanpreet Singh
*@param child Pointer to the nod of quad tree
*@date 04/08/19
*/
void printTree(struct Node * child);

/**
*This method will be used to represent the quad tree in form of maximal square array
*@author Karanpreet Singh
*@param tree Pointer to root node of passed quad tree
*@param array Pointer to maximal square array of quad tree
*@date 04/08/19
*/
void fill_outArray(struct Node * tree , int ** array);

/**
*This method will be used to print the Quad tree in maximal square array form 
*@author Karanpreet Singh
*@param array Maximal square array of quad tree
*@param size size of each dimension of array
*@date 04/08/19
*/
void printTreeInArray(int** array,int size);


void main() {

    /// to mark start and end of cpu clock
    clock_t start, end;
    /// store the time taken by cpu to perform operation 
    double cpu_time;

    start = clock ();

    /// Pointer to file containing region in form of array
    FILE * fp = fopen("sampleinput2.txt","r");

    char ch[1024];

    fgets(ch,1024,fp);

    int l= strlen(ch)/2;

    int size = (int)pow(2,(int)(log(l)/log(2))+1);

    int **arr;
    arr = (int **)malloc(size* sizeof(int *)); 
    for (int k=0; k<100; k++) 
        arr[k] = (int *)malloc(size* sizeof(int));
    
    for(int i = 0; i<size ; i++ )
        for(int j=0;j<size;j++)
           arr[i][j]=0;

    int m=0;

    int row = size-l;

    for(int i=row;i<size;i++){
       arr[row][i] = ch[m]-48;
       m=m+2; 
    }
    row++; 

    while(fgets(ch,1024,fp)){
        m=0;
        for(int i = (size-l) ;i<size;i++){
        arr[row][i] = ch[m] -48;
        m=m+2;
        }
        row++ ;
    }
    
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            printf("%d ",arr[i][j]);
        }
        printf("\n");
    }
    
    int **max_array;
    max_array = (int **)malloc(size* sizeof(int *)); 
    for (int k=0; k<100; k++) 
        max_array [k] = (int *)malloc(size* sizeof(int));

    struct Point p1,p2;
    p1.x=0;
    p2.x=size-1;
    p1.y=0;
    p2.y=size-1;

    struct Node* qtree = new_node(p1,p2);

    buildTree(arr,p1,p2,qtree);

    t_height=height(qtree);

    fill_outArray(qtree,max_array);

    end = clock();
    cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("\nCPU time Taken to form Quad tree and Maximal square array is %f \n",cpu_time);

    int op;
   
    while(1){

        printf("\n1.Enter to view tree in form (node value, bit value, level) \n2. Two view quad tree on maximal square array form \n");
        printf("Enter ur choice");
        scanf("%d",&op);
        
        switch(op){

            case 1: start = clock();
                    printTree(qtree);
                    end = clock();
                    cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;
                    printf("cpu time taken to perform printing operation is %f \n",cpu_time);             
                    break;
            case 2: start = clock();
                    printTreeInArray(max_array,size);
                    end = clock();
                    cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;
                    printf("cpu time taken to perform printing operation is %f \n",cpu_time);
                    break;
            default: exit(0);

        }
    }

}

struct Node * new_node(struct Point topL,struct  Point btmR){
    struct Node * node = (struct Node*)calloc(1,sizeof(struct Node));
    node->ne=NULL;
    node->nw=NULL;
    node->se=NULL;
    node->sw=NULL;
    node->topleft = topL;
    node->btmright = btmR;
    return node;
}

void buildTree(int** arr,struct  Point p1,struct Point p2,struct Node* root){
    if(abs(p1.x - p2.x) < 1 && abs(p1.y - p2.y) < 1){
    root->bit_value = arr[p1.y][p1.x];
    return ;
    }

    bool stop = false;
    int xor=arr[p1.y][p1.x];
    int k=0;

    for(int i=p1.y;i<=p2.y &&!stop;i++){
        for(int j=p1.x;j<=p2.x &&!stop;j++){
            
            k=xor^arr[i][j];

            if(k==1){

                struct Point c1,c2,c3,c4,c5,c6;

                c2.x=(p1.x+p2.x)/2+1; c2.y=p1.y;
                c4.x=(p1.x+p2.x)/2; c4.y=p2.y;
                c3.x=(p1.x+p2.x)/2+1; c3.y=(p1.y+p2.y)/2+1;
                c1.x=p2.x; c1.y=(p1.y+p2.y)/2;
                c5.x=p1.x; c5.y=(p1.y+p2.y)/2+1;
                c6.x=(p1.x+p2.x)/2; c6.y=(p1.y+p2.y)/2;
                
                root->ne=new_node(p1,c6);
                buildTree(arr,p1,c6,root->ne);

                struct Node* child2=new_node(c2,c1);
                buildTree(arr,c2,c1,child2);
                

                struct Node* child3=new_node(c5,c4);
                buildTree(arr,c5,c4,child3);

                struct Node* child4=new_node(c3,p2);
                buildTree(arr,c3,p2,child4);

                root->nw = child2;
                root->se = child3;
                root->sw = child4;

                stop = true;
            }
            else {
                root->bit_value=arr[p1.y][p1.x];
            }
        }
    }    
}

int maximum(int num1,int num2,int num3,int num4){
    int max;

    max = (num1 > num2? num1 : num2);  
    max = (num3 > num4? (num3 > max? num3 : max) : (num4 > max? num4 : max));
    
    return max;
}

int height(struct Node* node){
    if(!node)
    return 0;
    else
    return maximum(height(node->ne),height(node->se),height(node->nw),height(node->sw))+1;
}

void printTree(struct Node * child){
    if(child){
        lev++;
        printTree(child->ne);
        printTree(child->nw);
        printTree(child->se);
        printTree(child->sw);
        if(!child->ne&&!child->nw&&!child->nw&&!child->nw){
            printf("%d %d %d\n",nv++,child->bit_value,lev-1);
        }
        lev--;
    }
}

void mark(int** array, int n,struct Node * node){
    for(int i=node->topleft.y;i<=node->btmright.y;i++){
        for(int j=node->topleft.x;j<=node->btmright.x;j++)
            array[i][j] = n;
    }
}

void fill_outArray(struct Node * tree , int ** array){
    if(tree){
        fill_outArray(tree->ne,array);
        fill_outArray(tree->nw,array);
        fill_outArray(tree->se,array);
        fill_outArray(tree->sw,array);
        if(!tree->ne&&!tree->nw&&!tree->nw&&!tree->nw){
            mark(array,node_value++,tree);
        }
    }
}

void printTreeInArray(int** array,int size){
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            if(array[i][j]/10==0)
            printf("%d  ",array[i][j]);
            else
            printf("%d ",array[i][j]);
        }
        printf("\n");
    }
}
