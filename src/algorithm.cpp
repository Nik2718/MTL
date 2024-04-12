//Algorithm for calculation of the Smith normal form

#include "../include/int_matrix.hpp"

//The type of matrix sizes
using size_type = IntegerMatrix::size_type;
//The type of matrix entries
using integer = IntegerMatrix::integer;

//States of the algorithm
enum class State{End, Continue};
State algorithmStep(IntegerMatrix& A, IntegerMatrix& Left, IntegerMatrix& Right,
                    size_type step);
void processRows   (IntegerMatrix& A, IntegerMatrix& Left, IntegerMatrix& Right,
                    size_type step);
void processColumns(IntegerMatrix& A, IntegerMatrix& Left, IntegerMatrix& Right,
                    size_type step);
//Checking whether the current row and column of the submatrix is
//zero except for, possibly, the corner element
bool isZero(IntegerMatrix& A, size_type step);
//Checking whether all entries of the next submatrix are divisible by
//the current corner entry
bool isDivisible(IntegerMatrix& A, size_type& jj, size_type step);

//Constructor for SmithForm
//The matrix A must be copied
SmithForm::SmithForm(IntegerMatrix A) {

    //The case of 1 x 1 matrices
    if (A.getNumberOfRows() == 1 && A.getNumberOfColumns() == 1) {
        isCorrect_ = true;
        minSize_ = 1;
        InvariantFactors_ = std::vector<integer> (1, A(0,0));
        Left_ = IntegerMatrix(1,1,1);
        Right_ = IntegerMatrix(1,1,1);
        return;
    }

    minSize_ =      std::min(A.getNumberOfRows(),    A.getNumberOfColumns());

    //Left and Right are assigned identity matrices
    Left_    = IntegerMatrix(A.getNumberOfRows(),    A.getNumberOfRows(), 0);
    Right_   = IntegerMatrix(A.getNumberOfColumns(), A.getNumberOfColumns(), 0);
    for (size_type i = 0; i < A.getNumberOfRows(); ++i) {
        Left_(i,i) = 1;
    }
    for (size_type i = 0; i < A.getNumberOfColumns(); ++i) {
        Right_(i,i) = 1;
    }

    //Steps of the algorithm
    State S = State::Continue;
    try{
        for (size_type step = 0; step < minSize_ &&
                                S == State::Continue; ++step) {
            S = algorithmStep(A, Left_, Right_, step);
        }
    }
    //This catch is relevant only when
    // IntegerMatrix::integer is checked boost integer
    //see documentation for boost/multiprecision/cpp_int.hpp
    catch(std::overflow_error &E) {
        isCorrect_ = false;
        InvariantFactors_ = std::vector<integer> (1, 0);
        Left_ = IntegerMatrix(1,1,1);
        Right_ = IntegerMatrix(1,1,1);
        return;
    }
    //Collecting the diagonal entries of the matrix in
    //InvariantFactors_ vector
    InvariantFactors_ = std::vector<integer> (minSize_, 0);
    for (size_type i = 0; i < minSize_; ++i) InvariantFactors_[i] = A(i,i);
    isCorrect_ = true;
}

State algorithmStep(IntegerMatrix& A, IntegerMatrix& Left, IntegerMatrix& Right,
                   size_type step) {
    //Searching for a nonzero entry
    if (A(step, step) == 0) {
        bool isSubmatrixZero = true;
        for (size_type i = step;
                      i < A.getNumberOfRows() && isSubmatrixZero; ++i) {
            for (size_type j = step; 
                          j < A.getNumberOfColumns() && isSubmatrixZero; ++j) {
                if (A(i,j) != 0) {
                    A.swapRows(step, i, step);
                    Left.swapRows(step, i);
                    A.swapColumns(step, j, step);
                    Right.swapColumns(step, j);
                    isSubmatrixZero = false;
                }
            }
        }
        //Only zeroes remains in the matrix
        if (isSubmatrixZero == true) return State::End;
    }
    //Processing rows and rows until the current step and row become zero
    while (isZero(A, step) == false) {
        processRows   (A, Left, Right, step);
        processColumns(A, Left, Right, step);
    }

    //Processing rows and columns until all entries of the next submatrix
    //become divisible by the current corner
    size_type jj;
    while (isDivisible(A, jj, step) == false) {
        //isDivisible receives a reference to jj
        A.addColumnToColumn(step, jj, 1, step);
        Right.addColumnToColumn(step, jj, 1);

        while (isZero(A, step) == false) {
            processRows   (A, Left, Right, step);
            processColumns(A, Left, Right, step);
        }
    }
    return State::Continue;
}

//Checking whether the current row and column of the submatrix is 
//zero except for, possibly, the corner element
bool isZero(IntegerMatrix& A, size_type step) {
    for (size_type i = step + 1; i < A.getNumberOfRows(); ++i) {
        if (A(i, step) != 0) return false;
    }
    for (size_type j = step + 1; j < A.getNumberOfColumns(); ++j) {
        if (A(step, j) != 0) return false;
    }
    return true;
}

//Checking whether all entries of the next submatrix are divisible by
//the current corner entry
bool isDivisible(IntegerMatrix& A, size_type& jj, size_type step) {
    for (size_type i = step + 1; i < A.getNumberOfRows(); ++i) {
        for (size_type j = step + 1; j < A.getNumberOfColumns(); ++j) {
            if (A(i,j) % A(step, step) != 0) {
                jj = j;
                return false;
            }
        }
    }
    return true;
}

//Making the current column zero except for the corner
void processRows (IntegerMatrix& A, IntegerMatrix& Left, IntegerMatrix& Right,
                  size_type step) {
    for (size_type i = step + 1; i < A.getNumberOfRows(); ++i) {
        integer x1 = A(step, step);
        integer x2 = A(i, step);
        if (x2 != 0) {
            if (x2 % x1 == 0) {
                A.addRowToRow   (i, step, - x2 / x1, step);
                Left.addRowToRow(i, step, - x2 / x1);
            } else {
                Xgcd X(x1, x2);
                A.transformRows   (step, i,
                                   X.factor_1, X.factor_2,
                                 - x2 / X.gcd, x1 / X.gcd, step);
                Left.transformRows(step, i,
                                   X.factor_1, X.factor_2,
                                 - x2 / X.gcd, x1 / X.gcd);
            }
        }
    }
    if (A(step, step) < 0) {
        A(step, step) *= -1;
        Right.multiplyColumn(step, -1);
    }    
}
//Making the current column zero except for the corner
void processColumns(IntegerMatrix& A, IntegerMatrix& Left, IntegerMatrix& Right,
                    size_type step) {
    for (size_type j = step + 1; j < A.getNumberOfColumns(); ++j) {
        integer x1 = A(step, step);
        integer x2 = A(step, j);
        if (x2 != 0) {
            if (x2 % x1 == 0) {
                A.addColumnToColumn    (j, step, -x2 / x1, step);
                Right.addColumnToColumn(j, step, -x2 / x1);
            } else {
                Xgcd X(x1, x2);
                A.transformColumns    (step, j,
                                       X.factor_1,  -x2 / X.gcd,
                                       X.factor_2,   x1 / X.gcd, step);
                Right.transformColumns(step, j,
                                       X.factor_1,  -x2 / X.gcd,
                                       X.factor_2,   x1 / X.gcd);
            }
        }
    }
    if (A(step,step) < 0) {
        A(step, step) *= -1;
        Left.multiplyRow(step, -1);
    }
}