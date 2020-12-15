#include <iostream>
#include <vector>
#include <algorithm>
#include "cyclebreak.h"
using namespace std;

void MakeSet(Tree forest[],int V){
    for(int i=0;i<V;i++){
        forest[i].p = i;
        forest[i].rank = 0;
    }
}

int FindSet(Tree forest[],int X){
    if(forest[X].p!=X){
        forest[X].p = FindSet(forest,forest[X].p);
    }
    return forest[X].p;
}

void Union(Tree forest[],int X, int Y){
    int Xp = FindSet(forest,X);
    int Yp = FindSet(forest,Y);
    if(forest[Xp].rank>forest[Yp].rank){
        forest[Yp].p = Xp;
    }
    else{
        forest[Xp].p = Yp;
        if(forest[Xp].rank==forest[Yp].rank){
            forest[Yp].rank = forest[Yp].rank + 1;
        }
    }
}

Graph::Graph(int V,int E){
    this->V = V;
    this->E = E;
    this->adj.reserve(V);
}

bool compare1(const vector<int> &i1,const vector<int> &i2){
    return (i1[2] > i2[2]);
}

bool compare2(const vector<int> &i1,const vector<int> &i2){
    return (i1[0] < i2[0]);
}

void Graph::reset(Vertex vertices[]){
    for(int i=0;i<this->V;i++){
        vertices[i].color = 0;
        vertices[i].pi = 0;
    }
}

vector<vector<int> > Graph::Kruskal_MST(int &cost){
    Tree *forest = new Tree[this->V];
    MakeSet(forest,this->V);
    vector<vector<int> > edges(this->E);
    vector<int> temp(3);
    vector<int> MST;
    for(int i=0;i<this->E;i++){
        edges[i].reserve(3);
    }
    int count = 0;
    cost = 0;
    for(int i=0;i<this->V;i++){
        for(int j=0;j<this->adj[i].size();j++){
            edges[count][0] = i;
            edges[count][1] = this->adj[i][j][0];
            edges[count][2] = this->adj[i][j][1];
            cost += this->adj[i][j][1];
            count+=1;
        }
    }
    sort(edges.begin(),edges.end(),compare1);
    for(int i=0;i<edges.size();i++){
        int u = edges[i][0];
        int v = edges[i][1];

        if(FindSet(forest,u)!=FindSet(forest,v)){
            MST.push_back(i);
            Union(forest,u,v);
        }
    }
    for(int i=0;i<MST.size();i++){
        cost -= edges[MST[i]-i][2];
        edges.erase(edges.begin()+MST[i]-i);
    }
    sort(edges.begin(),edges.end(),compare2);
    return edges;
}

void Graph::removeEdge(int u, int v, int w){
    vector<int> temp(2);
    temp[0] = v;
    temp[1] = w;
    vector<vector<int> >::iterator itr;
    itr = find(this->adj[u].begin(),this->adj[u].end(),temp);
    this->adj[u].erase(itr);
}

int Graph::findWeight(int u, int v){
    vector<vector<int> >::iterator itr;
    for(itr=this->adj[u].begin();itr!=this->adj[u].end();itr++){
        if((*itr)[0]==v){
            return (*itr)[1];
        }
    }
}

void Graph::cycleBreaking(vector<vector<int> >& ans, int& cost){
    cost = 0;
    // while(true){
    //     vector<vector<int> > min_edge;
    //     DFS(min_edge);
    //     if(min_edge.size()==0) break;
    //     vector<vector<int> >::iterator itr;
    //     for(itr=min_edge.begin();itr!=min_edge.end();itr++){
    //         ans.push_back(*itr);
    //         cost+=(*itr)[2];
    //         removeEdge((*itr)[0],(*itr)[1],(*itr)[2]);
    //     }
    // }
    vector<vector<int> > min_edge;
    DFS(min_edge);
}


void Graph::DFS(vector<vector<int> >& min_edge){
    Vertex *vertices = new Vertex[this->V];
    for(int i=0;i<this->V;i++){
        if(vertices[i].color==0)
        DFS_back(i,vertices,min_edge);    
    }
}

void Graph::DFS_back(int u, Vertex vertices[],vector<vector<int> >& min_edge){
    if(vertices[u].color==2){
        return;
    }
    else if(vertices[u].color==1){
        int node = vertices[u].pi;
        vector<int> cycle;
        cycle.push_back(u);
        while(node!=u){
            cycle.push_back(node);
            node = vertices[node].pi;
        }
        cycle.push_back(u);
        reverse(cycle.begin(),cycle.end());
        int minW = 99999;
        int from = 0;
        int to = 0;
        vector<int>::iterator itr;
        for(itr=cycle.begin();itr!=cycle.end()-1;itr++){
            int w = findWeight(*itr,*(itr+1));
            if(w < minW && w!=0){
                minW = w;
                from = *(itr);
                to = *(itr+1);
            }
        }
        min_edge.push_back({from,to,minW});
        return;
    }
    else{
        vertices[u].color = 1;
        vector<vector<int> >::iterator itr;
        for(itr = this->adj[u].begin();itr!=this->adj[u].end();itr++){
            int v = (*itr)[0];
            vertices[v].pi = u;
            DFS_back(v,vertices,min_edge);
        }
        vertices[u].color = 2;
    }
}





void Graph::printAdj(){
    for(int i=0;i<this->V;i++){
        cout<<i<<" ->";
        for(int j=0;j<this->adj[i].size();j++){
            cout<<" "<<this->adj[i][j][0]<<"("<<this->adj[i][j][1]<<")";
        }
        cout<<endl;
    }
}
