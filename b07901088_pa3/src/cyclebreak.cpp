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
    if(itr!=this->adj[u].end())
    this->adj[u].erase(itr);
    else cout<<"none"<<endl;
}

void Graph::addEdge(int u,int v,int w){
    vector<int> temp(2);
    temp[0] = v;
    temp[1] = w;
    this->adj[u].push_back(temp);
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
    for(int i=0;i<this->V;i++){
        this->adj[i].clear();
    }
    vector<int> adj_temp(2);
    for(int i=0;i<MST.size();i++){
        cost -= edges[MST[i]-i][2];
        adj_temp[0] = edges[MST[i]-i][1];
        adj_temp[1] = edges[MST[i]-i][2];
        this->adj[edges[MST[i]-i][0]].push_back(adj_temp);
        edges.erase(edges.begin()+MST[i]-i);
    }
    sort(edges.begin(),edges.end(),compare1);
    vector<vector<int> >::iterator itr;
    for(itr=edges.begin();itr!=edges.end();itr++){
        if((*itr)[2]>0){
            addEdge((*itr)[0],(*itr)[1],(*itr)[2]);
            cost -= (*itr)[2];
            if(cycleDetect()){
                cost += (*itr)[2];
                temp[0] = (*itr)[0];
                temp[1] = (*itr)[1];
                temp[2] = (*itr)[2];
                ans.push_back(temp);
                removeEdge((*itr)[0],(*itr)[1],(*itr)[2]);
            }
        }
        else{
            temp[0] = (*itr)[0];
            temp[1] = (*itr)[1];
            temp[2] = (*itr)[2];
            ans.push_back(temp);
        }
    }
    this->E -= ans.size();
    sort(ans.begin(),ans.end(),compare2);
}


bool Graph::cycleDetect(){
    Vertex *vertices = new Vertex[this->V];
    for(int i=0;i<this->V;i++){
        if(vertices[i].color==0){
            if(cycleDetect_DFS(i,vertices)==true)
            return true;    
        }
    }
    for(int i=0;i<this->V;i++){
        if(vertices[i].color==3) return true;
    }
    return false;
}

bool Graph::cycleDetect_DFS(int u, Vertex vertices[]){
    vertices[u].color = 1;
    vector<vector<int> >::iterator itr;
    for(itr=this->adj[u].begin();itr!=this->adj[u].end();itr++){
        if(this->adj[u].size()==0){
            vertices[u].color=3;
            break;
        } 
        int v = (*itr)[0];
        if(vertices[v].color==1)return true;
        if(vertices[v].color==0 && cycleDetect_DFS(v,vertices))return true;
    }
    vertices[u].color = 2;
    return false;
}

bool Graph::checkAns(){
    if(cycleDetect()) return false;
    Tree *forest = new Tree[this->V];
    MakeSet(forest,this->V);
    vector<vector<int> > edges(this->E);
    vector<int> temp(3);
    for(int i=0;i<this->E;i++){
        edges[i].reserve(3);
    }
    int count = 0;
    for(int i=0;i<this->V;i++){
        for(int j=0;j<this->adj[i].size();j++){
            if(this->adj[i].size()==0) break;
            edges[count][0] = i;
            edges[count][1] = this->adj[i][j][0];
            edges[count][2] = this->adj[i][j][1];
            count+=1;
        }
    }
    sort(edges.begin(),edges.end(),compare1);
    for(int i=0;i<edges.size();i++){
        int u = edges[i][0];
        int v = edges[i][1];

        if(FindSet(forest,u)!=FindSet(forest,v)){
            Union(forest,u,v);
        }
    }
    int test = FindSet(forest,0);
    for(int i=0;i<this->V;i++){
        if(FindSet(forest,i)!=test) return false;
    }
    return true;
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
