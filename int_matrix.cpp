#include "int_matrix.h"

IntegerMatrix::IntegerMatrix(size_type row, size_type col) {
    if(col == 0 || row == 0){
        throw IntegerMatrix_Exception("Zero size parameter of a matrix");
        col = row = 1;
    }

    numberOfColumns_ = col;
    numberOfRows_ = row;

    Matrix_ = new integer*[numberOfRows_];

    if(!Matrix_) {
        std::cerr << "Memory error when creating a matrix" << std::endl;
        exit(-1);
    }

    for(size_type i = 0; i < numberOfRows_; ++i) {
        Matrix_[i] = new integer[numberOfColumns_];

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

IntegerMatrix::IntegerMatrix(const std::vector<std::vector<integer>>& M) {

    if(M.size() == 0 || M[0].size() == 0) {
        throw IntegerMatrix_Exception("Zero size parameter of a matrix");
        numberOfColumns_ = numberOfRows_ = 1;
    }
    else if(M.size() > getMaxSize() || M[0].size() > getMaxSize()){
        throw IntegerMatrix_Exception("Matrix size is too large");
        numberOfColumns_ = numberOfRows_ = 1;
    }
    else{
        numberOfRows_ = M.size();
        numberOfColumns_ = M[0].size();
    }

    Matrix_ = new integer*[numberOfRows_];

    if(!Matrix_) {
        std::cerr << "Memory error when creating a matrix" << std::endl;
        exit(-1);
    }

    for(size_type i = 0; i < numberOfRows_; ++i) {
        Matrix_[i] = new integer[numberOfColumns_];

        if(! Matrix_[i]) {
            std::cerr << "Memory error when creating a matrix" << std::endl;
            exit(-1);            
        }
    }

    for(size_type i = 0; i < numberOfRows_; ++i){
        for(size_type j = 0; j < numberOfColumns_; ++j){
            Matrix_[i][j] = M[i][j];
        }
    }
}

IntegerMatrix& IntegerMatrix::operator=(const IntegerMatrix& M) {
    integer** M2 = new integer*[M.numberOfRows_];
    if(!M2){
        std::cerr << "Memory error when creating a matrix" << std::endl;
        exit(-1);
    }

    for(size_type i = 0; i < M.numberOfRows_; ++i){
        M2[i] = new integer[M.numberOfColumns_];
        if(!M2[i]){
            std::cerr << "Memory error when creating a matrix" << std::endl;
            exit(-1);           
        }
    }

    for(size_type i = 0; i < M.numberOfRows_; ++i){
        for(size_type j = 0; j < M.numberOfColumns_; ++j){
            M2[i][j] = M.Matrix_[i][j];
        }
    }

    for(size_type i = 0; i < this->numberOfRows_; ++i){
        delete [] this->Matrix_[i];
    }
    delete [] this->Matrix_;

    this->Matrix_ = M2;
    this->numberOfRows_ = M.numberOfRows_;
    this->numberOfColumns_ = M.numberOfColumns_;

    return *this;
}
       

bool IntegerMatrix::operator==(const IntegerMatrix& A) const {
    if(this->numberOfRows_ != A.numberOfRows_) return false;
    if(this->numberOfColumns_ != A.numberOfColumns_) return false;

    for(size_type i = 0; i < this->numberOfRows_; ++i){
        for(size_type j = 0; j < this->numberOfColumns_; ++j){
            if(this->Matrix_[i][j] != A.Matrix_[i][j]) return false;
        }
    }
    return true;
}


IntegerMatrix::IntegerMatrix(const std::initializer_list<
                                   std::initializer_list<integer>>& M){

    if(M.size() == 0 || M.begin()->size() == 0) {
        throw IntegerMatrix_Exception("Zero size parameter of a matrix");
        numberOfColumns_ = numberOfRows_ = 1;
    }
    else if(M.size() > getMaxSize() || M.begin()->size() > getMaxSize()){
        throw IntegerMatrix_Exception("Matrix size is too large");
        numberOfColumns_ = numberOfRows_ = 1;
    }
    else{
        numberOfRows_ = M.size();
        numberOfColumns_ = M.begin()->size();
    }

    Matrix_ = new integer*[numberOfRows_];

    if(!Matrix_) {
        std::cerr << "Memory error when creating a matrix" << std::endl;
        exit(-1);
    }

    for(size_type i = 0; i < numberOfRows_; ++i) {
        Matrix_[i] = new integer[numberOfColumns_];

        if(! Matrix_[i]) {
            std::cerr << "Memory error when creating a matrix" << std::endl;
            exit(-1);            
        }
    }
    int i = 0, j = 0;
    for(const std::initializer_list<integer>& row : M){
        j = 0;
        for(const integer& el: row){
            Matrix_[i][j] = el;
            ++j;
        }
        ++i;
    }
}

IntegerMatrix::~IntegerMatrix() {
    for(size_type i = 0; i < numberOfRows_; ++i){
        delete [] Matrix_[i];
    }

    delete [] Matrix_;
}


std::ostream& operator<<(std::ostream& os, const IntegerMatrix& M) {
    unsigned int maxLength = 1, currentLength;
    for(IntegerMatrix::size_type i = 0; i < M.numberOfRows_; ++i) {
        for(IntegerMatrix::size_type j = 0; j < M.numberOfColumns_; ++j) {
            currentLength = IntegerMatrix::number_length10(M.Matrix_[i][j]);
            if(maxLength < currentLength) maxLength = currentLength;
        }
    }

    int difference;
    for(IntegerMatrix::size_type i = 0; i < M.numberOfRows_; ++i) {
        os << '\n' << "||";
        for(IntegerMatrix::size_type j = 0; j < M.numberOfColumns_; ++j) {
            difference = maxLength - 
                         IntegerMatrix::number_length10(M.Matrix_[i][j]);
            for(int k = 0; k < difference; ++k){
                os << ' ';
            }
            os << M.Matrix_[i][j];
            if(j != M.numberOfColumns_ - 1) os << ' ';
        }
        os << "||";
    }
    os << '\n';

    return os;
}


unsigned int IntegerMatrix::number_length10(integer a){
    unsigned int result = (a < 0) ? 2: 1;

    a = a/10;
    while(a != 0) {
        ++result;
        a = a/10; 
    }

    return result;
}