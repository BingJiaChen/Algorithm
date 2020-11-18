#ifndef MAXPLANARSUBSET_H
#define MAXPLANARSUBSET_H
#include<vector>
using namespace std;
void MPS(vector<int>&,vector<vector<int>>&);
void getChord(int, int, vector<int>&, vector<vector<int> >&,vector<vector<int> >&);
void countingSort(vector<vector<int> >&,vector<vector<int> >&,int);
int MPS_DP(int,int,vector<int>&, vector<vector<int>>&, vector<vector<int>>&);
#endif