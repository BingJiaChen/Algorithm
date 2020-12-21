#include <iostream>
#include <vector>
using namespace std;

class Tree{
    public:
        int p;
        int rank;
};

void MakeSet(Tree forest[], int V);
int FindSet(Tree forest[], int X);
void Union(Tree forest[], int X, int Y);

class Vertex{
    public:
        Vertex(){color=0;pi=0;};
        int color;
        int pi;
};

class Graph{
    public:
        Graph();
        Graph(int V,int E);
        ~Graph(){}
        vector<vector<vector<int> > > adj;
        void Kruskal_MST(vector<vector<int> >&,int&);
        void printAdj();
        void removeEdge(int,int,int);
        bool cycleDetect();
        bool cycleDetect_DFS(int,Vertex vertices[]);
        int findWeight(int u , int v);
        void reset(Vertex[]);
        void cycleBreaking(vector<vector<int> >&,int&);
        void addEdge(int,int,int);
        bool checkAns();
        void countingSort(vector<vector<int> >&, int);

    private:
        int V;
        int E;

};



