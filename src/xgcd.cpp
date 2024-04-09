#include "../include/int_matrix.h"

using integer = IntegerMatrix::integer;

Xgcd::Xgcd(integer x1, integer x2): number_1{x1}, number_2{x2} {
    if(x1 == 0 && x2 == 0){
        throw std::domain_error("GCD of two zeroes is undefined");
        gcd = 0;
        factor_1 = 0;
        factor_2 = 0;
        return;
    }

    //Extended Euclidean algorithm
    integer factor_1_previous = 1, factor_2_previous = 0;
    factor_1 = 0;
    factor_2 = 1;

    integer quotient;
    while(x2) {
        quotient = x1/x2;

        factor_1_previous = factor_1_previous - quotient * factor_1;
        std::swap(factor_1_previous, factor_1);

        factor_2_previous = factor_2_previous - quotient * factor_2;
        std::swap(factor_2_previous, factor_2);

        x1 = x1 % x2;
        std::swap(x1, x2);
    }
    gcd = x1;
    factor_1 = factor_1_previous;
    factor_2 = factor_2_previous;

    if(gcd < 0){
        gcd *= -1;
        factor_1 *= -1;
        factor_2 *= -1;
    }

}