#include <string.h> //< memset, memcpy

unsigned int transitive_closure(bool *adjacency_matrix, const unsigned int n) {
	const unsigned int SIZE = n*n; //< Size of matrix
	bool even[SIZE]; //< Temp array stating if there is a path from (i,j) 
	bool  odd[SIZE]; //< Temp array stating if there is a path from (i,j)
	unsigned int i, j, k; //< Indices for the loop
	unsigned int entry, col; //< Position in matrix
	unsigned int count = 0; //< Number of transitive closures
	bool *current, *previous; //< Keeps T(k) and T(k-1) respectively
	bool gotIntermediate; //< Indicate if node_k was used as intermediate node
	
	// All are not connected at first
	memset(even, false, SIZE*sizeof(bool));
	memset( odd, false, SIZE*sizeof(bool));
	
	// Get all closures without any intermediate nodes
	for(i = 0; i < n; i++) {
		for(j = 0; j < n; j++) {
			entry = i*n + j;
			if(adjacency_matrix[entry] || i == j) {
				if(!odd[entry]) count++;
				odd[entry] = true;
			}
			
		}
	}
	
	for(k = 0; k < n; k++) {
		// Swap current and previous
		current  = (k % 2 == 0) ? even : odd;
		previous = (k % 2 == 0) ? odd : even;

		for(i = 0; i < n; i++) {
			col = i*n; //<- Current column
			if(i != k) {
				for(j = 0; j < n; j++) {
					// Check if there is a path using node_k as intermediate,
					// i.e. node_i -> ... -> node_k -> node_j
					entry = col + j;
					gotIntermediate = previous[col + k] & previous[k*n + j];
					// If a _new_ closure was intermediate found using k as
					// intermediate, then increment the counter
					if(!previous[entry] && gotIntermediate) count++;
					// Update the current value
					current[entry] = previous[entry] | gotIntermediate;
				}
			} else {
				// Nothing can change using the the k'th node as intermediate,
				// e.g. node_1 -> node_1 -> node_5 is the same as node_1 -> node_1
				memcpy(&current[col], &previous[col], n*sizeof(bool));
			}
		}
	}
	// The total number of pairs that is part of the transitive closure
	return count;
}
