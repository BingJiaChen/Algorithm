#include <iostream>
#include <vector>
#include "maxPlanarSubset.h"
using namespace std;

int find_k(vector<vector<int>>& data,int j){
    int k = 0;
    vector<vector<int>>::iterator itr;
    for (itr=data.begin();itr!=data.end();itr++){
        if((*itr)[0]==j){
            k = (*itr)[1];
            break;
        }       
        if((*itr)[1]==j){
            k = (*itr)[0];
            break;
        }
    }
    return k;
}

void getChord(int i,int j,vector<int>& data,vector<vector<int>>& output,vector<vector<int>>& record){
    int N = data.size();
    while(j-i>1){
        if(record[i][j]==1){
            int k = data[j];
            if(j<k){output.push_back({j,k});}
            else{output.push_back({k,j});}
            getChord(i+1,j-1,data,output,record);
            j = i-1;
        }
        else if(record[i][j]==2){
            int k = data[j];
            if(j<k){output.push_back({j,k});}
            else{output.push_back({k,j});}
            getChord(k,j-1,data,output,record);
            j = k-1;
        }
        else{j--;}
    }
}

void countingSort(vector<vector<int>>& data,vector<vector<int>>& output,int N){
    int B[N] = {0};
    vector<vector<int>>::iterator itr;
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


void MPS(vector<int>& data,vector<vector<int>>& output){
    int N = data.size();
    vector<vector<int>> M;
    vector<vector<int>> record;
    M.reserve(N);
    record.reserve(N);
    M.resize(N);
    record.resize(N);
    for(int i=0;i<N;i++){
        M[i].resize(N);
        record[i].resize(N);
    }
    int k = 0;
    for(int l=1;l<N;l++){
        for(int i=0;i<N-l;i++){
            int j=i+l;
            k = data[j];           
            if(k<i || k>j){
                M[i][j] = M[i][j-1];
            } 
            else if(k==i){
                M[i][j] = M[i+1][j-1] + 1;
                record[i][j] = 1;
            }
            else{
                if(M[i][j-1]>=(M[i][k-1]+1+M[k+1][j-1])){
                    M[i][j] = M[i][j-1];
                }
                else{
                    M[i][j]=M[i][k-1]+1+M[k+1][j-1];
                    record[i][j] = 2;
                    }
            }
        }
    }
    cout<<M[0][N-1]<<endl;
    getChord(0,N-1,data,output,record);
}

