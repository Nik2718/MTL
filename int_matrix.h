#ifndef IntegerMatrix_e415q671_
#define IntegerMatrix_e415q671_

#include <string>
#include <iostream>
#include <vector>
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

    explicit IntegerMatrix(size_type row = 1, size_type col = 1);
    IntegerMatrix(std::vector<std::vector<integer>>& M);
    ~IntegerMatrix();
    IntegerMatrix(const IntegerMatrix& M);

    inline size_type numberOfRows() {return numberOfRows_;}
    inline size_type numberOfColumns() {return numberOfColumns_;}
    inline unsigned int getMaxSize() {
        return std::numeric_limits<size_type>::max();
    }
    inline integer getMaxEntry(){return std::numeric_limits<integer>::max();}
    inline integer getMinEntry(){return std::numeric_limits<integer>::min();}


    //Output
    friend std::ostream& operator<<(std::ostream& os, const IntegerMatrix& M);
    //number of digits in the 10-base system
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

#endif