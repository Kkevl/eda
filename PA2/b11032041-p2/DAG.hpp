#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<limits.h>
#include<list>
#include<stack>
#define NINF INT_MIN
using namespace std;

class AdjNode{
private:
    //  v = next node's name, weight = this edge weight
    int v,weight;
public:
    // initialize
    AdjNode(int _v, int _weight){
        v = _v;
        weight = _weight;
    }
    int getV() {return v;}
    int getWeight() {return weight;}
    // vector<AdjNode> previous, next;
};

// edges' weight = width or height
class DAG{
    // define by giving the number of nodes
private:
    int V;

    vector<bool> visited;
    list<AdjNode>* adj;
    
    void topologicalSortUtil(int v//,bool visited[]
                                ,stack<int>& Stack);
public:
    int maxlength; // calculate max length untill now
    
    // need to return height and width
    DAG(int V){
        this->V = V;
        adj = new list<AdjNode>[V];
        visited.assign(V, false);
    };
    
    ~DAG(){ delete [] adj;};

    // AdjNode source,tail,connect_all;
    void addEdge(int u, int v, int weight);

    void eraseEdge(int u, int v);
    
    void longestPath(int s);
};

inline void DAG::topologicalSortUtil(int v //, vector<bool> visite
                                    ,stack<int> &Stack){
    // mark the current AdjNode as visited
    visited[v] = true;
    
    list<AdjNode>::iterator i;
    for ( i = adj[v].begin(); i != adj[v].end(); i++){
        AdjNode node = *i;
        if (!visited[node.getV()]){
            topologicalSortUtil(node.getV()//,visite
                                        ,Stack);
        }   
    
    }
    //Push current vertex to stack which stored topological sort
    Stack.push(v);
}

inline void DAG::addEdge(int u, int v, int weight){
    if (u == v)  return;
    AdjNode node(v,weight);
    adj[u].push_back(node);
}

inline void DAG::eraseEdge(int u, int v){
    if (u == v)
        return;
    list<AdjNode>::iterator it;
    int i = 0;
    for (it = adj[u].begin(); ; it++){
        if ( it->getV() == v){
            break;
        }else if ( it == adj[u].end() || i >= adj[u].size()-1 ){
            // not found, do nothing and return;
            return;
        }
        i++;
    }
    // remove idot
    if (!adj[u].empty()){
        adj[u].erase(it);
    }
    
}

inline void DAG::longestPath(int s){

    stack<int> Stack;
    vector<int> dist(V);

    // vector<bool> visited(V);
    
    for (int i = 0; i < V; i++){
        visited[i] = false;
    }

    //Call the recursive helper function to stire Topological
    //Sort starting from all vertics one by one
    for (int i = 0; i < V; i++){
        if (visited[i] == false){
            topologicalSortUtil(i//,visited
                                ,Stack);
        }        
    }
    // Initialize distances to all vertics as infinite
    // distance to source as 0
    for (int  i = 0; i < V; i++){
        dist[i] = NINF;
    }

    dist[s] = 0;
    while (Stack.empty() == false){
        int u =Stack.top();
        Stack.pop();
        list<AdjNode>::iterator i;
        if (dist[u] != NINF){
            for ( i = adj[u].begin(); i != adj[u].end(); i++){
                if (dist[i->getV()] < dist[u] + i->getWeight()){
                    dist[i->getV()] = dist[u] + i->getWeight();
                }
            }
        }
        // then you got logest distances by dist[] list
    }

    // debug use
    // cout<<"Following are longest distance from vertex "<< s <<endl;
    // for (int i = 0; i < V; i++){
    //     (dist[i] == NINF) ? cout<<"INF ":cout<<dist[i]<<" ";
    // }
    // cout<<endl;
    
    maxlength = dist[V-1];
    dist.clear();
}
