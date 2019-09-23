/** 
*@file Q2.cpp
*@brief this  file will contain all required 
*definitions and basic utilities functions.
*
*@author Karanpreet Singh
*
*@date 04/08/19
*/

#include<bits/stdc++.h>
#include <string>
#include <algorithm>
#include <chrono>
using namespace std::chrono; 
using namespace std;



/// Structure to store data for the one node of linked list
struct node {
    /// variable that stores the data in node
    int data;
    /// right link and down link for the node
    struct node* right; node* down;
};

/// Structure to the store the pointer the head of the linked list
struct nodeList {
    struct node* head;
    int size;
};

/// global variable which stores the total number of required triplets
int ans = 0;

/// vector that stores the indices where cummulative xor is same
map <int , vector<int> > tree;

nodeList* initialize();
nodeList* initialize2d(int n);
void insert(struct nodeList * list , int new_data); 
void fillDp(struct nodeList * dplist,struct nodeList * inplist);
int findMax(struct nodeList * dplist);
int get(struct nodeList * list , int m, int n);
void setElement(struct nodeList * list , int m, int n,int dt);
void countAnswer(struct nodeList * calc , struct nodeList * dp,int n);
void printAnswer();



int main(){

    
    
    

    struct nodeList* input = initialize();

    cout<<"Enter the value of n"<<endl;
    int n;
    cin>>n;
    cout<<"Enter the array values"<<endl;

    int k;
    for(int i=0;i<n;i++){
        cin>>k;
        insert(input,k);
    }

    auto start = high_resolution_clock::now();
    struct nodeList* dp = initialize();

    fillDp(dp,input);
    int max = findMax(dp);
    struct nodeList* calc = initialize2d(max);

    countAnswer(calc,dp,n);

    printAnswer();

    vector<string> output;
    vector<string>::iterator it;

    for(auto elem : tree)
    {
        vector <int> v;
        v = elem.second;
        int n =elem.first;

        if(n==0){
            v.insert(v.begin(),0);
            for(int i=1;i<v.size();i++ ){
                int k=1;
                for(int j = v[0];j<=v[i];j=j+v[k++]){
                    for(int m=j+2;m<=v[i];m++){
                        string str;
                        str = to_string(j+1);
                        str=str + " ";
                        str = str+to_string(m);
                        str=str + " ";
                        str = str+to_string(v[i]);
                        output.push_back(str);
                    }
                }
            }
        }
        else if(v.size() > 1){
            
            for(int i=1;i<v.size();i++ ){
                int k=1;
                for(int j = v[0];j<=v[i];j=j+v[k++]-1){
                    for(int m=j+2;m<=v[i];m++){
                        string str;
                        str = to_string(j+1);
                        str=str + " ";
                        str = str+to_string(m);
                        str=str + " ";
                        str = str+to_string(v[i]);
                        output.push_back(str);
                    }
                }
            }
        }

    }
    sort(output.begin(), output.end());
    cout<<" i j k in lexographical order \n";
    for (auto it=output.begin(); it!=output.end(); ++it)
    cout << " " << *it<<endl;

    auto stop = high_resolution_clock::now();
    auto duration =duration_cast<microseconds>(stop - start);
    cout << "CPU Time taken "<< duration.count() << " microseconds" << endl;

    return 0;
}



/**
*This method will be used inintialize the 1D node 
*@author Karanpreet Singh
*@date 04/08/19
*/
nodeList* initialize(){
    struct nodeList* new_nodeList = new (struct nodeList); 
    new_nodeList->head = NULL;
    new_nodeList->size = 0;
    return new_nodeList;
}

/**
*This method will be used inintialize the 2D node with the given data
*@author Karanpreet Singh
*@param n data to be inserted into the node
*@date 04/08/19
*/
nodeList* initialize2d(int n){
    struct nodeList* new_nodeList = new (struct nodeList);
    new_nodeList->head = NULL;
    new_nodeList->size = 0;
    for(int i = 0; i<=n ; i++){
        insert(new_nodeList, 0);
    }

    struct  node* currentright = new_nodeList->head;
    for(int i = 0; i<=n ; i++){
        struct node* current = currentright;
        for(int j=0;j<2;j++){
        struct node* new_node = new (struct node);
        new_node->data = 0;
        new_node->right = NULL;
        new_node->down = NULL;
        current->down = new_node;
        current = current->down;
        }
        currentright = currentright->right;
    }
    return new_nodeList;
}

/**
*This method will be used to insert the node  in the linked list
*@author Karanpreet Singh
*@param list pointer to the list to which data is to be inserted
*@param new_data data to be inserted
*@date 04/08/19
*/
void insert(struct nodeList * list , int new_data) { 
    struct node* new_node = new (struct node);
    new_node->data = new_data;
    new_node->right = NULL;
    new_node->down = NULL;
    list->size++;
    if(list->head==NULL){
        list->head = new_node;
        return;
    }
    struct node* current = list->head;
    while(current->right!=NULL){
        current = current->right;
    };
    current->right = new_node;
    //delete current;
} 

/**
*This method will be used to create the cummulative xor linked list
*@author Karanpreet Singh
*@param dplist 1D linked that stores the cummulative xor
*@param inplist 1D linked from the triplets are to be counted
*@date 04/08/19
*/
void fillDp(struct nodeList * dplist,struct nodeList * inplist){
    struct node* currentInp = inplist->head;
    insert(dplist,currentInp->data);
    int last_element = currentInp->data;
    currentInp=currentInp->right;
    while(currentInp!=NULL){
        int dpelement = last_element^currentInp->data;
        insert(dplist,dpelement);
        currentInp=currentInp->right;
        last_element = dpelement;
    }
}

/**
*This method will be used to create individual node of a quad tree
*@author Karanpreet Singh
*@param dplist 1D linked that stores the cummulative xor 
*@date 04/08/19
*/
int findMax(struct nodeList * dplist){
    struct node* current = dplist->head;
    int max = current->data;
    while(current){
        if(current->data>max)
            max=current->data;
        current = current->right;
    }
    return max;
}

/**
*This method will be used to get the data from the particular node of the linked list
*@author Karanpreet Singh
*@param list 2D linked List that the previous values of indices corresponding given cummulative xor value
*@param n correspoding to which get downward linked list node value
*@date 04/08/19
*/
int get(struct nodeList * list , int m, int n){
    struct node* current1 = list->head;
    while(n>0){
        current1 = current1->right;
        n--;
    };

    if(current1->down!=NULL){
        while(m!=1){
            current1 = current1->down;
            m--;
        };
        int k =  current1->data;
        return k;
    }
    int k =  current1->data;
    return k;
}

/**
*This method will be used set the node of 2D linked list according the given data
*@author Karanpreet Singh
*@param list Pointer to the 2D linked list 
*@param  n correspoding to which downward linked list is filled
*@date 04/08/19
*/
void setElement(struct nodeList * list , int m, int n,int dt){
    struct node* current2 = list->head;
    while(n>0){
        current2 = current2->right;
        n--;
    };

    while(m>1){
        current2 = current2->down;
        m--;
    };

    current2->data = dt;
}

/**
*This method will be used to actually to actually count the number of required triplets
*@author Karanpreet Singh
*@param calc 2D linked List that the previous values of indices corresponding given cummulative xor value
*@param  nodeList 1D linked that stores the cummulative xor 
*@date 04/08/19
*/
void countAnswer(struct nodeList * calc , struct nodeList * dp,int n){
    for(int i = 1;i<=n;i++){
        int m = get(dp,0,i-1);
        if(get(calc,1,m)==0){
            if(m==0){
                ans=ans+(i-1);
                tree[m].push_back(i);
                setElement(calc,1,m,1);
                setElement(calc,2,m,i);
                setElement(calc,3,m,i-1);
            }
            else {
                int temp = get(calc,1,m);
                tree[m].push_back(i);
                setElement(calc,1,m,temp+1);
                setElement(calc,2,m,i);
            }
        }
        else {
            if(m==0){
                tree[m].push_back(i);
                int tmp = get(calc,1,m);
                setElement(calc,1,m,tmp+1);
                int tmp1 = get(calc,3,m);
                int tmp2 = get(calc,2,m);
                int tmp3 = tmp1+ ((i-tmp2)*(tmp+1)) -1;
                setElement(calc,3,m,tmp3);
                ans = ans +tmp3;
                setElement(calc,2,m,i);
            }
            else{
                tree[m].push_back(i);
                int tmp = get(calc,1,m);
                int tmp1 = get(calc,3,m);
                int tmp2 = get(calc,2,m);
                int tmp3 = tmp1+ ((i-tmp2)*tmp) -1;
                setElement(calc,3,m,tmp3);
                setElement(calc,1,m,tmp+1);
                ans = ans +tmp3;
                setElement(calc,2,m,i);
            }
        }
    }
}

/**
*This method will be used to print the number of required triplets
*@author Karanpreet Singh
*@date 04/08/19
*/
void printAnswer(){
    cout<<"Number of such triplets  = ";
    cout<<ans<<endl;
}
