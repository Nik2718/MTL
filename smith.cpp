#include "int_matrix.h"

int algorithm_step(IntegerMatrix& M, 
                   std::vector<IntegerMatrix::size_type>& row, 
                   std::vector<IntegerMatrix::size_type>& col, 
                   IntegerMatrix::size_type step);

bool isAnyDivisibleByCorner(IntegerMatrix& M, 
                            std::vector<IntegerMatrix::size_type>& row, 
                            std::vector<IntegerMatrix::size_type>& col, 
                            IntegerMatrix::size_type step,
                            IntegerMatrix::size_type& ii,
                            IntegerMatrix::size_type& jj);

void addRowToRow(IntegerMatrix& M, 
                const std::vector<IntegerMatrix::size_type>& row, 
                const std::vector<IntegerMatrix::size_type>& col, 
                IntegerMatrix::size_type step,
                IntegerMatrix::size_type i1,
                IntegerMatrix::size_type i2,
                IntegerMatrix::integer c);

void addColToCol(IntegerMatrix& M, 
                const std::vector<IntegerMatrix::size_type>& row, 
                const std::vector<IntegerMatrix::size_type>& col, 
                IntegerMatrix::size_type step,
                IntegerMatrix::size_type j1,
                IntegerMatrix::size_type j2,
                IntegerMatrix::integer c);


int IntegerMatrix::reduceToSmithForm(){

    std::vector<size_type> row(getNumberOfRows());
    for(size_type i = 0; i < getNumberOfRows(); ++i) row[i] = i;

    std::vector<size_type> col(getNumberOfColumns());
    for(size_type i = 0; i < getNumberOfColumns(); ++i) col[i] = i;

    size_type min_size = std::min(getNumberOfRows(), getNumberOfColumns());    

    int flag;
    for(size_type i = 0; i < min_size; ++i){
        flag == algorithm_step(*this, row, col, min_size, i);
        if(flag < 0){
            throw IntegerMatrix_Exception(
                  "The algorithm of reduction to Smith form failed");
            return flag;
        }
    }
}

bool isAnyDivisibleByCorner(IntegerMatrix& M, 
                            std::vector<IntegerMatrix::size_type>& row, 
                            std::vector<IntegerMatrix::size_type>& col, 
                            IntegerMatrix::size_type step,
                            IntegerMatrix::size_type& ii,
                            IntegerMatrix::size_type& jj){
    
    for(IntegerMatrix::size_type i = step; i < M.getNumberOfRows(); ++i)
    {
        for(IntegerMatrix::size_type j = step; j < M.getNumberOfColumns(); ++i){
            if(M(row[i],col[j]) % M(row[step], row[step]) != 0){
                ii = i;
                jj = j;
                return false;
            }
        }
    }
    return true;
}

// Add the i1-th row  to the i2-th row 
//with the coefficient c
void addRowToRow(IntegerMatrix& M, 
                std::vector<IntegerMatrix::size_type>& row, 
                std::vector<IntegerMatrix::size_type>& col, 
                IntegerMatrix::size_type step,
                IntegerMatrix::size_type& i1,
                IntegerMatrix::size_type& i2,
                IntegerMatrix::integer c){
    for(int j = step; j < M.getNumberOfColumns(); ++j){
        M(row[i2], col[j]) += c * M(row[i1], col[j]);
    }
}

// Add the j1-th column to the j2-th column 
//with the coefficient c
void addColToCol(IntegerMatrix& M, 
                const std::vector<IntegerMatrix::size_type>& row, 
                const std::vector<IntegerMatrix::size_type>& col, 
                IntegerMatrix::size_type step,
                IntegerMatrix::size_type j1,
                IntegerMatrix::size_type j2,
                IntegerMatrix::integer c){
    for(int i = 0; i < M.getNumberOfRows(); ++i){
        M(row[i], col[j2]) += c * M(row[i], row[j1]);
    }
}


int algorithm_step(IntegerMatrix& M, 
                   std::vector<IntegerMatrix::size_type>& row, 
                   std::vector<IntegerMatrix::size_type>& col, 
                   IntegerMatrix::size_type step){
    IntegerMatrix::size_type ii = step, jj = step;
    while (isAnyDivisibleByCorner(M, row, col, step, ii, jj) == false){
        
        
    }

    return 0;
}
