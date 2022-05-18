// **************************************************************************
//  File       [maxPlanarSubset.h]
//  Author     [Hugo Chen]
//  Synopsis   [The maxPlanarSubset.h program of 2020 fall Algorithm PA2]
// **************************************************************************

#ifndef _MAXPLANARSUBSET_H
#define _MAXPLANARSUBSET_H

#include <vector>
using namespace std;

class MPS{
    public:
                                     MPS() {}; // constructor
        int**                        MaximumPlanarSubset(int* C, int N); // based on recursive pseudo code
        void                         which_chord(int i, int j, int** M, int* chord_array, vector<int>& optimal_chord);
};

#endif