BIN = bin
TC = floyd_warshall.cpp FW_EAGER.cpp FW_LAZY.cpp DFS_LAZY.cpp DFS_EAGER.cpp
UTILS = input_reader.cpp performance.cpp
FLAGS = -O3 -Wall -lrt -std=c++0x

main: *.cpp *.h
	mkdir -p $(BIN)
	mkdir -p output
	g++ $(FLAGS) $(UTILS) $(TC) main.cpp -o $(BIN)/main
