#pragma once

#include <exception>
#include <iostream>
#include <vector>

#include "../../SharedFiles/TimeTest.h"
#include "../../SharedFiles/TypeOfRun.h"
#include "../Model/SLEAlgorithm.h"

namespace s21 {
class SLEConsoleView {
 private:
    enum commands {
        mainMenu = 0,
        loadFile = 1,
        createMatrix = 2,
        solve = 3,
        compare = 4,
        exit = 5,
        compResult = 6,
        wrongCommand = 7
    };

    std::vector<std::string> printable{
        "Choose the command:\n"
        "1. Load matrix from file\n"
        "2. Enter matrix from keyboard\n"
        "3. Solve matrix (one thread)\n"
        "4. Compare one thread and multithread solve\n"
        "5. Exit\n",                                // 0
        "Enter file path:\n",                       // 1
        "Enter size and then values of matrix:\n",  // 2
        "Result of solving in one thread:\n",       // 3
        "Enter number of cycles:\n",                // 4
        "Exiting program\n",                        // 5
        "Result of comparison:\n",                  // 6
        "Wrong command, try again\n"                // 7
    };

    SLEAlgorithm gauss;
    unsigned int curCommand = mainMenu;

 public:
    SLEConsoleView();

 private:
    void runMenu();
    void waitCommand();
    bool isNumber(std::string entry);
    void chooseCommand();
    void fileLoad();
    void matrixEnter();
    void solveMethod();
    void compareMethod();
    void print(const commands& com);
};
}  // namespace s21
