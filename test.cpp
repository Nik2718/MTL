#include "int_matrix.h"

#define BOOST_TEST_MODULE Tests
#include  <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( test_1 ){
    try{
        IntegerMatrix A(0,1);
    }
    catch(IntegerMatrix_Exception &E){
        std::cout << E.what() << '\n';
        return;
    }
    BOOST_ERROR("Zero number of rows was not found\n");
}

BOOST_AUTO_TEST_CASE( test_2 ){
    try{
        IntegerMatrix A(1,0);
    }
    catch(IntegerMatrix_Exception &E){
        std::cout << E.what() << '\n';
        return;
    }
    BOOST_ERROR("Zero number of columns was not found\n");
}

BOOST_AUTO_TEST_CASE( test_3 )
{
    IntegerMatrix A{{1, 2, -34},
                    {-32, 1, 3}};
    std::vector<std::vector<int>> V{{1, 2, -34},
                                    {-32, 1, 3}};
    std::cout << A;
    BOOST_CHECK(A.getNumberOfRows() == 2);
    BOOST_CHECK(A.getNumberOfColumns() == 3);
    for(int i = 0; i < 2; ++i){
        for(int j = 0; j < 3; ++j){
            BOOST_CHECK(A(i,j) == V[i][j]);
        }
    }
}