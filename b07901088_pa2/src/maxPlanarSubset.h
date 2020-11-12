#ifndef MAXPLANARSUBSET_H
#define MAXPLANARSUBSET_H
#include<vector>
using namespace std;
void MPS(vector<int>&,vector<vector<int>>&);
int find_k(vector<vector<int>>&,int);
void getChord(int, int, vector<int>&, vector<vector<int>>&,int**);
void countingSort(vector<vector<int>>&,vector<vector<int>>&,int);
#endif