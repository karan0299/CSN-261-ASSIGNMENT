#include <iostream> 
#include <fstream>
#include <string>
#include <stdlib.h>
#include <stdio.h> 
#include <limits.h> 
#include <vector>
#include <set>
#include <iterator>
#include <map>
#include <cmath> 
#include <cstdlib> 
#include <malloc.h>
using namespace std;
 
set<int> vertices;

// structure to represent a fibonacci_node in the heap 
struct fibonacci_node { 
	fibonacci_node* parent; // Parent pointer 
	fibonacci_node* child; // Child pointer 
	fibonacci_node* left; // fibonacci_node on the left 
	fibonacci_node* right; // fibonacci_node on the right
	
	int vertex; 
	int weight; // Value of the fibonacci_node 
	int degree; // Degree of the fibonacci_node 
	char colour_mark; // Black or white colour_mark of the fibonacci_node 
	char flag; // Flag for assisting in the find_node fibonacci_node function 
}; 
 
struct fibonacci_node* base = NULL; 

// integer storing number of nodes
int node_count= 0; 

// Function to insert a fibonacci_node  
void insert_node(int vertex,int value) 
{ 
	struct fibonacci_node* node = (struct fibonacci_node*)malloc(sizeof(struct fibonacci_node)); 
	node->vertex=vertex;
	node->weight = value;
    node->colour_mark = 'W'; 
	node->flag = 'N';  
	node->degree = 0; 
	node->parent = NULL; 
	node->child = NULL; 
	node->left = node; 
	node->right = node; 

	if (base != NULL) 
	{ 
		(base->left)->right = node; 
		node->right = base; 
		node->left = base->left; 
		base->left = node; 
		if (node->weight < base->weight) 
			base = node; 
	} 
	else { 
		base = node; 
	} 
	node_count++; 
} 
// establish parent child relationship 
void establish_link(struct fibonacci_node* temporary_one, struct fibonacci_node* temporary_two) 
{ 
	(temporary_one->left)->right = temporary_one->right; 
	(temporary_one->right)->left = temporary_one->left; 
	if (temporary_two->right == temporary_two) 
		base = temporary_two; 
	temporary_one->left = temporary_one; 
	temporary_one->right = temporary_one; 
	temporary_one->parent = temporary_two; 

	if (temporary_two->child == NULL) 
		temporary_two->child = temporary_one; 
	temporary_one->right = temporary_two->child; 
	temporary_one->left = (temporary_two->child)->left; 
	((temporary_two->child)->left)->right = temporary_one; 
	(temporary_two->child)->left = temporary_one; 
	if (temporary_one->weight < (temporary_two->child)->weight) 
		temporary_two->child = temporary_one; 
	temporary_two->degree++; 
} 
// integrating the heap 
void integrate() 
{ 
	int tmp1; 
	float tmp2 = (log(node_count)) / (log(2)); 
	int tmp3 = tmp2; 
	struct fibonacci_node* array[tmp3]; 
	for (int i = 0; i <= tmp3; i++) 
		array[i] = NULL; 
	fibonacci_node* temporary_two = base; 
	fibonacci_node* temporary_one; 
	fibonacci_node* temporary_three; 
	fibonacci_node* temporary_four = temporary_two; 
	do { 
		temporary_four = temporary_four->right; 
		tmp1 = temporary_two->degree; 
		while (array[tmp1] != NULL) { 
			temporary_one = array[tmp1]; 
			if (temporary_two->weight > temporary_one->weight) { 
				temporary_three = temporary_two; 
				temporary_two = temporary_one; 
				temporary_one = temporary_three; 
			} 
			if (temporary_one == base) 
				base = temporary_two; 
			establish_link(temporary_one, temporary_two); 
			if (temporary_two->right == temporary_two) 
				base = temporary_two; 
			array[tmp1] = NULL; 
			tmp1++; 
		} 
		array[tmp1] = temporary_two; 
		temporary_two = temporary_two->right; 
	} while (temporary_two != base); 
	base = NULL; 
	for (int j = 0; j <= tmp3; j++) { 
		if (array[j] != NULL) { 
			array[j]->left = array[j]; 
			array[j]->right = array[j]; 
			if (base != NULL) { 
				(base->left)->right = array[j]; 
				array[j]->right = base; 
				array[j]->left = base->left; 
				base->left = array[j]; 
				if (array[j]->weight < base->weight) 
					base = array[j]; 
			} 
			else { 
				base = array[j]; 
			} 
			if (base == NULL) 
				base = array[j]; 
			else if (array[j]->weight < base->weight) 
				base = array[j]; 
		} 
	} 
} 

// Function to extract minimum fibonacci_node in the heap 
fibonacci_node* extract_minimum_node() 
{ 
	if (base == NULL) 
		cout << "The heap is empty" << endl; 
	else { 
		fibonacci_node* p;
		fibonacci_node* temp = base; 
		fibonacci_node* pntr; 
		pntr = temp;
		p=temp; 
		fibonacci_node* x = NULL; 
		if (temp->child != NULL) { 

			x = temp->child; 
			do { 
				pntr = x->right; 
				(base->left)->right = x; 
				x->right = base; 
				x->left = base->left; 
				base->left = x; 
				if (x->weight <= base->weight) 
					base = x; 
				x->parent = NULL; 
				x = pntr; 
			} while (pntr != temp->child); 
		} 
		(temp->left)->right = temp->right; 
		(temp->right)->left = temp->left; 
		base = temp->right; 
		if (temp == temp->right && temp->child == NULL) 
			base = NULL; 
		else { 
			base = temp->right; 
			integrate(); 
		} 
		node_count--;
		return  p;
	} 
	return NULL;
} 

// Cutting a fibonacci_node in the heap to be placed in the root list 
void trim(struct fibonacci_node* current, struct fibonacci_node* temp) 
{ 
	if (current == current->right) 
		temp->child = NULL; 

	(current->left)->right = current->right; 
	(current->right)->left = current->left; 
	if (current == temp->child) 
		temp->child = current->right; 

	temp->degree = temp->degree - 1; 
	current->right = current; 
	current->left = current; 
	(base->left)->right = current; 
	current->right = base; 
	current->left = base->left; 
	base->left = current; 
	current->parent = NULL; 
	current->colour_mark = 'B'; 
} 

// Recursive cascade cutting function 
void cascade_trim(struct fibonacci_node* temp) 
{ 
	fibonacci_node* temporary = temp->parent; 
	if (temporary != NULL) { 
		if (temp->colour_mark == 'W') { 
			temp->colour_mark = 'B'; 
		} 
		else { 
			trim(temp, temporary); 
			cascade_trim(temporary); 
		} 
	} 
} 

// Function to decrease the value of a fibonacci_node in the heap 
void decrease_weight(struct fibonacci_node* current, int value) 
{ 
	if (base == NULL) 
		cout << "The Heap is Empty" << endl; 

	if (current == NULL) 
		cout << "Node not current in the Heap" << endl; 

	current->weight = value; 

	struct fibonacci_node* temp = current->parent; 
	if (temp != NULL && current->weight < temp->weight) { 
		trim(current, temp); 
		cascade_trim(temp); 
	} 
	if (current->weight < base->weight) 
		base = current; 
} 

// Function to find the given fibonacci_node 
void find_node(struct fibonacci_node* base , int vertex, int value) 
{ 
	struct fibonacci_node* current = NULL; 
	fibonacci_node* temporary_five = base; 
	temporary_five->flag = 'Y'; 
	fibonacci_node* found_ptr = NULL; 
	if (temporary_five->vertex == vertex) { 
		found_ptr = temporary_five; 
		temporary_five->flag = 'N'; 
		current = found_ptr; 
		decrease_weight(current, value); 
	} 
	if (found_ptr == NULL) { 
		if (temporary_five->child != NULL) 
			find_node(temporary_five->child,vertex,value); 
		if ((temporary_five->right)->flag != 'Y') 
			find_node(temporary_five->right,vertex,value); 
	} 
	temporary_five->flag = 'N'; 
	current = found_ptr; 
} 



std::map<std::pair<int,int>, int> edge_map;

struct Adjacency_list_node { 
    int destination; 
    int wgt; 
    struct Adjacency_list_node* next; 
}; 
  
class Adjacency_list {
    public:
    Adjacency_list(){ first = NULL; } 
    struct Adjacency_list_node* first; 
};

struct Adjacency_list_node* new_adj_node(int destination, int wgt) 
{ 
    struct Adjacency_list_node* newNode = (struct Adjacency_list_node*)malloc(sizeof(struct Adjacency_list_node)); 
    newNode->destination = destination; 
    newNode->wgt = wgt; 
    newNode->next = NULL; 
    return newNode; 
} 
  
  
class Graph {
    public:
        int V;
        int E; 
        Graph();
        void addEdge(int source, int destination, int wgt);
        void getVertices(); 
        vector<Adjacency_list> array; 
};

Graph :: Graph(){
    E=0;
    for(int i=0;i<10000;i++){
        Adjacency_list a;
        a.first = NULL;
        array.push_back(a);
    }
}
  
void Graph:: addEdge(int source, int destination, int wgt) { 
    struct Adjacency_list_node* newNode = new_adj_node(destination, wgt); 
    newNode->next = (array.at(source)).first; 
    (array.at(source)).first = newNode; 
  
    newNode = new_adj_node(source, wgt); 
    newNode->next = (array.at(destination)).first; 
    (array.at(destination)).first = newNode;
    E++; 
}



void print_minimum_span_tree(int array[], int n) 
{ 
    ofstream fout;
    fout.open("graph.tre");
    fout<<"(";
    int all = 0;
    int wgt = 0;
    for (int i = 1; i < n; ++i){
		if (vertices.find(i) == vertices.end()||vertices.find(array[i]) == vertices.end())
			continue;
        if(edge_map[std::make_pair(array[i],i)]){
            wgt = edge_map[std::make_pair(array[i],i)];
        } 
        else 
            wgt = edge_map[std::make_pair(i,array[i])];
        cout<<(char)(array[i]+65)<<"---"<<(char)(i+65)<<"    "<<wgt<<endl;
        fout<<"("<<(char)(array[i]+65)<<","<<(char)(i+65)<<"),";
        all=all+wgt;
    }
    fout<<")"<<endl;
    fout.close();
    cout<<"Total wgt = "<<all<<endl;
    system("python3 command.py");
} 

void prim_algo(Graph* graph) 
{ 
    int V = graph->V; // Get the number of vertices in graph 
    int parent[26]; // Array to store constructed MST 
    int weight[26]; // weight values used to pick minimum wgt edge in cut

    int *array = new int[26*sizeof(int)];  
   
  
    for (int vertex = 0; vertex <26; ++vertex) { 
     if(vertices.find(vertex) == vertices.end())
	 	continue;
        parent[vertex] = -1; 
        weight[vertex] = INT_MAX;
        if(vertex==0)
            weight[vertex] = 0;
        insert_node(vertex,weight[vertex]);
    } 
  
        while(base!=NULL){

        struct fibonacci_node *p = extract_minimum_node();
        int u = p->vertex; 
        array[u]=1;
  
        struct Adjacency_list_node* pnode = graph->array.at(u).first; 
        while (pnode != NULL) { 
            int vertex = pnode->destination; 

            if (!array[vertex] && pnode->wgt < weight[vertex]) {   
                parent[vertex] = u; 
                find_node(base, vertex , pnode->wgt);
                weight[vertex] = pnode->wgt; 
            } 
            pnode = pnode->next; 
        } 
    } 
  
    print_minimum_span_tree(parent, 26); 
} 



int main() 
{ 
    Graph *graph = new Graph();

    ifstream file("input_csv.csv");
    string line;
    
    while ( file.good() ){ 
            getline ( file, line, '\n' );
            if(line == "")
                break;
            int src = int(line.at(0))-65;
            int des = int(line.at(2))-65;
            int w = int(line.at(4))-48;
            edge_map[std::make_pair(src,des)] = w;
            vertices.insert(src);
            vertices.insert(des);
            graph->addEdge(src,des,w);
    }
    graph->V=vertices.size();
    prim_algo(graph);
    return 0;
}