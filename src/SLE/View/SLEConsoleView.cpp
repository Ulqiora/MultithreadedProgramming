#include "SLEConsoleView.h"

namespace s21 {

SLEConsoleView::SLEConsoleView() {
    runMenu();
    while (curCommand != exit) {
        try {
            if (std::cin.eof()) {
                std::cout << "^D" << std::endl;
                break;
            }
            waitCommand();
            chooseCommand();
        } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
            runMenu();
        }
    }
}

void SLEConsoleView::runMenu() {
    curCommand = mainMenu;
    chooseCommand();
}

void SLEConsoleView::waitCommand() {
    std::string entry;
    std::cin >> entry;
    if (isNumber(entry)) {
        curCommand = std::stoi(entry);
        if (curCommand > 5) {
            print(wrongCommand);
        }
    } else {
        throw std::out_of_range("Wrong command!\n");
    }
}

bool SLEConsoleView::isNumber(std::string entry) {
    bool result = true;
    for (int i = 0; i < entry.size(); i++) {
        if (!std::isdigit(entry[i])) {
            result = false;
        }
    }
    return result;
}

void SLEConsoleView::chooseCommand() {
    switch(curCommand) {
        case mainMenu:
            print(mainMenu);
            break;
        case loadFile:
            fileLoad();
            break;
        case createMatrix:
            matrixEnter();
            break;
        case solve:
            solveMethod();
            break;
        case compare:
            compareMethod();
            break;
        case exit:
            print(exit);
            break;
        default:
            runMenu();
            break;
    }
}

void SLEConsoleView::fileLoad() {
    print(loadFile);
    std::string filePath;
    std::cin >> filePath;
    try {
        gauss.setFromFile(filePath);
        std::cout << "File loaded successfully\n";
    } catch (std::exception& e) {
        throw;
    }
    runMenu();
}

void SLEConsoleView::matrixEnter() {
  try {
    print(createMatrix);
    gauss.createMatrix();
    std::cout << "Matrix created successfully\n";
  } catch (std::exception& e) {
    throw;
  }
  runMenu();
}

void SLEConsoleView::solveMethod() {
  try {
    print(solve);
    gauss.start();
    gauss.printAnswer();
  } catch (std::exception& e) {
    throw;
  }
  runMenu();
}

void SLEConsoleView::compareMethod() {
    try {
        print(compare);
        std::string num;
        std::cin >> num;
        if (!isNumber(num) || num[0] == '-') {
            throw std::invalid_argument("wrong num of cycles");
        } else {
            print(compResult);
            s21::TimeTest tt;
            std::cout << "One thread, ms: " << tt.startest<SLEAlgorithm,std::chrono::milliseconds>(gauss, TypeOfRun::ONE, std::stoi(num)) << '\n';
            std::cout << "Multithread, ms: " << tt.startest<SLEAlgorithm,std::chrono::milliseconds>(gauss, TypeOfRun::MULTI_CLASSIC, std::stoi(num)) << '\n';
        }
    } catch (std::exception& e) {
        throw;
    }
    runMenu();
}

void SLEConsoleView::print(const commands& com) {
    std::cout << "***" << std::endl;
    std::cout << printable[com];
    std::cout << "***" << std::endl;
}

}  // namespace s21