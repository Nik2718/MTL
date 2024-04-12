//A short example

#include "../include/int_matrix.hpp"
#include <iostream>


int main(){

    std::cout << '\n';
    std::cout << "**********************************************" << '\n';
    std::cout << "This is is an example of work with the library" << '\n';
    std::cout << "**********************************************" << "\n\n";

    IntegerMatrix A{{-2, 4, -2, -16, -8, -6},
                    {-2, 10, 4, 14, -8, 0},
                    {2, -4, 44, 16, 92, 90},
                    {0, 6, 6, 114, -1, 90}};

    std::cout << "Let's consider an integer matrix A equal to " << A << '\n';

    SmithForm S(A);

    std::cout << "The invariant factors of the matrix A are ";
    for (IntegerMatrix::size_type i = 0; i < S.getMinSize(); ++i) {
        std::cout << S.getInvariantFactor(i) << ' ';
    }
    std::cout << "\n\n";

    std::cout << "The left transformation matrix L is " << 
                                      S.getLeftMatrix() << '\n';
    std::cout << "The right transformation matrix R is " << 
                                      S.getRightMatrix() << '\n';

    std::cout << "The product L * A * R equals to " <<
                "the diagonal matrix of the invariant factors" <<
                S.getLeftMatrix() * A * S.getRightMatrix() << "\n";
}