#include <bits/stdc++.h>
#include <vector>
#include <set>
#include <algorithm>
#include <fstream>
#include <string>
using namespace std;

struct edge {
    int weight;
    int source;
    int dest;
};

class Graph {
    private:
        void insertEdge(vector<edge>& Edge, int w, int src,int des);
    public:
        vector<edge> Edges;
        int V,E;
        int count;
        Graph(){count = 0 ;}
        void insert(int src , int des ,int w){ insertEdge(Edges,w,src,des); }
        void getVertices();

};

void Graph:: insertEdge(vector<edge>& Edge, int w, int src,int des){
    struct edge e = { w, src, des } ;
    count++;
    Edge.push_back(e);
}

void Graph:: getVertices(){
    set<int> vertices;
    for(auto elem: Edges){
        int src = elem.source;
        int dest = elem.dest;
        vertices.insert(src);
        vertices.insert(dest);
    }
    V = vertices.size();
}

bool compare(edge e1 , edge e2){
    if(e1.weight<e2.weight)
        return 1;
    return 0;
}

int find(int parent[], int i)  
{  
    if (parent[i] == -1)  
        return i;  
    return find(parent, parent[i]);  
} 

void Union(int parent[], int x, int y)  
{  
    int xp = find(parent, x);  
    int yp = find(parent, y);  
    if(xp != yp) 
    {  
        parent[xp] = yp;  
    }  
} 

void makeDOTfile(edge MST[],int len){
    int i=0;
    ofstream fout;
    fout.open("graph.dot");
    fout<<"graph kruskal{"<<endl;
    while(len-->1){
        char src = (char)((MST[i].source+64));
        char des = (char)(MST[i].dest+64);
        fout<<src<<"--"<<des<<"["<<"label = "<<MST[i].weight<<"];"<<endl;
        i++;
    }
    fout<<"}"<<endl;
    fout.close();
}

void kruskal(Graph graph){
   sort((graph.Edges).begin(), (graph.Edges).end(), [] (const auto& lhs, const auto& rhs) {
    return lhs.weight < rhs.weight;
    });
    edge *MST = new edge[graph.V*sizeof(int)];
    int c=0;
    int *parent = new int[graph.V * sizeof(int)];
    for(int i=0;i<graph.V;i++){
        parent[i] = -1;
    }  
    for(auto elem : graph.Edges){
        int x = find(parent, elem.source);  
        int y = find(parent, elem.dest);  
  
        if (x == y)  
           continue;

        MST[c++] = elem;  
        Union(parent, x, y);

        if(c==graph.V)
            break;
    }

    int totalWeight = 0;
    for(int i=0;i<graph.V-1;i++){
        cout<<(char)(MST[i].source+64)<<"   "<<(char)(MST[i].dest+64)<<"  "<<MST[i].weight<<endl;
        totalWeight+=MST[i].weight;
    }
    cout<<"total weight :"<<totalWeight<<endl;

    makeDOTfile(MST , graph.V);  
}


int main(){
    Graph graph;
     graph.insert(1,2,10);
    graph.insert(1,3,6);
    graph.insert(1,4,5);
    graph.insert(2,4,15);
    graph.insert(3,4,4);
    // ifstream file("input_csv.csv");
    // string value;
    // while ( file.good() ){ 
    //         getline ( file, value, '\n' );
    //         if(value == "")
    //             break;
    //         string delimiter = ",";
    //         int pos = value.find(delimiter);
    //         string src_string = value.substr(0,pos);
    //         string remaining = value.substr(pos+1,value.length());
    //         pos = remaining.find(delimiter);
    //         string des_string = remaining.substr(0,pos);
    //         string weight = remaining.substr(pos+1,remaining.length());
    //         int src = int(src_string.at(0))-64;
    //         int des = int(des_string.at(0))-64;
    //         int w = stoi(weight);
    //         graph.insert(src,des,w);
    // }
    graph.getVertices();
    kruskal(graph);
    return 0;
}
