# Dynamic Algorithms, Spring 2015: Project
This project has both theoretical and practical aspects. In this repository only the pratical aspects are shown.

> In this project you must both implement a trivial solution based on recomputing
> the transitive closure from scratch upon each change using the Floyd-Warshall
> algorithm, and you must implement a truly dynamic algorithm
> that uses Sankowskis randomized reduction of dynamic transitive closure to
> dynamic matrix adjoint combined with the Sherman-Morrison formula for
> maintaining matrix inverse (and determinant) under rank one updates. Finally
> you should make experimental comparisons of the two implementations
> and comment on the results.

All solutions implements the class TC (Transitive Closure) with the following functions:

1. `init(int n)`
2. `ins(int i, int j)`
3. `del(int i, int j)`
4. `query()`
5. `get_name()`

# Compile the code
TODO
