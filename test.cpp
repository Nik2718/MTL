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
        std::cout << E.what() << std::endl;
        return;
    }
    BOOST_ERROR("Zero number of columns was not found\n");
}

BOOST_AUTO_TEST_CASE( test_3 ) {
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

BOOST_AUTO_TEST_CASE( test_4 ){
    try{
        IntegerMatrix A{{IntegerMatrix::getMaxEntry()+1}};
    }
    catch(std::overflow_error const& E){
        std::cout << E.what() << std::endl;
        return;
    }
    BOOST_ERROR("A too large entry was not detected\n");
}

BOOST_AUTO_TEST_CASE( test_5 ){
    try{
        IntegerMatrix A{{IntegerMatrix::getMinEntry()-1}};
    }
    catch(std::overflow_error const& E){
        std::cout << E.what() << std::endl;
        return;
    }
    BOOST_ERROR("A too small negative entry was not detected\n");
}

BOOST_AUTO_TEST_CASE( test_6 ){
    BOOST_CHECK(IntegerMatrix::number_length10(0) == 1);
    BOOST_CHECK(IntegerMatrix::number_length10(-1) == 2);
    BOOST_CHECK(IntegerMatrix::number_length10(999999) == 6);
    BOOST_CHECK(IntegerMatrix::number_length10(-999999) == 7);
    BOOST_CHECK(IntegerMatrix::number_length10(1000000) == 7);     
    BOOST_CHECK(IntegerMatrix::number_length10(IntegerMatrix::getMaxEntry()) == 
                        std::string{IntegerMatrix::getMaxEntry().str()}.size());
    BOOST_CHECK(IntegerMatrix::number_length10(IntegerMatrix::getMinEntry()) == 
                        std::string{IntegerMatrix::getMinEntry().str()}.size());
}

BOOST_AUTO_TEST_CASE( test_7 ) {
    IntegerMatrix A{{1, 2, -4, 222, 1, 444, 1},
                    {2, 3, -25, 333, 19, 2, 4}};
    
    std::vector<std::vector<IntegerMatrix::integer>> V{
                                    {1, 2, -4, 222, 1, 444, 1},
                                    {2, 3, -25, 333, 19, 2, 4}};
    IntegerMatrix B(V);

    BOOST_CHECK(A == B);
    std::cout << A;
}