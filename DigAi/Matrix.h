#include <iostream>
#include <tuple>
#include <vector>

template <typename T>
class matrix {
public:
    matrix(int n, int m, T* mat = nullptr) 
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

    matrix(const matrix<T>& copy) 
    {
        std::cout << "no no " << std::endl;
        this->n = copy.n;
        this->m = copy.m;
        this->mat = new T[n * m];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                this->mat[i * m + j] = copy.mat[i * m + j];
            }
        }

    }

    T* operator[](int i)
    {
        return mat + (i * m);
    }

    void operator+=(matrix& other)
    {
        for (int i = 0; i < this->n * this->m; i++) {
            this->mat[i] += other.mat[i];
        }
    }

    void operator*=(T val)
    {
        for (int i = 0; i < n * m; i++) {
            mat[i] *= val;
        }
    }

    matrix operator-=(T val)
    {
        for (int i = 0; i < n * m; i++) {
            mat[i] -= val;
        }
    }

    void operator-=(matrix<T>& other)
    {
        for (int i = 0; i < n * m; i++) {
            mat[i] -= other.mat[i];
        }
    }

    void Set(matrix<T>& other)
    {
        for (int i = 0; i < n * m; i++) {
            mat[i] = other.mat[i];
        }
    }

    void mul(matrix& other, matrix& into, bool add = false)
    {
        for (int i = 0; i < this->n; i++) {
            for (int j = 0; j < other.m; j++) {
                if(!add)
                    into.mat[i * other.m + j] = 0;
                for (int k = 0; k < this->m; k++) {
                    into.mat[i * other.m + j] += this->mat[i * this->m + k] * other.mat[k * other.m + j];
                }
            }
        }
    }

    void mulTranspose(matrix& other, matrix& into, bool add = false) {
        for (int i = 0; i < this->n; i++) {
            for (int j = 0; j < other.n; j++) {
                if (!add)
                    into.mat[i * other.n + j] = 0;
                for (int k = 0; k < this->m; k++) {
                    into.mat[i * other.n + j] += this->mat[i * this->m + k] * other.mat[j * other.m + k];
                }
            }
        }
    }

    void TransposeMul(matrix& other, matrix& into, bool add = false) {
        for (int i = 0; i < this->m; i++) {
            for (int j = 0; j < other.m; j++) {
                if (!add)
                    into.mat[i * other.m + j] = 0;
                for (int k = 0; k < this->n; k++) {
                    into.mat[i * other.m + j] += this->mat[k * this->m + i] * other.mat[k * other.m + j];
                }
            }
        }
    }

    void CrossCorrelation(matrix& other, matrix& into, bool add = false) {
        if (this->n - other.n + 1 != into.n || this->m - other.m + 1 != into.m)
            throw "mtrix size in wrong";

        for (int i = 0; i < this->n - other.n + 1; i++) {
            for (int j = 0; j < this->m - other.m + 1; j++) {
                if (!add)
                    into.mat[i * into.m + j] = 0;
                for (int y = 0; y < other.n; y++) {
                    for (int x = 0; x < other.m; x++) {
                        into.mat[i * into.m + j] += this->mat[(i + y) * this->m + j + x] * other.mat[y * other.m + x];
                    }
                }
            }
        }
    }

    void FullConvolution(matrix& other, matrix& into, bool add = false) {
        if (this->n + other.n - 1 != into.n || this->m + other.m - 1 != into.m)
            throw "mtrix size in wrong";

        for (int i = 0 - other.n + 1; i < this->n; i++) {
            for (int j = 0 - other.m + 1; j < this->m; j++) {
                int ii = i + other.n - 1;
                int jj = j + other.m - 1;
                if (!add)
                    into.mat[ii * into.m + jj] = 0;
                int startY = std::max(-i, 0);
                int endY = std::min(other.n, this->n - i);
                int startX = std::max(-j, 0);
                int endX = std::min(other.m, this->m - j);
                for (int y = startY; y < endY; y++) {
                    for (int x = startX; x < endX; x++) {
                        into.mat[ii * into.m + jj] += this->mat[(i + y) * this->m + j + x] * other.mat[(other.n - y - 1) * other.m + other.m - x - 1];
                    }
                }
            }
        }
    }

    matrix transpose()
    {
        matrix newmat(this->m, this->n);
        for (int i = 0; i < this->n; i++) {
            for (int j = 0; j < this->m; j++) {
                newmat[j][i] = mat[i * m + j];
            }
        }
        return newmat;
    }

    friend std::ostream& operator<<(std::ostream& os, const matrix& toPrint)
    {

        for (int i = 0; i < toPrint.n; i++) {
            for (int j = 0; j < toPrint.m; j++) {
                os << toPrint.mat[i * toPrint.m + j] << " ";
            }
            os << std::endl;
        }
        return os;
    }

    void RandomInit()
    {
        for (int i = 0; i < n * m; i++) {
            mat[i] = GenerateRandom();
        }
    }

    void Zeros() {
        for (int i = 0; i < n * m; i++) {
            mat[i] = 0;
        }
    }

    T* GetPointer()
    {
        return mat;
    }

    ~matrix()
    {
        if (selfAllocated)
        {
            delete mat;
        }
    }

private:
    double GenerateRandom() {
        return (rand() % 2001 - 1000.0) / 1000.0;
    }

    int n, m;
    bool selfAllocated;
    T* mat;
};

template <typename T>
class Vector :
    public matrix<T> {
public:
    Vector(int n, T* vec = nullptr) :matrix<T>(n, 1, vec) {};
};