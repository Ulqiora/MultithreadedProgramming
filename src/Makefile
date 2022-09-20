CC=g++
BD=../build
CXX_FLAGS=-c -Wall -Werror -Wextra -std=c++17
LCOVFLAGS=-fprofile-arcs -ftest-coverage
GTESTFLAGS=-lgtest

.PHONY: winograd ant

ifeq ($(shell uname -s), Linux)
	GTESTFLAGS+= -lpthread -lrt
endif
###      Winograd Algorithm
##       Model and View 
WINOGRAD_SOURCES= main_winograd.cpp Matrix.cpp WinogradAlgorithm.cpp WinogradView.cpp
WINOGRAD_OBJECTS=$(addprefix $(BD)/,$(WINOGRAD_SOURCES:.cpp=.o))
###      Ant Algorithm
##       Model and View 
ANT_SOURCES= main_ant.cpp SquareMatrix.cpp graph.cpp Ant.cpp AntAlgorithm.cpp AntView.cpp TsmResult.cpp
ANT_OBJECTS=$(addprefix $(BD)/,$(ANT_SOURCES:.cpp=.o))
###      SLE Algorithm
##       Model and View 
SLE_SOURCES= main_sle.cpp Matrix.cpp SLEAlgorithm.cpp SLEConsoleView.cpp SLEResult.cpp
SLE_OBJECTS=$(addprefix $(BD)/,$(SLE_SOURCES:.cpp=.o))


winograd:clean $(WINOGRAD_OBJECTS)
	$(CC) -g  $(WINOGRAD_OBJECTS) -o $(BD)/$@  -lpthread
	./$(BD)/$@

ant:clean $(ANT_OBJECTS)
	$(CC) -g  $(ANT_OBJECTS) -o $(BD)/$@  -lpthread
	./$(BD)/$@

gauss:clean $(SLE_OBJECTS)
	$(CC) -g  $(SLE_OBJECTS) -o $(BD)/$@  -lpthread
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

cpplint:
	cp -f ../materials/linters/CPPLINT.cfg ./
	python3 ../materials/linters/cpplint.py --extensions=cpp ../src/*/*.h ../src/*/*.cpp ../src/*/*/*.h ../src/*/*/*.cpp
	rm -rf CPPLINT.cfg
	