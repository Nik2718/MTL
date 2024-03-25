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
    IntegerMatrix(size_type row = 1, size_type col = 1);
    IntegerMatrix(const std::vector<std::vector<integer>>& M);
    IntegerMatrix(const std::initializer_list<
                        std::initializer_list<integer>>& M);
    ~IntegerMatrix();

    //Copying
    IntegerMatrix(const IntegerMatrix& M);
    IntegerMatrix& operator=(const IntegerMatrix& M);
    IntegerMatrix::IntegerMatrix(IntegerMatrix&& M);

    //Access
    inline size_type getNumberOfRows() {return numberOfRows_;}
    inline size_type getNumberOfColumns() {return numberOfColumns_;}
    integer& operator()(size_type i, size_type j){return Matrix_[i][j];}

    //Limits
    inline static unsigned int getMaxSize() {
        return std::numeric_limits<size_type>::max();
    }
    inline static integer getMaxEntry(){
                          return std::numeric_limits<integer>::max();
    }  
    inline static integer getMinEntry(){
                          return std::numeric_limits<integer>::min();
    }

    //Comparison
    bool operator==(const IntegerMatrix& A) const;

    //Arithmetic


    int reduceToSmithForm();

    //Output
    friend std::ostream& operator<<(std::ostream& os, const IntegerMatrix& M);
    //number of digits in the 10-base system (sign will be took into account)
    static unsigned int number_length10(integer a);
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

std::vector<IntegerMatrix::integer> findSmithNormalForm(const IntegerMatrix& A);

#endif