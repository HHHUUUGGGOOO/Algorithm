// **************************************************************************
//  File       [main.cpp]
//  Author     [Hugo Chen]
//  Synopsis   [The main program of 2020 fall Algorithm PA2]
// **************************************************************************

#include "maxPlanarSubset.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>
#include <bits/stdc++.h> // sort


using namespace std;

void help_message() {
    cout << "QAQQQQQQ" << endl;
}

int main(int argc, char* argv[])
{
    if(argc != 3) {
       help_message();
       return 0;
    }
    //////////// read the input file /////////////
    char buffer[100];
    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2],ios::out);
    fin.getline(buffer,15);
    // size (int --> string)
    stringstream length(buffer);
    int node_num = 0;
    length >> node_num;
    // chord
    int j_node, k_node;
    int* chord_array = new int[node_num];
    while (fin >> j_node >> k_node){
        chord_array[j_node] = k_node;
        chord_array[k_node] = j_node;
    }     
    //////////// max planar subset /////////////// 
    MPS NTUMPS;
    int** M = NTUMPS.MaximumPlanarSubset(chord_array, node_num);
    int max_chord_num = M[0][node_num-1];
    
    vector<int> opt;
    NTUMPS.which_chord(0, node_num-1, M, chord_array, opt);
    sort(opt.begin(), opt.end());
    
    //////////// write the output file ///////////
    fout << max_chord_num << endl;
    for (int i = 0; i < max_chord_num; i++)
        fout << opt[i] << " " << chord_array[opt[i]] << endl;
    fin.close();
    fout.close();

    return 0;
}