// **************************************************************************
//  File       [maxPlanarSubset.cpp]
//  Author     [Hugo Chen]
//  Synopsis   [The maxPlanarSubset.cpp program of 2020 fall Algorithm PA2]
// **************************************************************************

#include "maxPlanarSubset.h"
#include <iostream>

// ****************************  Function   *********************************

// Main Recursion
// ******************************************** M with array *****************************************
int**
MPS::MaximumPlanarSubset(int* chord_array, int node_num){
    // Create a vector "M"
    // vector< vector<int> > v(rows, vector<int> (cols, val)); val: default number
    int** M = new int*[node_num];
    for (int i=0 ; i < node_num ; i++){
        M[i] = new int[node_num];
        M[i][i] = 0;
    }
    for (int l=1 ; l <= (node_num-1) ; l++){
        for (int i=0 ; i <= (node_num-l-1) ; i++){
            int j = i+l;
            int k = chord_array[j];
            // if chord kj ∈ C and k /∈ [i, j]
            if ((k < i) || (k > j)) { M[i][j] = M[i][j-1]; }
            // if k == i
            else if (k == i) { 
                M[i][j] = M[i+1][j-1]+1; 
                M[j][i] = 3;
            }
            // if k ∈ (i, j)
            else if ((k > i) && (k < j)) {
                if (M[i][j-1] < (M[i][k-1]+1+M[k+1][j-1])) { 
                    M[i][j] = M[i][k-1]+1+M[k+1][j-1]; 
                    M[j][i] = 2;
                }
                else {
                    M[i][j] = M[i][j-1];
                }
            }
        }
    }
    return M;
}

// Find chord
void 
MPS::which_chord(int i, int j, int** M, int* chord_array, vector<int>& optimal_chord){
    if (j-i >= 1){
        int k = chord_array[j];
        // if k ∈ (i, j)
        if (M[j][i] == 2){
            optimal_chord.push_back(k);
            which_chord(k+1, j-1, M, chord_array, optimal_chord);
            which_chord(i, k-1, M, chord_array, optimal_chord);
        }
        // if k == i
        else if (M[j][i] == 3){
            optimal_chord.push_back(i);
            which_chord(i+1, j-1, M, chord_array, optimal_chord);
            return;
        }
        // if chord kj ∈ C and k /∈ [i, j]
        else {
            which_chord(i, j-1, M, chord_array, optimal_chord);
        }
    }
}