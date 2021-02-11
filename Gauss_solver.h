#ifndef LINEAR_SYSTEM_GAUSS_SOLVER_H
#define LINEAR_SYSTEM_GAUSS_SOLVER_H

#define MAX_ITERATION 50
#define ERROR_VALUE 1e-6
#include "SquareMatrix.h"
#include "iostream"
#include "cmath"

template<class T>
class Gauss_solver: public SquareMatrix<T>
{
public:
    explicit Gauss_solver(int size_ = 2);
    ~Gauss_solver();
    void setGauss_solver(const T * a /* matrix A */, const T * b /* b in Ax=b */);
    bool solve();//default solver using Gauss-Seidel iteration TODO
    bool LU_solve();//Using L-U decomposition
    void printEqu() ;
    void printSolution() const;

private:
    T *sums;//  b in Ax = b
    T *solution;// x in Ax = b
};


template<class T>
Gauss_solver<T>::Gauss_solver(int size_):SquareMatrix<T>(size_)
{
    sums = new T [size_ * size_];
    solution = new T [size_ * size_];
}

template<class T>
Gauss_solver<T>::~Gauss_solver()
{
    delete [] sums;
    delete [] solution;
}


template<class T>
void Gauss_solver<T>::setGauss_solver(const T * a /* matrix A */, const T * b /* b in Ax=b */)
{
    for (size_t i = 0; i < SquareMatrix<T>::size; ++i)
    {
        sums[i] = b[i];
        for (int j = 0; j < SquareMatrix<T>::size; ++j) {
            SquareMatrix<T>::setElement(i+1, j+1,  a[i * SquareMatrix<T>::size + j]);
//            std::cout << SquareMatrix<T>::element(i+1,j+1) << std::endl;
        }
    }
//    for (int i = 0; i < 4; ++i) {
//        std::cout << SquareMatrix<T>::Matrix::values[i] <<  std::endl;
//    }
}

template<class T>
void Gauss_solver<T>::printEqu()
{
    std::cout << "The Line eqution is:" << std::endl;
    for (size_t i = 0; i < SquareMatrix<T>::size; i++)
    {
        for (size_t j = 0; j < SquareMatrix<T>::size; j++)
            std::cout << SquareMatrix<T>::element(i+1, j+1) << "	";
        std::cout << "	" << sums[i] << std::endl;
    }
}

template<class T>
void Gauss_solver<T>::printSolution() const
{
    std::cout << "The Line solution is: " << std::endl;
    for (size_t i = 0; i < SquareMatrix<T>::size; i++)
       std::cout << "x[" << i << "]=" << solution[i] << std::endl;
}

template<class T>
bool Gauss_solver<T>::solve()
{
    //check diagonal superior
    for (size_t i = 0 /* row */; i < SquareMatrix<T>::size; ++i)
    {
        T indiagonal_sum = 0; // sum of off-diagonal elements
//        pVecOut_x->SetElement( uRow , 0.0 );
        for (size_t j = 0/* col */; j < SquareMatrix<T>::size; ++j)
        {
            if (i != j)
            {
                indiagonal_sum += std::fabs( SquareMatrix<T>::element(i+1, j+1) );
            }
        }
        if (indiagonal_sum > SquareMatrix<T>::element(i+1, i+1))
        {
            std::cerr << "maybe not iteration" << std::endl;
        }
    }

    //begin Gauss Seidel iteration
    size_t iter_time = 0;
    T e;//error value
    auto *temp = new T [SquareMatrix<T>::size];//temp in iteration
    for (int i = 0; i < SquareMatrix<T>::size; ++i)
    {
        temp[i] = 0;
    }
    auto *s_temp = new T [SquareMatrix<T>::size];//store range of error
    do{
        for (int i = 0; i < SquareMatrix<T>::size; ++i)
        {
            T sum_ax = 0;
            for (int j = 0; j < i; ++j)
            {
                sum_ax += SquareMatrix<T>::element(i+1, j+1) * solution[j];
            }
            for (int j = i+1; j < SquareMatrix<T>::size; ++j)
            {
                sum_ax += SquareMatrix<T>::element(i+1, j+1) * temp[j];
            }
            solution[i] = (sums[i] - sum_ax) / SquareMatrix<T>::element(i+1, i+1);
            s_temp[i] = (temp[i] - solution[i]) * (temp[i] - solution[i]);
        }
        for (int i = 0; i < SquareMatrix<T>::size; ++i)
        {
            temp[i] = solution[i] ;//update
        }
        e = s_temp[0];
        for (int i = 0; i < SquareMatrix<T>::size; ++i)
        {
            if (e < s_temp[i]) e = s_temp[i];
        }
        iter_time++;
//        printSolution();
    } while (iter_time < MAX_ITERATION && e > ERROR_VALUE );
    delete [] temp;
    delete [] s_temp;
    return true;
}

template<class T>
bool Gauss_solver<T>::LU_solve()
{
    auto * middle = new T [SquareMatrix<T>::size]; // Y in LY = b
    auto * col_main = new T [SquareMatrix<T>::size]; // main element in col
    for (int i = 0; i < SquareMatrix<T>::size; ++i)
    {
        middle [i] = 0;
        col_main [i] = 0;
        solution [i] = 0;
    }
    for (size_t k = 0; k < SquareMatrix<T>::size; ++k)
    {
        //choose main elements in col选列主元
        size_t index = k;
        for (int i = k; i < SquareMatrix<T>::size; ++i)
        {
            T temp = 0;
            for (int m = 0; m < k; ++m)
            {
                temp += SquareMatrix<T>::element(i+1, m+1) * SquareMatrix<T>::element(m+1, k+1);
            }
            col_main[i] = SquareMatrix<T>::element(i+1, k+1) - temp;
            if (col_main[index] < col_main[i])
            {
                index = i;
            }

        }
        // exchange row
        T temp = 0;
        for (int i = 0; i < SquareMatrix<T>::size; ++i)
        {
            temp = SquareMatrix<T>::element(index+1, i+1);
            SquareMatrix<T>::setElement(index+1, i+1, SquareMatrix<T>::element(k+1, i+1));
            SquareMatrix<T>::setElement(k+1, i+1, temp);
        }
        temp = sums[index];
        sums[index] = sums[k];
        sums[k] = temp;

        //construct L and U
        for (size_t j = k; j < SquareMatrix<T>::size; j++)
        {
            T temp = 0;
            for (size_t m = 0; m < k; m++)
            {
                temp += SquareMatrix<T>::element(k+1, m+1) * SquareMatrix<T>::element(m+1, j+1);
            }
            SquareMatrix<T>::setElement(k+1,j+1, SquareMatrix<T>::element(k+1, j+1) - temp);//构造一行的向量 construct one row vector in U
        }
        for (size_t i = k + 1; i < SquareMatrix<T>::size; i++)
        {
            T temp = 0;
            for (int m = 0; m < k; m++)
            {
                temp += SquareMatrix<T>::element(i+1, m+1) * SquareMatrix<T>::element(m+1, k+1);
            }
            SquareMatrix<T>::setElement(i+1,k+1, ((SquareMatrix<T>::element(i+1, k+1) - temp) / SquareMatrix<T>::element(k+1,k+1)));
            //construct one col vector in L
        }
    }
//    求解LY = B   solve LY=B
    middle[0] = sums[0];
    for (size_t i = 1; i < SquareMatrix<T>::size; i++)
    {
        T temp = 0;
        for (size_t j = 0; j < i; j++)
        {
            temp += SquareMatrix<T>::element(i+1, j+1) * middle[j];
        }
//        Y[i] = B[i] - temp;
        middle[i] = sums[i] - temp;
    }
    //求解UX = Y  solve UX = Y
    solution[SquareMatrix<T>::size - 1] = middle[SquareMatrix<T>::size - 1] / SquareMatrix<T>::element(SquareMatrix<T>::size, SquareMatrix<T>::size);
    for (int i = SquareMatrix<T>::size - 2; i >= 0; i--)
    {

        T  temp = 0;
        for (size_t j = i + 1; j < SquareMatrix<T>::size; j++)
        {
            temp += SquareMatrix<T>::element(i+1, j+1) * solution[j];
        }
        solution[i] = (middle[i] - temp) / SquareMatrix<T>::element(i+1, i+1);
    }
//    //打印X
//    cout << "此方程组的解为：" << endl;
//    for (i = 0; i < N; i++)
//    {
//        cout << X[i] << " ";
//    }
//    cout << endl;
    delete [] middle;
    delete [] col_main;
    return true;
}
#endif //LINEAR_SYSTEM_GAUSS_SOLVER_H
