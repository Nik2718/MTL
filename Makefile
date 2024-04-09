CXX = clang++
BOOST_PATH = -I/opt/homebrew/Cellar/boost/1.84.0_1/include
TEST_LIB = /opt/homebrew/Cellar/boost/1.84.0_1/lib/libboost_unit_test_framework.a
CXXFLAGS = -c -std=c++17 -Wall -Werror -Wextra -pedantic -O2

SRC_DIR = ./src
BUILD_DIR = ./build
OUT_DIR = ./lib

_OUT = libint_matrix.a
OUT = $(OUT_DIR)/$(_OUT)

_OBJ_OUT = int_matrix.o xgcd.o algorithm.o
_OBJ_TEST = test.o
_OBJ_EXAMPLE = example.o

OBJ_OUT = $(patsubst %, $(BUILD_DIR)/%, $(_OBJ_OUT))
OBJ_TEST = $(BUILD_DIR)/$(_OBJ_TEST)
OBJ_EXAMPLE = $(BUILD_DIR)/$(_OBJ_EXAMPLE)


all: lib test example

lib: $(OBJ_OUT)
	ar rcs $(OUT) $^
$(OBJ_OUT): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(BOOST_PATH) $< -o $@

test: $(OBJ_TEST)
	$(CXX) $^ -o test $(OUT) $(TEST_LIB)
$(OBJ_TEST): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(BOOST_PATH) $< -o $@

example: $(OBJ_EXAMPLE)
	$(CXX) $^ -o example $(OUT)
$(OBJ_EXAMPLE): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(BOOST_PATH) $< -o $@


.PHONY: clean

clean:
	rm -f $(BUILD_DIR)/*.o test example $(OUT)
