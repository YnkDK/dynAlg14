cmake_minimum_required(VERSION 3.2)
project(dynAlg14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    DFS_EAGER.cpp
    DFS_EAGER.h
    DFS_LAZY.cpp
    DFS_LAZY.h
    TD_EAGER.cpp
    TD_EAGER.h
    floyd_warshall.cpp
    floyd_warshall.h
    FW_EAGER.cpp
    FW_EAGER.h
    FW_LAZY.cpp
    FW_LAZY.h
    input_reader.cpp
    input_reader.h
    main.cpp
    performance.cpp
    performance.h
    TC.h
    utils.h)

add_executable(dynAlg14 ${SOURCE_FILES})