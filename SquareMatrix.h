#ifndef LINEAR_SYSTEM_SQUAREMATRIX_H
#define LINEAR_SYSTEM_SQUAREMATRIX_H
//#define USE_CSRMATRIX_ 1 //1 to use CSRMatrix
//
//#if !USE_CSRMATRIX_
#include "Matrix.h"


//VECTOR
template<class T>
class LinearVector
{
private:
    size_t vec_dim;
    T * vec_data;
//    std::shared_ptr<T> vec_data_smartptr;     TODO: smartptr! set value function, Try sparse, explict, 接口,初始向量
public:
    explicit LinearVector(size_t vec_dim_ = 1);
    explicit LinearVector(T * vec_data_, size_t vec_dim_ = 1);
    ~LinearVector();
    void setElement(size_t index_, const T& insert);
    size_t getDim() const {return vec_dim;}
    T& getData(size_t index_) const {return vec_data[index_];}
    void printVec() const;
};

template<class T>
LinearVector<T>::LinearVector(size_t vec_dim_)
{
    vec_data = new T [vec_dim_];
    vec_dim = vec_dim_;
//    vec_data_smartptr = new T [vec_dim_];
}

template<class T>
LinearVector<T>::LinearVector(T *vec_data_, size_t vec_dim_)
{
    vec_data = new T [vec_dim_];
    vec_dim = vec_dim_;
    for (int i = 0; i < vec_dim; ++i)
    {
        vec_data[i] = vec_data_[i];
    }
}

template<class T>
LinearVector<T>::~LinearVector()
{
    delete [] vec_data;
}

template<class T>
void LinearVector<T>::setElement(size_t index_, const T& insert)
{
    vec_data[index_] = insert;
}

template<class T>
void LinearVector<T>::printVec() const {}//TODO: May implement


//SQUARE MATRIX
template<class T>
class SquareMatrix: public Matrix<T>
{
public:
    explicit SquareMatrix(int size_);
    SquareMatrix(int size_, T * value_ptr);
    ~SquareMatrix();
    inline T element(int i, int j){return Matrix<T>::values[(i-1)*size + (j-1)];}//i,j is realistic number index
    inline void setElement(size_t i, size_t j, T value){Matrix<T>::values[(i-1)*size + (j-1)] = value;}//i, j is real index
    bool Trans();
    int size = 0;
private:
};

template<class T>
SquareMatrix<T>::SquareMatrix(int size_): Matrix<T>(size_, size_, true){size = size_;}

template<class T>
SquareMatrix<T>::SquareMatrix(int size_, T *value_ptr) : Matrix<T>(size_, size_, true)
{
    for (int i = 0; i < size_*size_; ++i)
    {
        Matrix<T>::values[i] = value_ptr[i];
    }
    size = size_;
}

template<class T>
SquareMatrix<T>::~SquareMatrix() {}

template<class T>
bool SquareMatrix<T>::Trans() {}



#endif //LINEAR_SYSTEM_SQUAREMATRIX_H
