CXX = clang++
BOOST_PATH = -I/opt/homebrew/Cellar/boost/1.84.0_1/include
TEST_LIB = /opt/homebrew/Cellar/boost/1.84.0_1/lib/libboost_unit_test_framework.a
PWD = /Users/nick/Documents/GitHub/MTL
CXXFLAGS = -c -std=c++17 -Wall -Werror -Wextra -pedantic -O2

SRC_DIR = $(PWD)/src
BUILD_DIR = $(PWD)/build
OUT_DIR = $(PWD)/lib

_OUT = libint_matrix.a
OUT = $(OUT_DIR)/$(_OUT)

_OBJ_OUT = int_matrix.o xgcd.o algorithm.o
_OBJ_TEST = test.o
_OBJ_EXAMPLE = example.o

OBJ_OUT = $(patsubst %, $(BUILD_DIR)/%, $(_OBJ_OUT))
OBJ_TEST = $(BUILD_DIR)/$(_OBJ_TEST)
OBJ_EXAMPLE = $(BUILD_DIR)/$(_OBJ_EXAMPLE)


all: lib test example

lib: $(OUT)
$(OUT): $(OBJ_OUT) | $(OUT_DIR) 
	ar rcs $(OUT) $^
$(OBJ_OUT): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(BOOST_PATH) $< -o $@
$(OUT_DIR):
	mkdir -p $(OUT_DIR)
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

test: $(OBJ_TEST) $(OUT)
	$(CXX) $^ -o test $(OUT) $(TEST_LIB)
$(OBJ_TEST): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(BOOST_PATH) $< -o $@

example: $(OBJ_EXAMPLE) $(OUT)
	$(CXX) $^ -o example $(OUT)
$(OBJ_EXAMPLE): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(BOOST_PATH) $< -o $@


.PHONY: clean

clean:
	rm -f $(BUILD_DIR)/*.o test example $(OUT)
