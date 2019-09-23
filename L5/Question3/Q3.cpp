#include <bits/stdc++.h>
#include <vector>
#include <set>
#include <algorithm> 
#include <limits>
#include <iterator>
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

int getMinimumValueKey(map<int,int> vertexValue,bool notInMST[]){
    int minv = 100000;
    int mink = 0;
    int i=1;
    for(auto itr = vertexValue.begin();itr != vertexValue.end();itr++){
        if((itr->second<minv)&&(notInMST[itr->first]==1)){
            minv = itr->second;
            mink = itr->first;
        }
    }
    return mink;
}

void setAdjacentValues(int min,map<int,int> &vertexValue,bool nmst[],vector<edge> Edges){
    for(auto elem : Edges){
        if((elem.source == min)&&(nmst[elem.dest]==1)){
            vertexValue[elem.dest] = elem.weight+vertexValue.at(elem.dest)- max(elem.weight,vertexValue.at(elem.dest));
        }
        if((elem.dest == min)&&(nmst[elem.source]==1)){
            vertexValue[elem.source] = elem.weight+vertexValue.at(elem.source)- max(elem.weight,vertexValue.at(elem.source));
        }

    }
}

int getParent(vector<edge> Edges,int min,int w){
   for(auto elem : Edges){
        if((elem.source == min)&&(elem.weight==w)){
            return elem.dest;
        }
        if((elem.dest == min)&&(elem.weight==w)){
            return elem.source;
        }
    }
    return -1;
}

void prim(Graph graph){
    set<int> mst;
    map<int,int> vertexValue;
    int tree[graph.V+1];
    bool notInMST[graph.V+1];
    for(int i=1;i<=graph.V;i++){
        notInMST[i] = 1;
    }
    vertexValue.insert(pair<int,int>(1,0));
    for(int i=2;i<=graph.V;i++){
        vertexValue.insert(pair<int,int>(i,1000));
    }
    int parent = 0;
    int min = getMinimumValueKey(vertexValue,notInMST);
    mst.insert(min);
    notInMST[min]=0;
    setAdjacentValues(min,vertexValue,notInMST,graph.Edges);
    // for(auto itr = vertexValue.begin();itr!=vertexValue.end();itr++){
    //         cout<<itr->second<<"   ";
    // }
    // cout<<endl;
    while(mst.size()!= graph.V){
        min = getMinimumValueKey(vertexValue,notInMST);
        mst.insert(min);
        notInMST[min]=0;
        parent = getParent(graph.Edges,min,vertexValue.at(min));
        tree[min] = parent;
        setAdjacentValues(min,vertexValue,notInMST,graph.Edges);
        // for(auto itr = vertexValue.begin();itr!=vertexValue.end();itr++){
        //     cout<<itr->second<<"   ";
        // }
        //cout<<endl;
    }
    
    int totalWeight = 0;
    ofstream fout;
    fout.open("graph.dot");
    fout<<"graph prim{"<<endl;
    for(int i=2;i<=graph.V;i++){
        char src = (char)((tree[i]+64));
        char des = (char)(i+64);
        cout<<src<<"  "<<des<<"   "<<vertexValue.at(i)<<endl;
        fout<<src<<"--"<<des<<"["<<"label = "<<vertexValue.at(i)<<"];"<<endl;
        totalWeight+=vertexValue.at(i);
    }
    fout<<"}"<<endl;
    fout.close();
    cout<<"total weight :"<<totalWeight<<endl;
}

int main(){
    Graph graph;
    // graph.insert(1,3,3);
    // graph.insert(2,3,10);
    // graph.insert(2,4,4);
    // graph.insert(3,4,2);
    // graph.insert(3,5,6);
    // graph.insert(4,5,1);
    ifstream file("input_csv.csv");
    string value;
    while ( file.good() ){ 
            getline ( file, value, '\n' );
            if(value == "")
                break;
            string delimiter = ",";
            int pos = value.find(delimiter);
            string src_string = value.substr(0,pos);
            string remaining = value.substr(pos+1,value.length());
            pos = remaining.find(delimiter);
            string des_string = remaining.substr(0,pos);
            string weight = remaining.substr(pos+1,remaining.length());
            int src = int(src_string.at(0))-64;
            int des = int(des_string.at(0))-64;
            int w = stoi(weight);
            graph.insert(src,des,w);
    }
    graph.getVertices();
    prim(graph);
    return 0;
}

