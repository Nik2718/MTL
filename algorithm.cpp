#include "int_matrix.h"

using size_type = IntegerMatrix::size_type;
using integer = IntegerMatrix::integer;

enum class State{End, Continue};
State algorithmStep(IntegerMatrix& A, IntegerMatrix& Left, IntegerMatrix& Right,
                    size_type step);
void processRows   (IntegerMatrix& A, IntegerMatrix& Left, IntegerMatrix& Right,
                    size_type step);
void processColumns(IntegerMatrix& A, IntegerMatrix& Left, IntegerMatrix& Right,
                    size_type step);

SmithForm::SmithForm(IntegerMatrix A) {
    if(A.getNumberOfRows() == 1 && A.getNumberOfColumns() == 1) {
        isCorrect_ = true;
        minSize_ = 1;
        InvariantFactors_ = std::vector<integer> (1, A(0,0));
        Left_ = IntegerMatrix(1,1,1);
        Right_ = IntegerMatrix(1,1,1);
        return;
    }

    minSize_ =      std::min(A.getNumberOfRows(),    A.getNumberOfColumns());
    Left_    = IntegerMatrix(A.getNumberOfRows(),    A.getNumberOfRows(), 0);
    Right_   = IntegerMatrix(A.getNumberOfColumns(), A.getNumberOfColumns(), 0);
    for(size_type i = 0; i < A.getNumberOfRows(); ++i) {
        Left_(i,i) = 1;
    }
    for(size_type i = 0; i < A.getNumberOfColumns(); ++i) {
        Right_(i,i) = 1;
    }

    State S = State::Continue;
    try{
        for(size_type step = 0; step < minSize_ && 
                                S == State::Continue; ++step) {
            S = algorithmStep(A, Left_, Right_, step);
        }
    }
    catch(std::overflow_error) {
        isCorrect_ = false;
        InvariantFactors_ = std::vector<integer> (1, 0);
        Left_ = IntegerMatrix(1,1,1);
        Right_ = IntegerMatrix(1,1,1);        
        return;
    }
    InvariantFactors_ = std::vector<integer> (minSize_, 0);
    for(size_type i = 0; i < minSize_; ++i) InvariantFactors_[i] = A(i,i);

    //std::cout << A;
}

State algorithmStep(IntegerMatrix& A, IntegerMatrix& Left, IntegerMatrix& Right,
                   size_type step) {
    if(A(step, step) == 0) {
        bool isSubmatrixZero = true;
        for(size_type i = step; 
                      i < A.getNumberOfRows() && isSubmatrixZero; ++i) {
            for(size_type j = step; 
                          j < A.getNumberOfColumns() && isSubmatrixZero; ++j) {
                if(A(i,j) != 0) {
                    A.swapRows(step, i, step);
                    A.swapColumns(step, j, step);
                    isSubmatrixZero = false;
                }
            }
        }
        if(isSubmatrixZero == true) return State::End;
    }
    processRows   (A, Left, Right, step);
    processColumns(A, Left, Right, step);
    return State::Continue;
}

void processRows (IntegerMatrix& A, IntegerMatrix& Left, IntegerMatrix& Right,
                  size_type step) {
    for(size_type i = step + 1; i < A.getNumberOfRows(); ++i) {
        integer x1 = A(step, step);
        integer x2 = A(i, step);
        if(x2 != 0) {
            if(x2 % x1 == 0) {
                A.addRowToRow   (i, step, - x2 / x1, step);
                Left.addRowToRow(i, step, - x2 / x1);
            }
            else {
                Xgcd X(x1, x2);
                A.transformRows   (step, i,
                                   X.factor_1,   X.factor_2,
                                   - x2 / X.gcd, x1 / X.gcd, step);
                Left.transformRows(step, i,
                                   X.factor_1,   X.factor_2,
                                   - x2 / X.gcd, x1 / X.gcd);            
            }
        }
    }
    if(A(step, step) < 0) {
        A(step, step) *= -1;
        Right.multiplyColumn(step, -1);
    }    
}

void processColumns(IntegerMatrix& A, IntegerMatrix& Left, IntegerMatrix& Right,
                    size_type step) {
    for(size_type j = step + 1; j < A.getNumberOfColumns(); ++j) {
        integer x1 = A(step, step);
        integer x2 = A(step, j);
        if(x2 != 0) {
            if(x2 % x1 == 0) {
                A.addColumnToColumn    (j, step, -x2 / x1, step);
                Right.addColumnToColumn(j, step, -x2 / x1);
            }
            else {
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
    if(A(step,step) < 0) {
        A(step, step) *= -1;
        Left.multiplyRow(step, -1);
    }
}