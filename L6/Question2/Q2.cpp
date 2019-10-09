#include <iostream>
#include<algorithm>
#include <vector>
#include <fstream>

using namespace std;

void insert(struct heap * tr,int p);
void stabilize(heap * tr);
void merge(heap * tr);
void printTree(struct node * elem);

struct node {
    int order;
    int c;
    vector <struct node *> children;
};

struct tree {
    node* top;
};

struct heap {
    vector < tree *> roots;

};


void insert(struct heap * tr,int p){
    node * new_node = new node;
    new_node->order = 0;
    new_node->c = p;

    tree * new_tree = new tree;
    new_tree->top = new_node;
    (tr->roots).push_back(new_tree);

    stabilize(tr);
}

void stabilize(heap * tr){
    int size = (tr->roots).size();
    if(size>1){
        if((tr->roots).at(size-1)->top->order == (tr->roots).at(size-2)->top->order)
        {
            merge(tr);
        }
    }
}

void merge(heap * tr){
    int size = (tr->roots).size();
    tree *last = (tr->roots).at(size-1);
    tree *lastsecond = (tr->roots).at(size-2);
    (tr->roots).pop_back();
    (tr->roots).pop_back();

    if(last->top->c < lastsecond->top->c){
        last->top->children.insert(last->top->children.begin(),(lastsecond->top));
        last->top->order++;
        (tr->roots).push_back(last);
    }
    else{
        lastsecond->top->children.insert(lastsecond->top->children.begin(),(last->top));
        lastsecond->top->order++;
        (tr->roots).push_back(lastsecond);
    }
    stabilize(tr);
}


void printHeap(heap* tr){
    for( auto elem: tr->roots){
        cout<<elem->top->c<<" ";
        printTree(elem->top);
        cout<<endl;
    }
}

void printTree(struct node * elem){
    if((elem->children).empty())
        return;
    for( auto e: elem->children){
        cout<<e->c<<" ";
        printTree(e);
    }
}

void tree_file(struct node* parent, ofstream &fout,struct heap * tr)
{
    if(parent->children.empty())
        return;

    for(auto element : parent->children)
    {   fout<<element->c<<"[color=\"olivedrab\", style=\"filled\" fillcolor=\"olivedrab2\"]"<<endl;
        fout<<parent->c<<"--"<<element->c<<endl;
        tree_file(element,fout,tr);
    }
}

void heap_file(ofstream &fout,struct heap * tr)
{
    for( auto element : tr->roots)
    {   fout<<element->top->c<<"[color=\"orangered\", style=\"filled\" fillcolor=\"orange\"]"<<endl;
        tree_file(element->top,fout,tr);
    }
}

void createDOTfile(int vertices,struct heap * tr)
{
    int i=0;
    ofstream fout;
    fout.open("graph.dot");
    fout<<"graph binomialHeap{"<<endl;
    heap_file(fout,tr);
    fout<<"}"<<endl;
    fout.close();
}

int main(){
    struct heap * tr = new (struct heap);
    int n;
    cout<<"Enter number of vertices"<<endl;
    cin>>n;
    int p;
    cout<<"Enter vertices"<<endl;
    for(int i=0;i<n;i++){
        cin>>p;
        insert(tr,p);
    }
    reverse((tr->roots).begin(),(tr->roots).end());
    printHeap(tr);
    createDOTfile(n,tr);
}