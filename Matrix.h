#ifndef LINEAR_SYSTEM_MATRIX_H
#define LINEAR_SYSTEM_MATRIX_H
//#pragma once          in windows
#include "iostream"

template <class T>
class Matrix
{
public:

    // constructor where we want to preallocate ourselves
    Matrix(int rows, int cols, bool preallocate);
    // constructor where we already have allocated memory outside
    Matrix(int rows, int cols, T *values_ptr);
    Matrix(const Matrix<T> & mat_);//deep copy method
    // destructor
    virtual ~Matrix();
    int getSize(){return size_of_values;}
    // Print out the values in our matrix
    void printValues();
    virtual void printMatrix();

    friend Matrix<T> operator+(const Matrix<T> &mat1, const Matrix<T> &mat2);

//    // Perform some operations with our matrix
//    virtual void matMatMult(Matrix& mat_left, Matrix& output);

    // Explicitly using the C++11 nullptr here
    T *values = nullptr;
    int rows = -1;
    int cols = -1;

// Private variables - there is no need for other classes
// to know about these variables
private:

    int size_of_values = -1;
    bool preallocated = false;

};

// Constructor - using an initialisation list here
template <class T>
Matrix<T>::Matrix(int rows, int cols, bool preallocate): rows(rows), cols(cols), size_of_values(rows * cols), preallocated(preallocate)
{
    // If we want to handle memory ourselves
    if (this->preallocated)
    {
        // Must remember to delete this in the destructor
        this->values = new T[size_of_values];
    }
}

// Constructor - now just setting the value of our T pointer
template <class T>
Matrix<T>::Matrix(int rows, int cols, T *values_ptr): rows(rows), cols(cols), size_of_values(rows * cols)
{
    for (int i = 0; i < rows * cols; ++i)
    {
        values[i] = values_ptr[i];
    }
}

//Deep copy
template<class T>
Matrix<T>::Matrix(const Matrix<T> & mat)
{
    rows = mat.rows;
    cols = mat.cols;
    preallocated = mat.preallocated;
    size_of_values = mat.size_of_values;
    for (int i = 0; i < size_of_values; ++i)
    {
       values[i] = mat.values;
    }
}

// destructor
template <class T>
Matrix<T>::~Matrix()
{
    // Delete the values array
    if (this->preallocated){
        delete[] this->values;
    }
}

// Just print out the values in our values array
template <class T>
void Matrix<T>::printValues()
{
    std::cout << "Printing values" << std::endl;
    for (int i = 0; i< this->size_of_values; i++)
    {
        std::cout << this->values[i] << " ";
    }
    std::cout << std::endl;
}

// Explicitly print out the values in values array as if they are a matrix
template <class T>
void Matrix<T>::printMatrix()
{
    std::cout << "Printing matrix" << std::endl;
    for (int j = 0; j< this->rows; j++)
    {
        std::cout << std::endl;
        for (int i = 0; i< this->cols; i++)
        {
            // We have explicitly used a row-major ordering here
            std::cout << this->values[i + j * this->cols] << " ";
        }
    }
    std::cout << std::endl;
}

template<class T>
Matrix<T> operator+(const Matrix<T> &mat1, const Matrix<T> &mat2)
{
    std::shared_ptr<T> ptr_mat_value ( new T [Matrix<T>::size_of_values] );
    for (size_t i = 0; i < Matrix<T>::size_of_values; ++i)
    {
        ptr_mat_value[i] = mat1.values[i] + mat2.values[i];
    }
    auto *mat = new Matrix<T>(Matrix<T>::rows, Matrix<T>::cols, ptr_mat_value);
    return *mat;
}

#endif //LINEAR_SYSTEM_MATRIX_H
