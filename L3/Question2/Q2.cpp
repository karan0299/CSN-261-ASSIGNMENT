#include<bits/stdc++.h>
using namespace std;

void insert(struct nodeList * list , int new_data);

map <int , vector<int> > tree;

struct node {
    int data;
    struct node* right; node* down;
};

struct nodeList {
    struct node* head;
    int size;
};

int ans = 0;

nodeList* initialize(){
    struct nodeList* new_nodeList = new (struct nodeList); 
    new_nodeList->head = NULL;
    new_nodeList->size = 0;
    return new_nodeList;
}

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



void printAnswer(){
    cout<<ans<<endl;
}

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

    
    struct nodeList* dp = initialize();

    fillDp(dp,input);
    int max = findMax(dp);
    struct nodeList* calc = initialize2d(max);

    countAnswer(calc,dp,n);

    printAnswer();
    
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
                        cout<<j+1<<" "<<m<<" "<<v[i]<<endl;
                    }
                }
            }
        }
        else if(v.size() > 1){
            
            for(int i=1;i<v.size();i++ ){
                int k=1;
                for(int j = v[0];j<=v[i];j=j+v[k++]-1){
                    for(int m=j+2;m<=v[i];m++){
                        cout<<j+1<<" "<<m<<" "<<v[i]<<endl;
                    }
                }
            }
        }

    }
    return 0;
}