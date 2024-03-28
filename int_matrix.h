#ifndef IntegerMatrix_e415q671_
#define IntegerMatrix_e415q671_

#include <string>
#include <iostream>
#include <vector>
#include <initializer_list>
#include <boost/multiprecision/cpp_int.hpp>

class IntegerMatrix;
class IntegerMatrix_Exception;
class SmithForm;

class IntegerMatrix {

    public:

    typedef unsigned int size_type; 
    typedef boost::multiprecision::checked_int256_t integer;

    private:

    size_type numberOfColumns_;
    size_type numberOfRows_;

    protected:

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
    // Left * Diagonal Matrix of Invariant Factors * Right == A

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
    inline const std::vector<
    IntegerMatrix::integer>& getInvariantFactors() const noexcept{
        return InvariantFactors_;
    }
};


#endif