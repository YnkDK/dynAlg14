/* ---------------------------------------------------------------------------
** This software is implemented as part of the course Dynamic Algorithms 
** (Q4 2015) at Aarhus Univerity Denmark. 
**
** TD_EAGER.cpp
** Implementation of a truly dynamic algorithm for dynamic transitive closure
** based on Shankowsis randomized reduction of dynamic transitive closure to dynamic matrix adjoint.
**
** Author: Martin Storgaard and Konstantinos Mampentzidis
** -------------------------------------------------------------------------*/

#include "TD_EAGER.h"


using namespace std;

void TD_EAGER::init(int n) {
    //initialize the adjacency matrix where we will store all the edges that are part of the graph
    //we need it in case our randomized algorithm fails (division by zero) to be able to reconstruct
    //the
    if (adjacency_matrix != NULL) delete[] adjacency_matrix;
    if (inverse_matrix != NULL) delete[] inverse_matrix;
    if (xs != NULL) delete[] xs;

    this->n = (uint32_t) n;

    // Allocate and initialize the adjacency matrix
    adjacency_matrix = new uint32_t[n * n];
    memset(adjacency_matrix, 0, n * n * sizeof(uint32_t));

    // Allocate and initialize the adjacency matrix
    inverse_matrix = new uint32_t[n * n];
    memset(inverse_matrix, 0, n * n * sizeof(uint32_t));

    // Compute I-A and (I-A)^(-1), i.e. I
    for (int i = 0; i < n; i++) {
        inverse_matrix[i * n + i] = 1;
        adjacency_matrix[i * n + i] = 1;
    }
    //initialize the counter to be n since all vertices can reach it self
    count = (uint32_t) n;

    // Pre-compute random values
    xs = new uint32_t[n * n];
    for (int i = 0; i < n * n; i++) {
        xs[i] = next();
    }
}

inline void TD_EAGER::sherman_morrison(int i, int j, uint32_t u) {
    // Indicate that n does not change at this point.
    const uint32_t n = this->n;
    // Define loop invariants
    uint32_t k, m;

    // We do not need v, since it is only a multiplication by 1
    //uint32_t v = 1;

    //find (A^(-1)*u) => pick i-th column of A^(-1) and multiply every value by u
    uint32_t *a = new uint32_t[n];
    for (k = 0; k < n; k++) {
        a[k] = mod_mul(inverse_matrix[k * n + i], u);
    }
    // v^T * A^(-1), i.e. multiply row j by 1
    uint32_t *b = &inverse_matrix[j * n];

    // find the value of the denominator 1 + v^T*A^(-1)*u
    uint32_t c = mod_add(1, mod_mul(u, b[i]));

    // Check that we do not divide by 0
    if (c == 0) {
        // TODO: Use a better solutuon than simply exit!
        std::cout << "Division by zero!!!!!!!!" << std::endl;
        exit(1);
    }
    // Find the multiplicative inverse of c, and (maybe) multiply the nominator by this value
    c = mod_inv(c);
    // Reset the number of reachable nodes, we recount below
    count = 0;

    // Be smart, do not multiply by 1
    if (c != 1) {
        //find the nominator of sherman morisson formula and divide with the denominator at the same time.
        uint32_t *e = new uint32_t[n * n];
        for (k = 0; k < n; ++k) {
            // Point to the k'th row
            uint32_t *t1 = &e[k * n];
            for (m = 0; m < n; ++m) {
                t1[m] = mod_mul(c, mod_mul(a[k], b[m]));
            }
        }
        //update the inverse matrix and counter
        for (k = 0; k < n; ++k) {
            const uint32_t kn = k * n;
            // Point to the k'th row
            uint32_t *t1 = &inverse_matrix[kn];
            const uint32_t *t2 = &e[kn];
            for (m = 0; m < n; ++m) {
                t1[m] = mod_sub(t1[m], t2[m]);
                // Increment number of reachable nodes if k can reach m
                count += t1[m] != 0; // [conv.integral] ensures that this is 1 if true, 0 otherwise
            }
        }
        delete[] e;
    } else {
        // We do not need to multiply by 1
        // Calculate A^-1 - (fraction)
        for (k = 0; k < n; ++k) {
            // Point to the k'th row
            uint32_t *t1 = &inverse_matrix[k * n];
            for (m = 0; m < n; ++m) {
                t1[m] = mod_sub(t1[m], mod_mul(a[k], b[m]));
                // Increment number of reachable nodes if k can reach m
                count += t1[m] != 0;  // [conv.integral] ensures that this is 1 if true, 0 otherwise
            }
        }
    }

    delete[] a;
}


void TD_EAGER::ins(int i, int j) {
    const uint32_t u = xs[i * n + j];
    adjacency_matrix[i * n + j] = u;

    //update the inverse matrix
    sherman_morrison(i, j, u);

}

void TD_EAGER::del(int i, int j) {
    // This is the same as inserting -u = P - u in the Z_P field
    sherman_morrison(i, j, P - adjacency_matrix[i * n + j]);
    // P - u + u (mod P) = 0
    adjacency_matrix[i * n + j] = 0;
}

unsigned int TD_EAGER::query() {
    // Oh, we were eager, wasn't we?
    return count;
}
