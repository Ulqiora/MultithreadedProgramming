CC=g++
BD=../build
CXX_FLAGS=-c #-Wall -Werror -Wextra -Wfloat-equal -Warray-bounds -std=c++17
LCOVFLAGS=-fprofile-arcs -ftest-coverage
GTESTFLAGS=-lgtest

.PHONY: winograd

ifeq ($(shell uname -s), Linux)
	GTESTFLAGS+= -lpthread -lrt
endif
#              Файлы для основного проекта
WINOGRAD_SOURCES= main_debug.cpp Matrix.cpp WinogradAlgorithm.cpp WinogradView.cpp
WINOGRAD_OBJECTS=$(addprefix $(BD)/,$(WINOGRAD_SOURCES:.cpp=.o))
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
	