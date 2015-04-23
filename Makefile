BIN = bin
TC = floyd_warshall.cpp FW_EAGER.cpp FW_LAZY.cpp DFS_LAZY.cpp
UTILS = input_reader.cpp
FLAGS = -O3 -Wall -lrt -std=c++0x

main: *.cpp *.h
	mkdir -p $(BIN)
	g++ $(FLAGS) $(UTILS) $(TC) main.cpp -o $(BIN)/main
