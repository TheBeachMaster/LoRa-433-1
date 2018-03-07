SRC_PATH=./test
OUT_PATH=./bin
UTILS_DIR=./utils
TEST_SRC=$(wildcard ${SRC_PATH}/test_*.cc)
TEST_BIN=$(TEST_SRC:${SRC_PATH}/%.cc=${OUT_PATH}/%)
VPATH=${SRC_PATH}
SHIM_FILES=${UTILS_DIR}/*.cpp
LIB_FILE=./lib/libmath.cc
CXX=g++
CFLAGS=-I${UTILS_DIR} -I./lib
CXXFLAGS=-Wall -Wextra -pedantic-errors -std=c++0x -g -O0

all: $(TEST_BIN)

${OUT_PATH}/%: ${SRC_PATH}/%.cc ${LIB_FILE} ${SHIM_FILES}
	mkdir -p ${OUT_PATH}
	${CXX} ${CXXFLAGS} ${CFLAGS} $^ -o $@

clean:
	@rm -rf ${OUT_PATH}

test: 
	cd ./bin/
	./test_*
