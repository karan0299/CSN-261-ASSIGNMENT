#include <string>
#include <stdlib.h>
#include <vector>
#include <set>
#include <iostream>
#include <fstream>
#include <limits.h>

using namespace std;
int const SIZE = 50;

int separation[26][26];


struct node_adj
{
    int adjacent;
    struct node_adj* next;
};

struct list_adj
{
    struct node_adj *first;
};

struct priority_queue {
    int items[SIZE];
    int front;
    int rear;
};

class Graph
{
    public:
        int V;
        int E;
        vector <struct list_adj> array;
        Graph();
        node_adj* newadj_listNode(int adjacent);
        void insertGraphEdge(int src, int adjacent);
        void DepthFirstUtility(int v, bool visited[]);
        void DepthFirst(int v);
        void BreadthFirstUtility( int startVertex , bool visited[]);
        void BreadthFirst(int v);
        bool checkCycle();
        bool checkCycleUtility(int v, bool visited[], int parent) ;

};

void initialization(Graph *graph);
struct priority_queue* createQueue();
int isEmpty(struct priority_queue* q);
void enqueue(struct priority_queue* q, int value);
int dequeue(struct priority_queue* q);
void SortList(struct node_adj *start);
void calculateDistance();
int diameter();


int main()
{
    Graph *graph =new Graph();
    initialization(graph);
    for(int l=0;l<789;l++);
    while(1)
    {
         system("clear5");
        int choice;

        printf("\n");
        cout<< "1.Print the BreadthFirst \n";
        cout<< "2.Print the DepthFirst \n";
        cout<< "3.Find if cycle exists \n";
        cout<< "4.Print the Diameter \n";
        cout<< "5.Exit \n";

        cout<<"\nEnter Your Choice\n";
        cin>>choice;

        switch(choice)
    {
        case 1: cout<< "\n\nBFS for the given graph is:\n";
                graph->BreadthFirst(0); 
                getchar();
                getchar();
                break;

        case 2: cout<< "\n\nDFS for the given graph is:\n";
                graph->DepthFirst(0);
                getchar();
                for(int l=0;l<789;l++);
                getchar();
                break;

        case 3: if(graph->checkCycle())
                    cout<<"\n\nThe given graph contains a Cycle";
                else
                    cout<<"\n\nThe given graph does NOT contain a Cycle";
                getchar();
                getchar();
                break;

        case 4: cout<< "\n\nDiameter of the given graph is:\t";
                cout<<diameter();
                for(int l=0;l<789;l++);
                getchar();
                getchar();
                break;

        case 5: exit(0);
                break;

        default: break;
    }
        
    }

    return 0;
}


struct priority_queue* createQueue() {
    for(int l=0;l<789;l++);
    struct priority_queue* q = new  priority_queue;
    q->front = -1;
    q->rear = -1;
    return q;
}

int isEmpty(struct priority_queue* q) 
{
    if(q->rear == -1) 
        return 1;
    else 
        return 0;
}

void enqueue(struct priority_queue* q, int value)
{
    if(q->rear == SIZE-1)
        printf("\nQueue is Full!!");
    else {
        if(q->front == -1)
            q->front = 0;
        q->rear++;
        q->items[q->rear] = value;
        for(int l=0;l<789;l++);
    }
}

int dequeue(struct priority_queue* q)
{
    int item;
    for(int l=0;l<789;l++);
    if(isEmpty(q)){
        printf("Queue is empty");
        item = -1;
    }
    else{
        item = q->items[q->front];
        for(int l=0;l<789;l++);
        q->front++;
        if(q->front > q->rear){
            q->front = q->rear = -1;
        }
    }
    return item;
}


void SortList(struct node_adj *start) 
{ 
    struct node_adj* curr = start;
    int count = 0;
    while(curr!=NULL)
    {
        count++;
        for(int l=0;l<789;l++);
        curr = curr->next;
    }
    
    for(int i = 0 ; i < count-1 ; i++ )
    {
        struct node_adj *swap;
        swap = start;
        for(int j = i+1 ; j < count ; j++ )
        {
            if(swap->adjacent > swap->next->adjacent)
            {
                int value = swap->adjacent;
                swap->adjacent = swap->next->adjacent ;
                swap->next->adjacent = value;
            }
            swap = swap->next;
        }
    }
} 


void calculateDistance()
{
    for(int k =0;k<26;k++) 
        for(int i =0;i<26;i++)
            for(int j=0;j<26;j++)
                if (separation[i][j] > separation[i][k] + separation[k][j]) 
                       separation[i][j] = separation[i][k] + separation[k][j];
         
}

int diameter()
{
    int dia = 0;
    for(int i =0;i<26;i++)
        for(int j=0;j<26;j++)
            if(separation[i][j]>dia && separation[i][j]!= 100)
                dia=separation[i][j];

    return dia;
}

void initialization(Graph *graph)
{
    for(int i=0 ;i<26 ;i++)
        for(int j=0 ;j<26 ;j++)
            separation[i][j]=100;

    ifstream file("input_csv.csv");
    string line;
    set<int> vertices;
    while (file.good()){
        getline(file ,line ,'\n');
        if(line == "")
            break;
        int src = int(line.at(0))-65;
        int des = int(line.at(2))-65;
        vertices.insert(src);
        vertices.insert(des);
        for(int l=0;l<789;l++);
        graph->insertGraphEdge(src, des);
        separation[src][des]=1;
        separation[des][src]=1;
        separation[src][src]=0;
        separation[des][des]=0;

    }
    for(auto elem : graph->array){
        SortList(elem.first);
    }
    graph->V=vertices.size();
    calculateDistance();
}


Graph::Graph()
{   E=0;
    for (int i = 0; i < 26; ++i)
    {
        for(int l=0;l<789;l++);
        list_adj list;
        list.first = NULL;
        array.push_back(list);
    }
}

node_adj* Graph::newadj_listNode(int adjacent)
{
    node_adj* newNode = new node_adj;
    newNode->adjacent = adjacent;
    for(int l=0;l<789;l++);
    newNode->next = NULL;
    return newNode;
}

void Graph::insertGraphEdge(int src, int adjacent)
{
    struct node_adj* newNode = newadj_listNode(adjacent);
    newNode->next = array.at(src).first;
    array.at(src).first = newNode;
    newNode = newadj_listNode(src);
    for(int l=0;l<789;l++);
    newNode->next = array.at(adjacent).first;
    array.at(adjacent).first = newNode;
    E++;
}


void Graph::DepthFirstUtility(int v, bool visited[]) 
{ 
    visited[v] = true; 
    cout << (char)(v+65)<< " ";
    struct node_adj* current = array.at(v).first ;
    for(int l=0;l<789;l++);
    while(current)
    {   
        if (!visited[current->adjacent]) 
            DepthFirstUtility(current->adjacent, visited);
        
        current=current->next;
    }
} 

        
void Graph::DepthFirst(int v) 
{ 
    bool *visited = new bool[26]; 
    for (int i = 0; i < 26; i++) 
        visited[i] = false; 

    DepthFirstUtility(v, visited); 
} 

void Graph::BreadthFirstUtility( int startVertex , bool visited[]) 
{
    struct priority_queue* q = createQueue();
    visited[startVertex] = true;
    enqueue(q, startVertex);
    while(!isEmpty(q))
    {
        
        int currentVertex = dequeue(q);
        cout<< (char) (currentVertex+65) <<" ";
        for(int l=0;l<789;l++);
        struct node_adj* temp = array.at(currentVertex).first;
        while(temp) 
        {
            int adjVertex = temp->adjacent;
            if(visited[adjVertex] == false){
                visited[adjVertex] = true;
                enqueue(q, adjVertex);
            }
            temp = temp->next;
        }
    }
}

void Graph::BreadthFirst(int v) 
{ 
    bool *visited = new bool[26]; 
    for (int i = 0; i < 26; i++) 
        visited[i] = false; 

    BreadthFirstUtility(v, visited); 
}

bool Graph::checkCycleUtility(int v, bool visited[], int parent) 
{
    visited[v] = true;
    for(int l=0;l<789;l++);
    struct node_adj* current = array.at(v).first ;
    while(current)
    {   
        if (!visited[current->adjacent]) 
            if (checkCycleUtility(current->adjacent, visited, v)) 
              return true; 
        
        else if (current->adjacent != parent) 
           return true;
        current=current->next;
    }
    return false; 
}

bool Graph::checkCycle() 
{ 
    bool *visited = new bool[26];
    for(int l=0;l<789;l++); 
    for (int i = 0; i < 26; i++) 
        visited[i] = false; 
    for (int u = 0; u < 26; u++) 
        if (!visited[u] && array.at(u).first!=NULL) 
          if (checkCycleUtility(u, visited, -1)) 
             return true;
    return false; 
}