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

BOOST_AUTO_TEST_CASE(test_8){
    try{
        Xgcd X(0,0);
    }
    catch(std::domain_error& E) {
        std::cout << E.what() << std::endl;
        return;
    }
    BOOST_ERROR("GCD of two zeroes was not caught\n");
}

BOOST_AUTO_TEST_CASE(test_9){

    Xgcd X(1,1);
    BOOST_CHECK(X.gcd == 1 && X.factor_1 == 0 && X.factor_2 == 1);

    X = Xgcd(0,5);
    BOOST_CHECK(X.gcd == 5 && X.factor_1 == 0 && X.factor_2 == 1);

    X = Xgcd(0,-7);
    BOOST_CHECK(X.gcd == 7 && X.factor_1 == 0 && X.factor_2 == -1);

    X = Xgcd(5,0);
    BOOST_CHECK(X.gcd == 5 && X.factor_1 == 1 && X.factor_2 == 0);

    X = Xgcd(-8,0);
    BOOST_CHECK(X.gcd == 8 && X.factor_1 == -1 && X.factor_2 == 0);

    X = Xgcd(26,14);
    BOOST_CHECK(X.gcd == 2 && X.factor_1 == -1 && X.factor_2 == 2);

    X = Xgcd(14,26);
    BOOST_CHECK(X.gcd == 2 && X.factor_1 == 2 && X.factor_2 == -1);

    X = Xgcd(-26,14);
    BOOST_CHECK(X.gcd == 2 && X.factor_1 == 1 && X.factor_2 == 2);

    X = Xgcd(39831245440000, 43370127360000);
    BOOST_CHECK(X.gcd == 75295360000 && X.factor_1 == 49 && X.factor_2 == -45);

    X = Xgcd(-21424777101, -1668406194);
    BOOST_CHECK(X.gcd == 20346417 && X.factor_1 == 19 && X.factor_2 == -244);

    X = Xgcd(2760727302559, 3741760723);
    BOOST_CHECK(X.gcd == 1 && X.factor_1 == 880326443 && X.factor_2 == -649518081532);

    X = Xgcd(-324489611, 324670817);
    BOOST_CHECK(X.gcd == 10067 && X.factor_1 == -12542 && X.factor_2 == -12535);

    X = Xgcd((IntegerMatrix::integer)"10633823966279326983230456482242756608",
             (IntegerMatrix::integer)"885443715538058477568");
    BOOST_CHECK(X.gcd == (IntegerMatrix::integer)"295147905179352825856" && 
                X.factor_1 == -1 && 
                X.factor_2 == 12009599006321323);
}

BOOST_AUTO_TEST_CASE(test_10){
    IntegerMatrix A{{1,2,3,4,5},
                    {0,3,5,7,-1}};
    IntegerMatrix B{{1,8,13,18,3},
                    {0,3,5,7,-1}};
    IntegerMatrix C{{1,2,13,18,3},
                    {0,3,5,7,-1}};
    BOOST_CHECK(A.addRowToRow(0,1,2) == B);
    BOOST_CHECK(A.addRowToRow(0,1,-2).addRowToRow(0,1,2,2) == C);
}

BOOST_AUTO_TEST_CASE(test_11){
    IntegerMatrix A{{1,4,-1},
                    {3,4,1}};

    IntegerMatrix B{{1,2,-1},
                    {3,-2,4}};
                    
    BOOST_CHECK(A.addColumnToColumn(1,0,-2).addColumnToColumn(2,0,1,1) == B);
}

BOOST_AUTO_TEST_CASE(test_12){
    IntegerMatrix A{{2,3,-10},
                    {3,4,10}};
    IntegerMatrix B{{2,4,10},
                    {3,3,-10}};
    BOOST_CHECK(A.swapRows(0,1,1) == B);
}

BOOST_AUTO_TEST_CASE(test_13){
    IntegerMatrix A{{2,1,-1},
                    {3,4,2}};
    IntegerMatrix B{{2,1,-1},
                    {3,2,4}};
    BOOST_CHECK(A.swapColumns(1,2,1) == B);
}

BOOST_AUTO_TEST_CASE(test_14) {
    IntegerMatrix A{{3,-6, 1, 3},
                    {4, 8, -1, 2}};
    IntegerMatrix B{{3,-6, 1, 3},
                    {4, -24, 3, -6}};
    BOOST_CHECK(A.multiplyRow(1,-3,1) == B);
}

BOOST_AUTO_TEST_CASE(test_15){
    IntegerMatrix A{{-1,3,6},
                    {5, 8, -1},
                    {9, 4, -2}};
    IntegerMatrix B{{-1,3,6},
                    {5, 8, 2},
                    {9, 4, 4}};
    BOOST_CHECK(A.multiplyColumn(2,-2, 1) == B);   
}

BOOST_AUTO_TEST_CASE(test_16){
    IntegerMatrix A{{0,1,0,-1},
                    {3,4,5,-1},
                    {-1,3,8,2},
                    {1,4,5,6}};
    IntegerMatrix B{{0,1,0,-1},
                    {3,-2,-11,-5},
                    {-1,15,23,-1},
                    {1,4,5,6}};
    BOOST_CHECK(A.transformRows(1, 2,
                                1, -2,
                                3, 1, 
                                1) == B);
}

BOOST_AUTO_TEST_CASE(test_17) {
    IntegerMatrix A{{0,1,0,-1},
                    {3,4,5,-1},
                    {-1,3,8,2},
                    {1,4,5,6}};
    IntegerMatrix B{{0,1,0,-1},
                    {3,4,-20,8},
                    {-1,3,-14,20},
                    {1,4,15,22}};
    BOOST_CHECK(A.transformColumns(2,  3,
                                   -3, 2,
                                   5, 2,
                                   1) == B);
}

BOOST_AUTO_TEST_CASE( test_18 ) {
    IntegerMatrix A{{1, -2, -11},{-2, 11, 43}, {-11, 43, 189}};
    SmithForm S(A);
    std::cout << S.getLeftMatrix();
    std::cout << S.getRightMatrix();
    std::cout << S.getLeftMatrix() * A * S.getRightMatrix();
}