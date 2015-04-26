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

# Run experiments
Compile the code by running `make`. Since the Performance class uses `linux/perf_event.h` the code will only compile on Linux kernels version 2.6.31 or higher. The `Makefile` ensures that needed folders are present.

Execute the main binary file to run the experiments, e.g. `./bin/main ./input/changefile3.txt`, which outputs the following files:

1. changefile3-del.stat - Timings of calls for `del(int i, int j)` on all algorithms
2. changefile3-ins.stat - Timings of calls for `ins(int i, int j)` on all algoruthms
3. changefile3-query.stat - Timings of calls for `query()` on all algorihms
4. changefile(name).out - Output of `query()`, where (name) is replaced by `get_name()`

# Test for correctness
Executing the Python script `./cmp_changefile.py` prints the following if everything is correct:

```

All output files have been compared!
```
while an error might yield

```

=========== ERROR IN changefile3 ===========
Eager DFS and Lazy DFS mismatches
 Lazy Floyd-Warshall and Lazy DFS mismatches
Lazy DFS and Eager Floyd-Warshall mismatches
============================================ 

All output files have been compared!
```
indicating that Lazy DFS is incorrect on changefile3 compared to Eager DFS and Lazy Floyd-Warshall
