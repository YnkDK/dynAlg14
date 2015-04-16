main: *.cpp *.h
	g++ -O3 -Wall -lrt -std=c++0x input_reader.cpp floyd_warshall.cpp FW_EAGER.cpp FW_LAZY.cpp main.cpp -o bin/main
