/** 
 *  @file	PS-1.c
 *  @brief	brief explanation of PS-1.c from xn
 @author karanpreet Singh
 */

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<stdbool.h>
#include <time.h>
#include <math.h>

int t_height;

struct Point {
    int x;
    int y;
};

struct Node {
    struct Point topleft, btmright;
    int bit_value;
    struct Node* ne;
    struct Node* nw;
    struct Node* se;
    struct Node* sw;
};

int count = 0;
struct Node * new_node(struct Point topL,struct  Point btmR){
   // printf("%d\n",count++);
    struct Node * node = (struct Node*)calloc(1,sizeof(struct Node));
    node->ne=NULL;
    node->nw=NULL;
    node->se=NULL;
    node->sw=NULL;
    node->topleft = topL;
    node->btmright = btmR;
    return node;
}

void homogenity(int** arr,struct  Point p1,struct Point p2,struct Node* root){
    if(abs(p1.x - p2.x) < 1 && abs(p1.y - p2.y) < 1){
    root->bit_value = arr[p1.y][p1.x];
    return ;
    }
   // printf("%d %d %d %d\n",p1.x,p1.y,p2.x,p2.y);
    bool stop = false;
    int xor=arr[p1.y][p1.x];
    int k=0;
    for(int i=p1.y;i<=p2.y &&!stop;i++){
        for(int j=p1.x;j<=p2.x &&!stop;j++){
            k=xor^arr[i][j];
            if(k==1){
                //printf("woo\n");
                struct Point c1,c2,c3,c4,c5,c6;
                c2.x=(p1.x+p2.x)/2+1; c2.y=p1.y;
                c4.x=(p1.x+p2.x)/2; c4.y=p2.y;
                c3.x=(p1.x+p2.x)/2+1; c3.y=(p1.y+p2.y)/2+1;
                c1.x=p2.x; c1.y=(p1.y+p2.y)/2;
                c5.x=p1.x; c5.y=(p1.y+p2.y)/2+1;
                c6.x=(p1.x+p2.x)/2; c6.y=(p1.y+p2.y)/2;
                
                //printf("ti\n");
                root->ne=new_node(p1,c6);
                //printf("jpp\n");
                homogenity(arr,p1,c6,root->ne);

                struct Node* child2=new_node(c2,c1);
                //printf("%d %d %d %d\n",c2.x,c2.y,c1.x,c1.y);
                homogenity(arr,c2,c1,child2);
                

                struct Node* child3=new_node(c5,c4);
                homogenity(arr,c5,c4,child3);

                struct Node* child4=new_node(c3,p2);
                homogenity(arr,c3,p2,child4);

                root->nw = child2;
                root->se = child3;
                root->sw = child4;

                // free(child2);
                // free(child3);
                // free(child4);

                stop = true;
            }
            else
            {
                
                root->bit_value=arr[p1.y][p1.x];
            }
        }
    }
    
}

int maximum(int num1,int num2,int num3,int num4)
{
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


static int nv=1;
static int lev=0;
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



void main() {
    FILE * fp = fopen("sampleinput.txt","r");

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

    for(int i = 0; i<size ; i++ ){
        for(int j=0;j<size;j++)
            printf("%d ",arr[i][j]);
        printf("\n");
    }
    
    struct Point p1,p2;
    p1.x=0;
    p2.x=size-1;
    p1.y=0;
    p2.y=size-1;
    struct Node* qtree = new_node(p1,p2);
    printf("hi\n");
    homogenity(arr,p1,p2,qtree);
    t_height=height(qtree);
    printTree(qtree);
}