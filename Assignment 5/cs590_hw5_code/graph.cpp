#include <iostream>
#include <set>
#include <queue>

#include "graph.h"

using namespace std;

Graph::Graph(int nodes)
{
    this->nodes = nodes;
    this->matrix = new int*[nodes];
    
    for (int i = 0; i < nodes; ++i) {
        (this->matrix)[i] = new int[nodes];
        
        for (int j = 0; j < nodes; ++j) {
            (this->matrix)[i][j] = 0;
        }
    }
}

Graph::Graph(int **matrix, int nodes) {
    this->nodes = nodes;
    this->matrix = new int*[nodes];
    
    for (int i = 0; i < nodes; ++i) {
        (this->matrix)[i] = new int[nodes];
        
        for (int j = 0; j < nodes; ++j) {
            (this->matrix)[i][j] = matrix[i][j];
        }
    }
}

Graph::~Graph()
{
    for (int i = 0; i < this->nodes; ++i) {
        delete[] (this->matrix)[i];
    }
    delete[] this->matrix;
}

bool Graph::set_edge(int i, int j, int edge)
{
    if (i < this->nodes && j < this->nodes && i >= 0 && j >= 0) {
        (this->matrix)[i][j] = edge;
        return true;
    }
    
    return false;
}

void Graph::dfs()
{
    set <int>* visited = new set<int>;
    cout<<"Depth First Tree"<<endl;
    dfs(0,visited);
    for (int u = 0; u < nodes; u++)
    {
        if (visited->count(u)==0)
        {
            dfs(u,visited);
        }
    }
    cout<<endl;
    delete visited;
}

void Graph::dfs(int start, set<int> *visited)
{
    cout<<start<<endl;
    visited->insert(start);
    for (int i = 0; i < nodes; i++)
    {
        if (visited->count(i)==0 && matrix[start][i] > 0)
        {
            dfs(i,visited);
        }
    }
}
void Graph::bfs(int start)
{
    if ( start < 0 || start > nodes - 1 )
    {
        cout<<"Invalid start node for BFS."<<endl;
        return;
    }
    set <int>* visited = new set<int>;
    bfs(start,visited);
}
void Graph::bfs(int start, set<int> *visited)
{
    queue<int> Q;
    visited->insert(start);
    cout<<"Breadth First Traversal:"<<endl;
    cout<<start<<"->";
    Q.push(start);
    while (!Q.empty()){
        int u = Q.front();
        Q.pop();
        for (int i = 0; i < nodes; i++){
            if (visited->count(i)==0 && matrix[u][i] > 0)
            {
                visited->insert(i);
                if(i==nodes-1)
                {
                    cout<<i;
                }
                else
                {
                    cout<<i<<"->";
                }
                Q.push(i);
            }
        }
    }
    cout<<endl;
    delete visited;
}

