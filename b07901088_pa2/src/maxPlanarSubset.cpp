#include <iostream>
#include <vector>
#include "maxPlanarSubset.h"
using namespace std;

void getChord(int i,int j,vector<int>& data,vector<vector<int> >& output,vector<vector<int> >& record){
    vector<int> temp(2);
    if(i==j){return;}
    if(record[i][j]==0){
        getChord(i,j-1,data,output,record);
    }
    else if(record[i][j]==1){
        int k = data[j];
        if(j<k){
            temp[0] = j;
            temp[1] = k;
            output.push_back(temp);}
        else{
            temp[0] = k;
            temp[1] = j;
            output.push_back(temp);}
        getChord(i+1,j-1,data,output,record);
    }
    else if(record[i][j]==2){
        int k = data[j];
        if(j<k){
            temp[0] = j;
            temp[1] = k;
            output.push_back(temp);}
        else{
            temp[0] = k;
            temp[1] = j;
            output.push_back(temp);}
        getChord(i,k-1,data,output,record);
        getChord(k+1,j-1,data,output,record);
    }   
}

void countingSort(vector<vector<int> >& data,vector<vector<int> >& output,int N){
    int B[N] = {0};
    vector<vector<int> >::iterator itr;
    for (itr=data.begin();itr!=data.end();itr++){
        B[(*itr)[0]] = 1;
    }
    for(int i=1;i<N;i++){
        B[i] = B[i] + B[i-1];
    }
    for (itr=data.begin();itr!=data.end();itr++){
        output[B[(*itr)[0]]] = *itr;
        B[(*itr)[0]] -= 1;
    }
}

int MPS_DP(int i, int j, vector<int>& data, vector<vector<int> >& M,vector<vector<int> >& record){
    int k = data[j];
    if(i>=j){return 0;}
    if(M[i][j]!=0){return M[i][j];}
    if(k<i || k>j){
        M[i][j] = MPS_DP(i,j-1,data,M,record);
    }
    else if(k==i){
        record[i][j] = 1;
        M[i][j] = MPS_DP(i+1,j-1,data,M,record)+1;
    }
    else{
        M[i][j-1] = MPS_DP(i,j-1,data,M,record);
        M[i][k-1] = MPS_DP(i,k-1,data,M,record);
        M[k+1][j-1] = MPS_DP(k+1,j-1,data,M,record);
        if(M[i][j-1]>=(M[i][k-1]+1+M[k+1][j-1])){
            M[i][j] = M[i][j-1];
        }
        else{
            record[i][j] = 2;
            M[i][j] = M[i][k-1]+1+M[k+1][j-1];
            }
    }
    return M[i][j];
}


void MPS(vector<int>& data,vector<vector<int> >& output){
    int N = data.size();
    vector<vector<int> > M;
    vector<vector<int> > record;
    M.reserve(N);
    record.reserve(N);
    for(int i=0;i<N;i++){
        M[i].reserve(N);
        record[i].reserve(N);
    }
    MPS_DP(0,N-1,data,M,record);
    cout<<M[0][N-1]<<endl;
    getChord(0,N-1,data,output,record);
}

