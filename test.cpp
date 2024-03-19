#include "int_matrix.h"

int main()
{
    std::vector<std::vector<IntegerMatrix::integer>> V{{121},{1}};
    IntegerMatrix A(V);

    std::cout << A;
}