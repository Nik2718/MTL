#include "int_matrix.h"

explicit IntegerMatrix::IntegerMatrix(size_type row, size_type col) {
    if(col == 0 || row == 0){
        throw IntegerMatrix_Exception("Zero size parametrs of a matrix");
        col = row = 1;
    }

    numberOfColumns_ = col;
    numberOfRows_ = row;

    Matrix_ = new boost::multiprecision::checked_int256_t*[numberOfRows_];

    if(!Matrix_) {
        std::cerr << "Memory error when creating a matrix" << std::endl;
        exit(-1);
    }

    for(size_type i = 0; i < numberOfRows_; ++i) {
        Matrix_[i] = new boost::multiprecision::checked_int256_t[numberOfColumns_];

        if(! Matrix_[i]) {
            std::cerr << "Memory error when creating a matrix" << std::endl;
            exit(-1);            
        }
    }
 
    for(size_type i = 0; i < numberOfRows_; ++i) {
        for(size_type j = 0; j < numberOfColumns_; ++j) {
            Matrix_[i][j] = 0;
        }
    }
}

IntegerMatrix::IntegerMatrix(std::vector<std::vector<boost::multiprecision::checked_int256_t>>& M) {
    if(M.size() == 0) {
        throw IntegerMatrix_Exception("Zero size parametrs of a matrix");
        numberOfRows_ = 1;
        numberOfColumns_ = 1;

        Matrix_ = new boost::multiprecision::checked_int256_t*[1];

        if(!Matrix_) {
            std::cerr << "Memory error when creating a matrix" << std::endl;
            exit(-1);
        }

        Matrix_[0] = new boost::multiprecision::checked_int256_t[1];

        if(!Matrix_[0]) {
            std::cerr << "Memory error when creating a matrix" << std::endl;
            exit(-1);
        }

        Matrix_[0][0] = 0;

        return;
    }

    if(M.size() > MAXIMUM_LINEAR_SIZE) {
        throw IntegerMatrix_Exception("The required number of rows is too large");
        std::cerr << '\n' << "(!) The matrix was trancated" << '\n';
        numberOfRows_ = MAXIMUM_LINEAR_SIZE;
    }
    else numberOfRows_ = M.size();

    Matrix_ = new boost::multiprecision::checked_int256_t*[numberOfRows_];

    if(!Matrix_) {
        std::cerr << "Memory error when creating a matrix" << std::endl;
        exit(-1);
    }

    if(M[0].size() == 0) {
        throw IntegerMatrix_Exception("Zero size parametrs of a matrix");
        numberOfColumns_ = 1;

        for(size_type i = 0; i < numberOfRows_; ++i) {
            Matrix_[i] = new boost::multiprecision::checked_int256_t[1];

            if(! Matrix_[i]) {
                std::cerr << "Memory error when creating a matrix" << std::endl;
                exit(-1);            
            }
        }

        for(size_type i = 0; i < numberOfRows_; ++i) {
            Matrix_[i][0] = 0;
        }
        return;
    }

    if(M[0].size() > MAXIMUM_LINEAR_SIZE) {
        throw IntegerMatrix_Exception("The required number of colums is too large");
        std::cerr << '\n' << "(!) The matrix was trancated" << '\n';
        numberOfColumns_ = MAXIMUM_LINEAR_SIZE;
    }

    for(size_type i = 0; i < numberOfRows_; ++i){
        for(size_type j = 0; j < numberOfColumns_; ++j){
            Matrix_[i][j] = M[i][j];
        }
    }

}

IntegerMatrix::~IntegerMatrix()
{
    for(size_type i = 0; i < numberOfRows_; ++i){
        delete [] Matrix_[i];
    }

    delete [] Matrix_;
}


std::ostream& operator<<(std::ostream& os, const IntegerMatrix& M)
{
    IntegerMatrix::size_type maximumSize = 1, currentSize;
    for(IntegerMatrix::size_type i = 0; i < M.numberOfRows_; ++i)
    {
        for(IntegerMatrix::size_type j = 0; j < M.numberOfColumns_; ++j)
        {

        }
    }
}