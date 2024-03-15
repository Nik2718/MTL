#ifndef IntegerMatrix_e415q671_
#define IntegerMatrix_e415q671_

#include <string>
#include <iostream>
#include <vector>
#include <boost/multiprecision/cpp_int.hpp>


class IntegerMatrix {
    typedef unsigned int size_type; 

    private:

    size_type numberOfColumns_;
    size_type numberOfRows_;
    boost::multiprecision::checked_int256_t **Matrix_;

    public:

    const unsigned int MAXIMUM_LINEAR_SIZE = std::numeric_limits<size_type>::max();
    const boost::multiprecision::checked_int256_t MAXIM_ENTRY = std::numeric_limits<
                                          boost::multiprecision::checked_int256_t>::max();
    const boost::multiprecision::checked_int256_t MINIMUM_ENTRY = std::numeric_limits<
                                          boost::multiprecision::checked_int256_t>::min();

    explicit IntegerMatrix(size_type row, size_type col);
    IntegerMatrix(std::vector<std::vector<boost::multiprecision::checked_int256_t>>& M);
    ~IntegerMatrix();
    IntegerMatrix(const IntegerMatrix& M);

    inline size_type numberOfRows() {return numberOfRows_;}
    inline size_type numberOfColumns() {return numberOfColumns_;}

    friend std::ostream& operator<<(std::ostream& os, const IntegerMatrix& M);
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