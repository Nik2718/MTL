//Realization of integer matrices

#include "../include/int_matrix.hpp"

//******************************************************************************
//***********************Constructors and destructor**********************


//Creates a matrix with the given numbers of rows
//each entry is assigned to the last argument
IntegerMatrix::IntegerMatrix(size_type row, size_type col, integer entry) {
    //Checking arguments
    if (col == 0 || row == 0) {
        //An empty matrix is not allowed
        throw IntegerMatrix_Exception("Zero size parameter of a matrix");
        numberOfColumns_ = numberOfRows_ = 1;
    } else if (col > getMaxSize() || row > getMaxSize()){
        throw IntegerMatrix_Exception("Matrix size is too large");
        numberOfColumns_ = numberOfRows_ = 1;
    } else {
        numberOfRows_ = row;
        numberOfColumns_ = col;
    }

    //Allocating memory
    Matrix_ = new integer*[numberOfRows_];
    if (!Matrix_) {
        std::cerr << "Memory error when creating a matrix" << std::endl;
        exit(-1);
    }
    for (size_type i = 0; i < numberOfRows_; ++i) {
        Matrix_[i] = new integer[numberOfColumns_];
        if (! Matrix_[i]) {
            std::cerr << "Memory error when creating a matrix" << std::endl;
            exit(-1);            
        }
    }

    //All entries will be equal to "entry"
    for (size_type i = 0; i < numberOfRows_; ++i) {
        for (size_type j = 0; j < numberOfColumns_; ++j) {
            Matrix_[i][j] = entry;
        }
    }
}

//Creating the matrix as copy of a two-dimensional vector
IntegerMatrix::IntegerMatrix(const std::vector<std::vector<integer>>& M) {
    //Checking arguments
    if (M.size() == 0 || M[0].size() == 0) {
        //An empty matrix is not allowed
        throw IntegerMatrix_Exception("Zero size parameter of a matrix");
        numberOfColumns_ = numberOfRows_ = 1;
    } else if (M.size() > getMaxSize() || M[0].size() > getMaxSize()) {
        throw IntegerMatrix_Exception("Matrix size is too large");
        numberOfColumns_ = numberOfRows_ = 1;
    } else {
        numberOfRows_ = M.size();
        numberOfColumns_ = M[0].size();
    }

    //Allocating memory
    Matrix_ = new integer*[numberOfRows_];
    if (!Matrix_) {
        std::cerr << "Memory error when creating a matrix" << std::endl;
        exit(-1);
    }
    for (size_type i = 0; i < numberOfRows_; ++i) {
        Matrix_[i] = new integer[numberOfColumns_];
        if (! Matrix_[i]) {
            std::cerr << "Memory error when creating a matrix" << std::endl;
            exit(-1);            
        }
    }

    //Copying entries
    for (size_type i = 0; i < numberOfRows_; ++i) {
        for (size_type j = 0; j < numberOfColumns_; ++j) {
            Matrix_[i][j] = M[i][j];
        }
    }
}

//Creating a matrix from an initializer list
IntegerMatrix::IntegerMatrix(const std::initializer_list<
                                   std::initializer_list<integer>>& M) {
    //Checking arguments
    if (M.size() == 0 || M.begin()->size() == 0) {
        //An empty matrix is not allowed
        throw IntegerMatrix_Exception("Zero size parameter of a matrix");
        numberOfColumns_ = numberOfRows_ = 1;
    } else if (M.size() > getMaxSize() || M.begin()->size() > getMaxSize()) {
        throw IntegerMatrix_Exception("Matrix size is too large");
        numberOfColumns_ = numberOfRows_ = 1;
    } else {
        numberOfRows_ = M.size();
        numberOfColumns_ = M.begin()->size();
    }

    //Allocating memory
    Matrix_ = new integer*[numberOfRows_];
    if (!Matrix_) {
        std::cerr << "Memory error when creating a matrix" << std::endl;
        exit(-1);
    }
    for (size_type i = 0; i < numberOfRows_; ++i) {
        Matrix_[i] = new integer[numberOfColumns_];
        if (! Matrix_[i]) {
            std::cerr << "Memory error when creating a matrix" << std::endl;
            exit(-1);
        }
    }

    //Copying entries
    {
        size_type i = 0, j = 0;
        for (const std::initializer_list<integer>& row : M) {
            j = 0;
            for (const integer& el: row) {
                Matrix_[i][j] = el;
                ++j;
            }
            ++i;
        }
    }
}

//Copy constructor
IntegerMatrix::IntegerMatrix(const IntegerMatrix& M) {
    numberOfColumns_ = M.numberOfColumns_;
    numberOfRows_ = M.numberOfRows_;

    //Allocating memory
    Matrix_ = new integer*[numberOfRows_];
    if (!Matrix_) {
        std::cerr << "Memory error when creating a matrix" << std::endl;
        exit(-1);
    }
    for (size_type i = 0; i < numberOfRows_; ++i) {
        Matrix_[i] = new integer[numberOfColumns_];
        if (! Matrix_[i]) {
            std::cerr << "Memory error when creating a matrix" << std::endl;
            exit(-1);
        }
    }

    //Copying entries
    for (size_type i = 0; i < numberOfRows_; ++i) {
        for (size_type j = 0; j < numberOfColumns_; ++j) {
            Matrix_[i][j] = M.Matrix_[i][j];
        }
    }
}

//Move constructor
IntegerMatrix::IntegerMatrix(IntegerMatrix&& M) noexcept {
    this->Matrix_ = M.Matrix_;
    this->numberOfRows_ = M.numberOfRows_;
    this->numberOfColumns_ = M.numberOfColumns_;

    M.Matrix_ = nullptr;
    M.numberOfRows_ = 0;
    M.numberOfColumns_ = 0;
}

//Destructor
IntegerMatrix::~IntegerMatrix() noexcept {
    for (size_type i = 0; i < numberOfRows_; ++i) {
        delete [] Matrix_[i];
    }
    delete [] Matrix_;
}

//******************************************************************************
//********************************Assignment*********************************

//Copy assignment
IntegerMatrix& IntegerMatrix::operator=(const IntegerMatrix& M) {

    //Allocating memory for the copy
    integer** M2 = new integer*[M.numberOfRows_];
    if (!M2){
        std::cerr << "Memory error when creating a matrix" << std::endl;
        exit(-1);
    }
    for (size_type i = 0; i < M.numberOfRows_; ++i) {
        M2[i] = new integer[M.numberOfColumns_];
        if (!M2[i]){
            std::cerr << "Memory error when creating a matrix" << std::endl;
            exit(-1);
        }
    }
    //Copying entries
    for (size_type i = 0; i < M.numberOfRows_; ++i) {
        for (size_type j = 0; j < M.numberOfColumns_; ++j) {
            M2[i][j] = M.Matrix_[i][j];
        }
    }

    //Freeing memory for the given matrix
    for (size_type i = 0; i < this->numberOfRows_; ++i) {
        delete [] this->Matrix_[i];
    }
    delete [] this->Matrix_;

    //Copying the pointer and the sizes
    this->Matrix_ = M2;
    this->numberOfRows_ = M.numberOfRows_;
    this->numberOfColumns_ = M.numberOfColumns_;

    return *this;
}

//Move assignment
IntegerMatrix& IntegerMatrix::operator=(IntegerMatrix&& M) noexcept {
    if (this != &M) {
        //Freeing memory for the given matrix
        for (size_type i = 0; i < this->getNumberOfRows(); ++i) {
            delete[] this->Matrix_[i];
        }
        delete [] this->Matrix_;

        this->Matrix_ = M.Matrix_;
        this->numberOfRows_ = M.numberOfRows_;
        this->numberOfColumns_ = M.numberOfColumns_;

        M.Matrix_ = nullptr;
        M.numberOfRows_ = 0;
        M.numberOfColumns_ = 0;
    }
    return *this;
}

//******************************************************************************
//********************************Comparison*********************************

bool IntegerMatrix::operator==(const IntegerMatrix& A) const noexcept {
    if (this->numberOfRows_ != A.numberOfRows_) return false;
    if (this->numberOfColumns_ != A.numberOfColumns_) return false;

    for (size_type i = 0; i < this->numberOfRows_; ++i){
        for (size_type j = 0; j < this->numberOfColumns_; ++j){
            if (this->Matrix_[i][j] != A.Matrix_[i][j]) return false;
        }
    }
    return true;
}

//******************************************************************************
//********************************Arithmetic*********************************

//Addition
IntegerMatrix& IntegerMatrix::operator+=(const IntegerMatrix & A) {
    if (A.getNumberOfColumns() != this->getNumberOfColumns() ||
        A.getNumberOfRows()    != this->getNumberOfRows()) {
        throw IntegerMatrix_Exception("Addition of matrices of distinct sizes");
        return *this;
    }

    for (size_type i = 0; i < A.getNumberOfRows(); ++i) {
        for (size_type j = 0; j < A.getNumberOfColumns(); ++j) {
            this->Matrix_[i][j] += A.Matrix_[i][j];
        }
    }
    return *this;
}

IntegerMatrix operator+(IntegerMatrix A, const IntegerMatrix& B) {
    A += B;
    return A;
}

//Multiplication
IntegerMatrix operator*(IntegerMatrix A, const IntegerMatrix& B) {
    if (A.getNumberOfColumns() != B.getNumberOfRows()) {
        throw IntegerMatrix_Exception(
              "Multiplication of matrices of inappropriate sizes");
        return IntegerMatrix(1,1,0);
    }

    IntegerMatrix::size_type common_size = A.getNumberOfColumns();
    IntegerMatrix C(A.getNumberOfRows(), B.getNumberOfColumns(), 0);

    for (IntegerMatrix::size_type i = 0; i < C.getNumberOfRows(); ++i) {
        for (IntegerMatrix::size_type j = 0; j < C.getNumberOfColumns(); ++j) {
            for (IntegerMatrix::size_type k = 0; k < common_size; ++k) {
                C.Matrix_[i][j] += A.Matrix_[i][k] * B.Matrix_[k][j];
            }
        }
    }
    return C;
}

IntegerMatrix& IntegerMatrix::operator*=(const IntegerMatrix & A){
    IntegerMatrix C = (*this) * A;
    *this = std::move(C);
    return *this;
}

//******************************************************************************
//************************Manipulation of rows and columns********************

//row i1  is changed to (row i1 + c * row i2)
//from the position "begin"
IntegerMatrix& IntegerMatrix::addRowToRow(size_type i1, size_type i2,
                                          integer c, size_type begin) {
    for (size_type j = begin; j < getNumberOfColumns(); ++j) {
        Matrix_[i1][j] += Matrix_[i2][j] * c;
    }
    return *this;
}

//rows are swapped from the position "begin"
IntegerMatrix& IntegerMatrix::swapRows(size_type i1, size_type i2, 
                                       size_type begin) {
    if (i1 == i2) return *this;
    for (size_type j = begin; j < getNumberOfColumns(); ++j) {
        std::swap(Matrix_[i1][j], Matrix_[i2][j]);
    }
    return *this;
}

//row i is multiplied by "c" from the position "begin"
IntegerMatrix& IntegerMatrix::multiplyRow(size_type i, integer c, 
                                          size_type begin) {
    for (size_type j = begin; j < getNumberOfColumns(); ++j) {
        Matrix_[i][j] *= c;
    }
    return *this;    
}

//Multiply two rows by 2 x 2 matrix on the left
IntegerMatrix& IntegerMatrix::transformRows(size_type i1,  size_type i2,
                                            integer   a11, integer   a12,
                                            integer   a21, integer   a22,
                                            size_type begin) {

    if (i1 == i2) return *this;
    integer buffer;
    for (size_type j = begin; j < getNumberOfColumns(); ++j) {
        buffer = Matrix_[i1][j];
        Matrix_[i1][j] = a11 * Matrix_[i1][j] + a12 * Matrix_[i2][j];
        Matrix_[i2][j] = a21 * buffer         + a22 * Matrix_[i2][j];
    }
    return *this;
}

//column j1  is changed to (column j1 + c * column i2)
//from the position "begin"
IntegerMatrix& IntegerMatrix::addColumnToColumn(size_type j1, size_type j2, 
                                                integer c, size_type begin) {
    for (size_type i = begin; i < getNumberOfRows(); ++i) {
        Matrix_[i][j1] += Matrix_[i][j2] * c;
    }
    return *this;
}

//columns are swapped from the position "begin"
IntegerMatrix& IntegerMatrix::swapColumns(size_type j1, size_type j2,
                                          size_type begin) {
    if (j1 == j2) return *this;
    for (size_type i = begin; i < getNumberOfRows(); ++i) {
        std::swap(Matrix_[i][j1], Matrix_[i][j2]);
    }
    return *this;
}

//columns is multiplied by "c" from the position "begin"
IntegerMatrix& IntegerMatrix::multiplyColumn(size_type j, integer c,
                                             size_type begin) {
    for (size_type i = begin; i < getNumberOfRows(); ++i) {
        Matrix_[i][j] *= c;
    }
    return *this;
}

//Multiplying two columns by 2 x 2 matrix on the right
IntegerMatrix& IntegerMatrix::transformColumns(size_type j1,  size_type j2,
                                               integer   a11, integer   a12,
                                               integer   a21, integer   a22, 
                                               size_type begin) {
    if (j1 == j2) return *this;
    integer buffer;
    for (size_type i = begin; i < getNumberOfRows(); ++i) {
        buffer = Matrix_[i][j1];
        Matrix_[i][j1] = Matrix_[i][j1] * a11 + Matrix_[i][j2] * a21;
        Matrix_[i][j2] = buffer     *     a12 + Matrix_[i][j2] * a22;
    }
    return *this;
}

//******************************************************************************
//********************************Output*********************************

//Formatted output of a matrix
std::ostream& operator<<(std::ostream& os, const IntegerMatrix& M) {
    unsigned int maxLength = 1, currentLength;

    //Searching for the maximum length of a matrix entry
    for (IntegerMatrix::size_type i = 0; i < M.numberOfRows_; ++i) {
        for (IntegerMatrix::size_type j = 0; j < M.numberOfColumns_; ++j) {
            currentLength = IntegerMatrix::number_length10(M.Matrix_[i][j]);
            if (maxLength < currentLength) maxLength = currentLength;
        }
    }
    //All entries are aligned to the longest one
    int difference;
    for (IntegerMatrix::size_type i = 0; i < M.numberOfRows_; ++i) {
        os << '\n' << "||";
        for (IntegerMatrix::size_type j = 0; j < M.numberOfColumns_; ++j) {
            difference = maxLength - 
                         IntegerMatrix::number_length10(M.Matrix_[i][j]);
            for (int k = 0; k < difference; ++k) {
                os << ' ';
            }
            os << M.Matrix_[i][j];
            if (j != M.numberOfColumns_ - 1) os << ' ';
        }
        os << "||";
    }
    os << '\n';
    return os;
}

//******************************************************************************
//***************************Auxiliary functions****************************

//number of digits in the 10-base system (the sign is took into account)
unsigned int IntegerMatrix::number_length10(integer a) {
    unsigned int result = (a < 0) ? 2: 1;

    a = a/10;
    while (a != 0) {
        ++result;
        a = a/10;
    }

    return result;
}