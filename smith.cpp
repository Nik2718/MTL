#include "int_matrix.h"

using size_type = IntegerMatrix::size_type;
using integer = IntegerMatrix::integer;

struct Data{
    IntegerMatrix M;

    IntegerMatrix Left; //matrix of left transformaion
    IntegerMatrix Right; //matrix of right transformaion

    size_type minSize;
    size_type step; //The number of a step of the algorithm
    size_type i; //The row number under consideration
    size_type j; //The column number under consideration

    Data(IntegerMatrix&& A): 
        M{A}, //the matrix is moved in the struct

        Left{IntegerMatrix(A.getNumberOfRows(), A.getNumberOfRows(), 0)},
        Right{IntegerMatrix(A.getNumberOfColumns(), A.getNumberOfColumns(), 0)},

        minSize{std::min(A.getNumberOfRows(), A.getNumberOfColumns())},
        step{0}, i{0}, j{0} {
            for(size_type i = 0; i < A.getNumberOfRows(); ++i) {
                Left(i,i) = 1;
            }
            for(size_type j = 0; j < A.getNumberOfColumns(); ++j) {
                Right(j,j) = 1;
            }
        }
//Left and Right are initialized as identity matrices
};


void algorithmStep(Data& D);

bool isNextSquareDivisibleByCorner(Data& D);
bool isCurrentRowDivisibleByCorner(Data& D);
bool isCurrentColumnDivisibleByCorner(Data& D);

void addRowToRow      (Data& D, size_type i1, size_type i2, integer c);
void addColumnToColumn(Data& D, size_type j1, size_type j2, integer c);

void swapRows   (Data& D, size_type i1, size_type i2);
void swapColumns(Data& D, size_type j1, size_type j2);



SmithForm::SmithForm(IntegerMatrix A) {

    Data D(std::move(A));

    try{
        for(D.step = 0; D.step < D.minSize; ++D.step) algorithmStep(D);
    }
    catch(std::overflow_error& E){
        isCorrect_ = false;
        minSize_ = D.minSize;
        InvariantFactors_ = std::vector<IntegerMatrix::integer>(1,0);
        Left_ = IntegerMatrix(1,1,0);
        Right_ = IntegerMatrix(1,1,0);
        std::cerr << E.what() << std::endl;
        return;
    }

    isCorrect_ = true;
    minSize_ = D.minSize;

    InvariantFactors_ = std::vector<IntegerMatrix::integer>(D.minSize, 0);
    for(size_type i = 0; i < D.minSize; ++i){
        InvariantFactors_[i] = D.M(i,i);
    }

    Left_ = std::move(D.Left);
    Right_ = std::move(D.Right);
}

void algorithmStep(Data& D){
    while(isCurrentRowDivisibleByCorner(D) == false){
        
    }
}
