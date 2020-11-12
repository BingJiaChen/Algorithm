#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include "maxPlanarSubset.h"


using namespace std;

void help_message(){
    cout<<"usage: msg <input_file> <output_file>"<<endl;
}


int main(int argc,char* argv[]){
    if(argc!=3){
        help_message();
        return 0;
    }
    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2],ios::out);
    int buffer;
    int start, end;
    fin>>buffer;
    vector<int> data(buffer,0);
    vector<vector<int>> output;
    while(fin>>start>>end){
        data[start]=end;
        data[end]=start;
    }
    // cout<<data.size()<<endl;
    MPS(data,output);
    vector<vector<int>> result(output.size()+1,{0,0});
    countingSort(output,result,data.size());
    vector<vector<int>>::iterator itr;
    fout<<output.size()<<endl;
    for (itr=result.begin()+1;itr!=result.end();itr++){
        fout<<(*itr)[0]<<" "<<(*itr)[1]<<endl;
    }
    fin.close();
    fout.close();
    cout<<"MIS complete!!"<<endl;
    return 0;
}