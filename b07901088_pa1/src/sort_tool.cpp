// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2020/9/15 Mu-Ting Wu]
// **************************************************************************

#include "sort_tool.h"
#include<iostream>

// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here
    for(int i=1;i<data.size();i++){
        int j = i-1;
        int key = data[i];
        while(j>=0 && key<data[j]){
            data[j+1] = data[j];
            j--;
        }
        data[j+1] = key;    
    }
}

// Quick sort method
void SortTool::QuickSort(vector<int>& data){
    QuickSortSubVector(data, 0, data.size() - 1);
}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int>& data, int low, int high) {
    // Function : Quick sort subvector
    // TODO : Please complete QuickSortSubVector code here
    // Hint : recursively call itself
    //        Partition function is needed
    if(low<high){
        int q = Partition(data,low,high);
        QuickSortSubVector(data,low,q);
        QuickSortSubVector(data,q+1,high);
    }
}

int SortTool::Partition(vector<int>& data, int low, int high) {
    // Function : Partition the vector 
    // TODO : Please complete the function
    // Hint : Textbook page 171
    int x = data[low];
    int i = low;
    int j = high;
    while(true){
        while(data[j]>x && j>low){
            j--;
        }
        while(data[i]<x && i<high){
            i++;
        }
        if(i<j){
            int temp = data[i];
            data[i] = data[j];
            data[j] = temp;
            i++;
            j--;
        }
        else{
            // cout<<j<<endl;
            return j;
        }
    }

}

// Merge sort method
void SortTool::MergeSort(vector<int>& data){
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int>& data, int low, int high) {
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    // Hint : recursively call itself
    //        Merge function is needed
    if(low<high){
        int mid = (low+high)/2;
        MergeSortSubVector(data,low,mid);
        MergeSortSubVector(data,mid+1,high);
        Merge(data,low,mid,mid+1,high);
    }
}

// Merge
void SortTool::Merge(vector<int>& data, int low, int middle1, int middle2, int high) {
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    vector<int> L;
    vector<int> R;
    for(int i=low;i<=middle1;i++){
        L.push_back(data[i]);
    }
    for(int j=middle2;j<=high;j++){
        R.push_back(data[j]);
    }
    int l=0;
    int r=0;
    int k=low;
    while(true){
        if(L[l]<R[r]){
            data[k] = L[l];
            l++;
            k++;
        }
        else{
            data[k] = R[r];
            r++;
            k++;
        }
        if(l==L.size()){
            for(r;r<R.size();r++){
                data[k] = R[r];
                k++;
            }
            break;
        }
        if(r==R.size()){
            for(l;l<L.size();l++){
                data[k] = L[l];
                k++; 
            }
            break;
        }
    }
}

// Heap sort method
void SortTool::HeapSort(vector<int>& data) {
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 1; i--) {
        swap(data[0],data[i]);
        heapSize--;
        MaxHeapify(data,0);
    }
}

//Max heapify
void SortTool::MaxHeapify(vector<int>& data, int root) {
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    // TODO : Please complete max-heapify code here
    int l = 2*root+1;
    int r = 2*root+2;
    int largest = root;
    if(l<=heapSize-1 && data[l]>data[root]){
        largest = l;
    }
    
    if(r<=heapSize-1 && data[r]>data[largest]){
        largest = r;
    }
    if (largest!=root){
        int temp = data[root];
        data[root] = data[largest];
        data[largest] = temp;
        MaxHeapify(data,largest);
    }
}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
    // TODO : Please complete BuildMaxHeap code here
    for(int i=(data.size()-1)/2;i>=0;i--){
        MaxHeapify(data,i);
    }
}
