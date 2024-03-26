#include "int_matrix.h"

using size_type = IntegerMatrix::size_type;
using integer = IntegerMatrix::integer;

struct Data{
    IntegerMatrix M;
    std::vector<size_type> row;
    std::vector<size_type> col;
    //The i,j-entry of the matrix M is M(row[i], col[j])
    //This construction is necessary for faster swap 
    //of two rows (or two columns) 

    size_type minSize; //Minimum of numbers of rows and columns
    size_type step; //The number of a step of the algorithm
    size_type ii; //The row number under consideration
    size_type jj; //The column number under consideration

    Data(IntegerMatrix&& A): 
        M{A}, //the matrix is moved in the struct
        row{std::vector<size_type>(A.getNumberOfRows(), 0)},
        col{std::vector<size_type>(A.getNumberOfColumns(), 0)},
        minSize{std::min(A.getNumberOfRows(), A.getNumberOfColumns())},
        step{0}, ii{0}, jj{0} {
            for(size_type i = 0; i < A.getNumberOfRows(); ++i) row[i] = i;
            for(size_type j = 0; j < A.getNumberOfColumns(); ++j) col[j] = j;
        }
};


void algorithmStep(Data& D, SmithForm& SF);

bool isNextSquareDivisibleByCorner(Data& D);
bool isCurrentRowDivisibleByCorner(Data& D);
bool isCurrentColumnDivisibleByCorner(Data& D);

void addRowToRow      (Data& D, SmithForm& SF, 
                       size_type i1, size_type i2, integer c);
void addColumnToColumn(Data& D, SmithForm& SF, 
                       size_type j1, size_type j2, integer c);

void swapRows   (Data& D, SmithForm& SF, size_type i1, size_type i2);
void swapColumns(Data& D, SmithForm& SF, size_type j1, size_type j2);


SmithForm findSmithForm(IntegerMatrix A){

    SmithForm SF(A.getNumberOfRows(), A.getNumberOfColumns());
    Data D(std::move(A));

    try{
        for(D.step = 0; D.step < D.minSize; ++D.step){
                algorithmStep(D, SF);
            }
    }
    catch(std::overflow_error& E){
        SF.isCorrect = false;
        std::cerr << E.what() << std::endl;
        return SF;
    }
    for(size_type i = 0; i < D.minSize; ++i){
        SF.InvariantFactors[i] = A(i,i);
    }
    SF.isCorrect = true;
    return SF;
}
