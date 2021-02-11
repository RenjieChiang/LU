cmake_minimum_required(VERSION 3.17)
project(Linear_system)

set(CMAKE_CXX_STANDARD 14)

add_executable(Linear_system main.cpp Matrix.h  Gauss_solver.h  SquareMatrix.h MatrixCaculate.cpp MatrixCaculate.h )
#add_executable(Linear_system main.cpp Matrix.h Matrix.cpp Gauss_solver.cpp Gauss_solver.h SquareMatrix.cpp SquareMatrix.h)