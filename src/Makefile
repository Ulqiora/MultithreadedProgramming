CC=g++
BD=../build
CXX_FLAGS=-c #-Wall -Werror -Wextra -Wfloat-equal -Warray-bounds -std=c++17
LCOVFLAGS=-fprofile-arcs -ftest-coverage
GTESTFLAGS=-lgtest

.PHONY: winograd

ifeq ($(shell uname -s), Linux)
	GTESTFLAGS+= -lpthread -lrt
endif
###      Winograd Algorithm
##       Model and View 
WINOGRAD_SOURCES= main_winograd.cpp Matrix.cpp WinogradAlgorithm.cpp WinogradView.cpp
WINOGRAD_OBJECTS=$(addprefix $(BD)/,$(WINOGRAD_SOURCES:.cpp=.o))
##       Tests
WINOGRAD_SOURCES= main_winograd.cpp Matrix.cpp WinogradAlgorithm.cpp WinogradView.cpp
WINOGRAD_OBJECTS=$(addprefix $(BD)/,$(WINOGRAD_SOURCES:.cpp=.o))
###      Ant Algorithm
##       Model and View 
ANT_SOURCES= main_debug.cpp SquareMatrix.cpp graph.cpp Ant.cpp AntAlgorithm.cpp 
ANT_OBJECTS=$(addprefix $(BD)/,$(ANT_SOURCES:.cpp=.o))
##       Tests
ANT_SOURCES= main_debug.cpp Matrix.cpp ANTAlgorithm.cpp ANTView.cpp
ANT_OBJECTS=$(addprefix $(BD)/,$(ANT_SOURCES:.cpp=.o))
#              Файлы для тестов
# TESTS_FILES_SOURCES=main_test.cpp Matrix.cpp graph.cpp GraphAlgorithms.cpp MatrixBnB.cpp Ant.cpp AntAlgorithm.cpp ConsoleView.cpp
# TESTS_FILES_OBJECTS=$(addprefix $(BD)/,$(TESTS_FILES_SOURCES:.cpp=.o))


winograd:clean $(WINOGRAD_OBJECTS)
	$(CC) -g  $(WINOGRAD_OBJECTS) -o $(BD)/$@  -lpthread
	./$(BD)/$@



./$(BD)/%.o:%.cpp
	$(CC) $(CXX_FLAGS) $< -o $@

./$(BD)/%.o:*/%.cpp
	$(CC) $(CXX_FLAGS) $< -o $@
 
./$(BD)/%.o: */*/%.cpp
	$(CC) $(CXX_FLAGS) $< -o $@

./$(BD)/%.o: */*/*/%.cpp
	$(CC) $(CXX_FLAGS) $< -o $@

clean:
	rm -rf $(BD)/*.*
	rm -rf $(BD)/*
	