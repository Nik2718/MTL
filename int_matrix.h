#ifndef IntegerMatrix_e415q671_
#define IntegerMatrix_e415q671_

#include <string>
#include <iostream>
#include <vector>
#include <initializer_list>
#include <boost/multiprecision/cpp_int.hpp>

class IntegerMatrix {
    public:

    typedef unsigned int size_type; 
    typedef boost::multiprecision::checked_int256_t integer;

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
    inline size_type getNumberOfRows() const noexcept {return numberOfRows_;}
    inline size_type getNumberOfColumns() const noexcept{
        return numberOfColumns_;
    }
    integer& operator()(size_type i, size_type j){return Matrix_[i][j];}

    //Limits
    inline static unsigned int getMaxSize(){
        return std::numeric_limits<size_type>::max();
    }
    inline static integer getMaxEntry(){
                          return std::numeric_limits<integer>::max();
    }  
    inline static integer getMinEntry(){
                          return std::numeric_limits<integer>::min();
    }

    //Comparison
    bool operator==(const IntegerMatrix& A) const noexcept;

    //Arithmetic
    IntegerMatrix& operator+=(const IntegerMatrix & A);
    friend IntegerMatrix operator+(IntegerMatrix A, const IntegerMatrix& B);
    IntegerMatrix& operator*=(const IntegerMatrix & A);
    friend IntegerMatrix operator*(IntegerMatrix A, const IntegerMatrix& B);

    //Output
    friend std::ostream& operator<<(std::ostream& os, const IntegerMatrix& M);
 
    //Auxiliary functions
    static unsigned int number_length10(integer a);
    //number of digits in the 10-base system (sign will be took into account)
};

struct SmithForm{
    bool isCorrect;//whether data are correct
    std::vector<IntegerMatrix::integer> InvariantFactors;
    IntegerMatrix Left; //matrix of left transformaion
    IntegerMatrix Right; //matrix of right transformaion

    SmithForm(IntegerMatrix::size_type numberOfRows = 1,
              IntegerMatrix::size_type numberOfColumns = 1):
        isCorrect{false}, 
        InvariantFactors{std::vector<IntegerMatrix::integer>(
                         std::min(numberOfRows, numberOfColumns), 0)},
        Left{IntegerMatrix(numberOfRows, numberOfRows, 0)},
        Right{IntegerMatrix(numberOfColumns, numberOfColumns, 0)} {
            for(IntegerMatrix::size_type i = 0; i < numberOfRows; ++i){
                Left(i,i) = 1;
            }
            for(IntegerMatrix::size_type j = 0; j < numberOfColumns; ++j){
                Right(j,j) = 1;
            }
            //Left and Right are initialized as the identity matrices
        }
};

//Reduction to Smith normal form
// Left * Diagonal Matrix of Invariant Factors * Right == A
SmithForm findSmithForm(IntegerMatrix A);

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

#endif