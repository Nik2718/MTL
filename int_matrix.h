#ifndef IntegerMatrix_e415q671_
#define IntegerMatrix_e415q671_

#include <string>
#include <iostream>
#include <vector>
#include <stack>
#include <initializer_list>
#include <stdexcept>
#include <boost/multiprecision/cpp_int.hpp>

class IntegerMatrix;
class IntegerMatrix_Exception;
class SmithForm;
class Xgcd;

class IntegerMatrix {

    public:

    typedef unsigned int size_type; 
    typedef boost::multiprecision::cpp_int integer;

    private:

    size_type numberOfColumns_;
    size_type numberOfRows_;
    integer **Matrix_;

    public:

    //Constructors and destructor
    IntegerMatrix(size_type row = 1, size_type col = 1, integer entry = 0);
    IntegerMatrix(const std::vector<std::vector<integer>>& M);
    IntegerMatrix(const std::initializer_list<
                        std::initializer_list<integer>>& M);
    IntegerMatrix(const IntegerMatrix& M);
    IntegerMatrix(IntegerMatrix&& M) noexcept;
    ~IntegerMatrix() noexcept;

    //Assignment
    IntegerMatrix& operator=(const IntegerMatrix& M);
    IntegerMatrix& operator=(IntegerMatrix&& M) noexcept;

    //Access
    inline size_type getNumberOfRows()    const noexcept {
        return numberOfRows_;
    }
    inline size_type getNumberOfColumns() const noexcept{
        return numberOfColumns_;
    }
    inline integer& operator()(size_type i, size_type j){return Matrix_[i][j];}

    //Limits
    inline static unsigned int getMaxSize(){return 10000;}

    //Comparison
    bool operator==(const IntegerMatrix& A) const noexcept;

    //Arithmetic
    IntegerMatrix& operator+=(const IntegerMatrix & A);
    friend IntegerMatrix operator+(IntegerMatrix A, const IntegerMatrix& B);
    IntegerMatrix& operator*=(const IntegerMatrix & A);
    friend IntegerMatrix operator*(IntegerMatrix A, const IntegerMatrix& B);



    //Manipulation of rows and columns

    //row i1  is changed to (row i1 + c * row i2) 
    //from the position "begin"
    IntegerMatrix& addRowToRow(size_type i1, size_type i2, integer c, 
                     size_type begin = 0);

    //column j1  is changed to (column j1 + c * column i2) 
    //from the position "begin"
    IntegerMatrix& addColumnToColumn(size_type j1, size_type j2, integer c, 
                           size_type begin = 0);
    
    //columns(rows) are swapped from the position "begin"
    IntegerMatrix& swapRows   (size_type i1, size_type i2, size_type begin = 0);
    IntegerMatrix& swapColumns(size_type j1, size_type j2, size_type begin = 0);

    //columns(rows) are multiplied by "c" from the position "begin"
    IntegerMatrix& multiplyRow   (size_type i, integer c, size_type begin = 0);
    IntegerMatrix& multiplyColumn(size_type j, integer c, size_type begin = 0);

    //Multiply two rows by 2 x 2 matrix on the left
    IntegerMatrix& transformRows  (size_type i1, size_type i2,
                                   integer a11,  integer a12,
                                   integer a21,  integer a22, 
                                   size_type begin = 0);

    //Multiply two columns by 2 x 2 matrix on the right
    IntegerMatrix& transformColumns(size_type j1, size_type j2,
                                    integer a11,  integer a12,
                                    integer a21,  integer a22, 
                                    size_type begin = 0);

    //Output
    friend std::ostream& operator<<(std::ostream& os, const IntegerMatrix& M);
 
    //Auxiliary functions
    static unsigned int number_length10(integer a);
    //number of digits in the 10-base system (sign will be took into account)
};

class IntegerMatrix_Exception: public std::exception {
    public:

    explicit IntegerMatrix_Exception(const std::string& message): 
                                             message_{message} {}

    const char* what() const noexcept {
        return message_.c_str();
    }

    private:

    std::string message_;

};

class SmithForm{

    private:

    bool isCorrect_;//whether data are correct
    IntegerMatrix::size_type minSize_; 
    //Minimum of sizes of square matrices Left_ and Right_
    std::vector<IntegerMatrix::integer> InvariantFactors_;
    IntegerMatrix Left_; //matrix of left transformaion
    IntegerMatrix Right_; //matrix of right transformaion

    public:

    SmithForm(IntegerMatrix A);
    // Left * A * Right == Diagonal Matrix of Invariant Factors

    inline bool isCorrect() const noexcept {return isCorrect_;}
    inline IntegerMatrix::size_type getMinSize() const noexcept{
        return minSize_;
    }
    inline const IntegerMatrix& getLeftMatrix() const noexcept{
        return Left_;
    }
    inline const IntegerMatrix& getRightMatrix() const noexcept{
        return Right_;
    }
    inline const IntegerMatrix::integer 
        getInvariantFactor(IntegerMatrix::size_type i) const noexcept{
        return InvariantFactors_.at(i);
    }
};

//The greatest common divisor and related quantities
struct Xgcd {
    //initial numbers
    IntegerMatrix::integer number_1, number_2;

    //the greatest common divisor of number_1, number_2
    IntegerMatrix::integer gcd;

    //Bezout's coefficients
    // factor_1 * number_1 + factor_2 * number_2 = gcd
    IntegerMatrix::integer factor_1, factor_2;

    Xgcd(IntegerMatrix::integer x1, IntegerMatrix::integer x2);
    //if x1 == 0 and x2 == 0 the constructor set gcd = 0 and
    //throws std::domain_error
};

#endif