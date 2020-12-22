#include <iostream>
#include <fstream>
#include <vector>
#include "cyclebreak.h"
using namespace std;

void help_message(){
    cout<<"usage: cb <input_file_name> <output_file_name>"<<endl;
}

int main(int argc,char* argv[]){
    if(argc!=3){
        help_message();
        return 0;
    }
    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2],ios::out);
    int V,E;
    char dir;
    int start,end,weight;
    int cost;
    fin>>dir;
    fin>>V;
    fin>>E;
    Graph g(V,E);
    while(fin>>start>>end>>weight){
        vector<int> temp(2);
        temp[0] = end;
        temp[1] = weight;
        g.adj[start].push_back(temp);
    }
    fin.close();
    // ----------------------------------------read file-------------------------------------
    vector<vector<int> > ans;
    if(dir=='u'){
        g.Kruskal_MST(ans,cost);
    }
    if(dir=='d'){
        g.cycleBreaking(ans,cost);
        // if(g.checkAns()) cout<<"cycle breaking completly !!!"<<endl;
        // else cout<<"There are something wrong..."<<endl;
        // g.printAdj();
    }
    fout<<cost<<endl;
    vector<vector<int> >::iterator itr;
    for(itr=ans.begin();itr!=ans.end();itr++){
        if(ans.size()==0) break;
        fout<<(*itr)[0]<<" "<<(*itr)[1]<<" "<<(*itr)[2]<<endl;    
    }
    // fout<<"0"<<endl;
    fout.close();
    
    return 0;
}