#include "SquareMatrix.h"

template<class T>
SquareMatrix<T>::SquareMatrix(int size_): Matrix<T>(size_, size_, true){}

template<class T>
SquareMatrix<T>::SquareMatrix(int size_, T *value_ptr) : Matrix<T>(size_, size_, true)
{
    for (int i = 0; i < size_*size_; ++i)
    {
        Matrix<T>::values[i] = value_ptr[i];
    }
}

template<class T>
SquareMatrix<T>::~SquareMatrix() {}

