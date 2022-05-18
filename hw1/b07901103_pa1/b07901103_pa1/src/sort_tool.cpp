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
    for (int i = 2; i <= data.size() ; i++){
        int key = data[i];
        int j = i-1;
        while(j > 0 && key < data[j]){
            data[j+1] = data[j];
            j -= 1;
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
    if (low < high){
        int pivot = Partition(data, low, high);
        QuickSortSubVector(data, low, pivot-1);
        QuickSortSubVector(data, pivot+1, high);
    }
}

int SortTool::Partition(vector<int>& data, int low, int high) {
    // Function : Partition the vector 
    // TODO : Please complete the function
    // Hint : Textbook page 171
    int pivot = data[high];
    int i = low-1;
    for(int j = low ; j <= high-1 ; j++){
        if (data[j] <= pivot){
            i += 1;
            int temp = data[i];
            data[i] = data[j];
            data[j] = temp;
        }
    }
    int temp = data[i+1];
    data[i+1] = data[high];
    data[high] = temp;
    return i+1;
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
    if (low < high){
        int mid = low + (high-low)/2;
        MergeSortSubVector(data, low, mid);
        MergeSortSubVector(data, mid+1, high);
        Merge(data, low, mid, mid+1, high);
    }
}

// Merge
void SortTool::Merge(vector<int>& data, int low, int middle1, int middle2, int high) {
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    int n1 = middle1-low+1;
    int n2 = high-middle1;
    int L[n1], R[n2];
    int i, j, k;
    for(i = 0 ; i < n1 ; i++){
        L[i] = data[low+i];
    }
    for(j = 0 ; j < n2 ; j++){
        R[j] = data[middle1+j+1];
    }
    i = 0;
    j = 0;
    k = low;
    while(i < n1 && j < n2){
        if(L[i] <= R[j]){
            data[k] = L[i];
            i++;
        }
        else{
            data[k] = R[j];
            j++;
        }
        k++;
    }
    while(i < n1){
        data[k] = L[i];
        i++;
        k++;
    }
    while(j < n2){
        data[k] = R[j];
        j++;
        k++;
    }
}

// Heap sort method
void SortTool::HeapSort(vector<int>& data) {
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = (int)heapSize-1 ; i >= 1; i--) {
        int temp = data[0];
        data[0] = data[i];
        data[i] = temp;
        heapSize--;
        MaxHeapify(data,0);
    }
}

//Max heapify
void SortTool::MaxHeapify(vector<int>& data, int root) {
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    // TODO : Please complete max-heapify code here
    int left = 2*root+1;
    int right = 2*root+2;
    int largest;
    if (left <= heapSize && data[left] > data[root]){
        largest = left;
    }
    else{
        largest = root;
    }
    if (right <= heapSize && data[right] > data[largest]){
        largest = right;
    }
    if (largest != root){
        int temp = data[root];
        data[root] = data[largest];
        data[largest] = temp;
        MaxHeapify(data, largest);
    }
}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
    // TODO : Please complete BuildMaxHeap code here
    for(int i = (int)heapSize/2 ; i >= 0 ; i--){
        MaxHeapify(data, i);
    }
}
