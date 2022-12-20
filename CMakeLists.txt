cmake_minimum_required(VERSION 3.22)
project(code_generation)

set(CMAKE_CXX_STANDARD 14)

add_executable(code_generation main.cpp scanner.cpp scanner.h parser.h parser.cpp analyzer.cpp analyzer.h codeGeneration.cpp codeGeneration.h)
