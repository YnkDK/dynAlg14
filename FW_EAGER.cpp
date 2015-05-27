/* ---------------------------------------------------------------------------
** This software is implemented as part of the course Dynamic Algorithms 
** (Q4 2015) at Aarhus Univerity Denmark. 
**
** FW_EAGER.cpp
** Implementation of a trivial eager dynamic algorithm for dynamic transitive
** closure based on the Floyd-Warshall algorithm.
**
** Author: Martin Storgaard and Konstantinos Mampentzidis
** -------------------------------------------------------------------------*/

#include "FW_EAGER.h"
#include <iostream>

using namespace std;

void FW_EAGER::init(int n) {
    if (adjacency_matrix != NULL) delete[] adjacency_matrix;
    if (current != NULL) delete[] current;
    cols = (unsigned int) n;
    //count = n;
    adjacency_matrix = new bool[n * n];
    current = new bool[n * n];
    memset(adjacency_matrix, false, n * n * sizeof(bool));
    memset(current, false, n * n * sizeof(bool));
    for (size_t k = 0; k < cols; k++) current[k * cols + k] = true;
}

void FW_EAGER::ins(int i, int j) {
    adjacency_matrix[i * cols + j] = true;
    //count = transitive_closure(adjacency_matrix, cols);
    //or the i-th row with the j-th
    bool *tmp1, *tmp2;
    tmp1 = &current[i * cols];
    tmp2 = &current[j * cols];
    tmp1[j] = true;
    size_t k, m;
    for (k = 0; k < cols; ++k)
        tmp1[k] |= tmp2[k];

    //or everything that reaches i with the row of j
    tmp2 = &current[i * cols];
    for (k = 0; k < cols; ++k) {
        tmp1 = &current[k * cols];
        if (tmp1[i])
            for (m = 0; m < cols; ++m)
                tmp1[m] |= tmp2[m];
    }
    count = 0;
    const size_t SIZE = cols * cols;
    for (k = 0; k < SIZE; k++) {
        count += current[k];
    }
}

void FW_EAGER::del(int i, int j) {
    adjacency_matrix[i * cols + j] = false;
    size_t m, l, k;
    const unsigned int SIZE = cols * cols; //< Size of matrix
    const unsigned int n = cols;
    bool *tmp1, *tmp2;
    /*
    memset( current, false, SIZE*sizeof(bool));
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            current[i*n+j] = adjacency_matrix[i*n+j];
    */
    std::copy(adjacency_matrix, adjacency_matrix + SIZE, current);


    for (k = 0; k < n; ++k) {
        tmp1 = &current[k * n];
        tmp1[k] = true;
        for (m = 0; m < n; ++m) {
            tmp2 = &current[m * n];
            for (l = 0; l < n; ++l) {
                tmp2[l] = (tmp2[l] | (tmp2[k] & tmp1[l]));
            }
        }
    }

    count = 0;
    for (m = 0; m < SIZE; ++m) {
        count += current[m];
    }
}

void FW_EAGER::jump(bool *state) {
    size_t k, m, l;
    bool *tmp1, *tmp2;
    const uint32_t n = cols;
    const uint32_t SIZE = n * n;

    std::copy(state, state + SIZE, adjacency_matrix);
    std::copy(state, state + SIZE, current);

    for (k = 0; k < n; ++k) {
        tmp1 = &current[k * n];
        tmp1[k] = true;
        for (m = 0; m < n; ++m) {
            tmp2 = &current[m * n];
            for (l = 0; l < n; ++l) {
                tmp2[l] = (tmp2[l] | (tmp2[k] & tmp1[l]));
            }
        }
    }

    count = 0;
    for (m = 0; m < SIZE; ++m) {
        count += current[m];
    }
}

unsigned int FW_EAGER::query() {
    return count;
}
