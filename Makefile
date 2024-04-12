#Makefile of the project

#C++ compiler
CXX := clang++
#A path to boost headers
BOOST_PATH := -I/opt/homebrew/Cellar/boost/1.84.0_1/include
#A path to libboost_unit_test_framework.a
TEST_LIB := \
/opt/homebrew/Cellar/boost/1.84.0_1/lib/libboost_unit_test_framework.a
#The compilation flags
CXXFLAGS := -c -std=c++17 -Wall -Werror -Wextra -pedantic -O2

#A path to the directory with *.cpp files
SRC_DIR := $(shell pwd)/src
#A path to the directory with *.o files
BUILD_DIR := $(shell pwd)/build
#A path to the directory where the created static library will be saved
OUT_DIR := $(shell pwd)/lib

#A path to the created static library
_OUT := libint_matrix.a
OUT := ${OUT_DIR}/${_OUT}

#Object files
_OBJ_OUT := int_matrix.o xgcd.o algorithm.o
_OBJ_TEST := test.o
_OBJ_EXAMPLE := example.o

#Paths to the object files
OBJ_OUT := ${patsubst %, ${BUILD_DIR}/%, ${_OBJ_OUT}}
OBJ_TEST := ${BUILD_DIR}/${_OBJ_TEST}
OBJ_EXAMPLE := ${BUILD_DIR}/${_OBJ_EXAMPLE}


all: dir lib test example

#Creating directories
dir: ${OUT_DIR} ${BUILD_DIR}
${OUT_DIR}:
	mkdir -p ${OUT_DIR}
${BUILD_DIR}:
	mkdir -p ${BUILD_DIR}

#Creating the static liabrary libint_matrix.a
lib: ${OBJ_OUT} 
	ar rcs ${OUT} $^
${OBJ_OUT}: ${BUILD_DIR}/%.o: ${SRC_DIR}/%.cpp | dir
	${CXX} ${CXXFLAGS} ${BOOST_PATH} $< -o $@

#Creating tests
test: ${OBJ_TEST} lib
	${CXX} $< -o test ${OUT} ${TEST_LIB}
${OBJ_TEST}: ${BUILD_DIR}/%.o: ${SRC_DIR}/%.cpp | dir
	${CXX} ${CXXFLAGS} ${BOOST_PATH} $< -o $@

#Creating an example
example: ${OBJ_EXAMPLE} lib
	${CXX} $< -o example ${OUT}
${OBJ_EXAMPLE}: ${BUILD_DIR}/%.o: ${SRC_DIR}/%.cpp | dir
	${CXX} ${CXXFLAGS} ${BOOST_PATH} $< -o $@

#Сleaning up the project
.PHONY: clean
clean:
	rm -r ${BUILD_DIR} ${OUT_DIR} test example
