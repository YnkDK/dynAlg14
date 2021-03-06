/* ---------------------------------------------------------------------------
** This software is implemented as part of the course Dynamic Algorithms 
** (Q4 2015) at Aarhus Univerity Denmark. 
**
** main.cpp
** Runs tests (correctness and execution time) for all implementations.
**
** Author: Martin Storgaard and Konstantinos Mampentzidis
** -------------------------------------------------------------------------*/

#include <iostream>

#include "TC.h"
#include "FW_EAGER.h"
#include "DFS_LAZY.h"
#include "DFS_EAGER.h"
#include "TD_EAGER.h"

#include "input_reader.h"
#include "performance.h"

const std::string inputPath("input/");


int main(int argc, const char *argv[]) {
    if (argc != 2) {
        return -1;
    }
    Performance *perf = new Performance();
    // Read input file (at most 255 characters)
    std::string inputFile(argv[1], 255);

    // First define which algorithms to run
    std::vector<TC *> algorithms = {
            //new FW_LAZY(),
            new FW_EAGER(),
            //new DFS_LAZY(),
            new DFS_EAGER(),
            new TD_EAGER()
    };
    // Then define input
    std::vector<Input> change_sequence;
    read_input(inputFile.c_str(), change_sequence);
    if (change_sequence.size() == 0) {
        std::cout << "ERROR" << std::endl;
        return -1;
    }
    // Format the output prefix
    unsigned long idx = inputFile.find("change");
    unsigned long idxEnd = inputFile.find(".txt");
    std::string output_prefix = inputFile.substr(idx, idxEnd - idx);
    perf->run(algorithms, change_sequence, output_prefix);


    return 0;
}
