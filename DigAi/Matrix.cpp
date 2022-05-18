#include "Matrix.h"

/*
template<typename T>
std::ostream& operator<<(std::ostream& os, const matrix<T>& toPrint)
{

    for (int i = 0; i < toPrint.n; i++) {
        for (int j = 0; j < toPrint.m; j++) {
            os << toPrint.mat[i * toPrint.m + j] << " ";
        }
        os << std::endl;
    }
    return os;

}


template<typename T>
inline matrix<T>::matrix(int n, int m, T* mat)
{
    this->n = n;
    this->m = m;
    if (mat) {
        this->mat = mat;
        selfAllocated = false;
    }
    else {
        this->mat = new T[n * m];
        selfAllocated = true;
    }
}

template<typename T>
inline matrix<T>::matrix(const matrix<T>& copy)
{

    this->n = copy.n;
    this->m = copy.m;
    this->mat = new T[n * m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            this->mat[i * m + j] = copy.mat[i * m + j];
        }
    }

}

template<typename T>
void matrix<T>::add(matrix& other)
{
    for (int i = 0; i < this->n * this->m; i++) {
        this->mat[i] += other->mat[i];
    }
}

template<typename T>
inline T* matrix<T>::operator[](int i)
{
    return mat + (i * m);
}

template<typename T>
inline matrix<T> matrix<T>::operator*(matrix& other)
{

    if (this->m != other.n)
        throw "Wrong size mats for mul";
    matrix newmat(this->n, other.m);
    for (int i = 0; i < this->n; i++) {
        for (int j = 0; j < other.m; j++) {
            newmat.mat[i * other.m + j] = 0;
            for (int k = 0; k < this->m; k++) {
                newmat.mat[i * other.m + j] += this->mat[i * this->m + k] * other.mat[k * other.m + j];
            }
        }
    }
    return newmat;

}

template<typename T>
inline void matrix<T>::mul(matrix& other, matrix& into)
{

    for (int i = 0; i < this->n; i++) {
        for (int j = 0; j < other.m; j++) {
            into.mat[i * other.m + j] = 0;
            for (int k = 0; k < this->m; k++) {
                into.mat[i * other.m + j] += this->mat[i * this->m + k] * other.mat[k * other.m + j];
            }
        }
    }

}

template<typename T>
inline matrix<T> matrix<T>::transpose()
{

    matrix newmat(this->m, this->n);
    for (int i = 0; i < this->n; i++) {
        for (int j = 0; j < this->m; j++) {
            newmat[j][i] = mat[i * m + j];
        }
    }
    return newmat;

}

double GenerateRandom() {
    return (rand() % 2001 - 1000.0) / 1000.0;
}

template<typename T>
void matrix<T>::RandomInit()
{
    for (int i = 0; i < n * m; i++) {
        mat[i] = GenerateRandom();
    }
}

template<typename T>
T* matrix<T>::GetPointer()
{
    return mat;
}

template<typename T>
matrix<T>::~matrix()
{
    if(selfAllocated)
    {
        delete mat;
    }
}

*/