/*
 * TODO: Implemenet O(|V|^2) version of inserts for Floyd Warshall.
 */


#include <string.h> //< memset, memcpy
#include <iostream>

using namespace std;

unsigned int transitive_closure(bool *adjacency_matrix, const unsigned int n, bool *current) {
    size_t m, l, k;
    const unsigned int SIZE = n * n; //< Size of matrix
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

    unsigned int count = 0;
    for (m = 0; m < SIZE; ++m) {
        count += current[m];
    }

    return count;
}
