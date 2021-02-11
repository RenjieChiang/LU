#include <iostream>
#include "Gauss_solver.h"

int main() {
//    std::cout << "Hello, World!" << std::endl;

//    double my_Avalue[4] = {1,1,4,5};
//    double my_Bvalue[2] = {3, 13};
////
    double my_Avalue[100] =
            {5,0,0,1,1,0,0,1,0,1,
             0,6,1,0,0,1,0,1,1,1,
             2,0,7,0,0,0,0,0,0,4,
             0,0,0,8,4,0,0,0,0,2,
             7,0,0,0,9,0,0,0,0,1,
             0,0,0,0,5,10,0,0,0,4,
             0,1,1,1,0,0,11,0,0,7,
             1,0,2,0,0,0,0,12,0,5,
             1,0,0,2,0,0,7,0,13,0,
             10,0,0,0,0,0,0,0,0,14
    };//10 x 10 matrix

    double my_Bvalue[10] = {32,48,63,72,62, 120,156,153,175,150};//b in Ax=b

    Gauss_solver<double> my_solver(10);

    my_solver.setGauss_solver(my_Avalue, my_Bvalue);
//    for (int i = 0; i < 4; ++i) {
//        std::cout << my_solver.values[i] << std::endl;
//    }
    my_solver.printEqu();
    if (my_solver.solve())
    {
        std::cout << "using Gauss Seidel method successful!"<< std::endl;
        my_solver.printSolution();
    }
    if (my_solver.LU_solve())
    {
        std::cout << "yes! using LU method successful!" << std::endl;
        my_solver.printSolution();
    }
//    for (int i = 0; i < 4; ++i) {
//        std::cout << my_solver.values[i] << std::endl;
//    }
//    my_solver.printEqu();



//    Matrix<double> matrix1(2, 2, my_value);
//    SquareMatrix<double> my_square(2, my_value);
//    matrix1.printValues();
//    my_square.printValues();
//    std::cout<<std::endl<<my_square.element(1,1);
    return 0;
}
