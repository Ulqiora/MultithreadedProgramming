#include "AntView.h"

namespace s21 {
void AntView::show() {
    int typeMatrices = -1;
    std::function<bool(int)> validfunctions = ([](int a) { return a == 0 || a == 1; });
    std::function<bool(std::string)> validfunctionsFilename =
        ([](std::string a) { return (a.empty() || true); });
    printMainWindow();
    while (typeMatrices != 0) {
        try {
            printSelectAction();
            typeMatrices = readFromCin<int>(validfunctions);
            if (!typeMatrices) continue;
            std::string filename = entryWithInvitation("Input filename : ", validfunctionsFilename);
            setToAlgorithm(filename);
        } catch (const std::domain_error& e) {
            std::cout << e.what() << "." << errorCtrlD;
            typeMatrices = 0;
        }
    }
}

void AntView::printMainWindow() {
    std::cout << "-----------------------------------\n";
    std::cout << "Main window for Winograd Algorithm!\n";
    std::cout << "-----------------------------------\n";
}

void AntView::printSelectAction() {
    std::cout << "-----------------------------------\n";
    std::cout << "Select an action\n";
    std::cout << "-----------------------------------\n";
    std::cout << "1 - Choose graph file.\n";
    std::cout << "0 - Exit.\n";
    std::cout << "Input: ";
}

void AntView::setToAlgorithm(const std::string& filename) {
    Graph g;
    std::function<bool(int)> validfunctions = ([](int a) { return a > 0; });
    try {
        int numOfCycles = entryWithInvitation("Enter number of the cycles: ", validfunctions);
        g.loadGraphFromFile(filename);
        AA.setGraph(&g);
        startMeasuring("One thread mode\n", numOfCycles, TypeOfRun::ONE);
        startMeasuring("Classic multithreads mode\n", numOfCycles, TypeOfRun::MULTI_CLASSIC, true);
    } catch (const std::exception& e) {
        std::cout << e.what() << '\n';
    }
}

void AntView::startMeasuring(std::string paragraphName, int numOfCycles, TypeOfRun type, bool printable) {
    std::cout << paragraphName;
    try {
        TsmResult res =
            timer.startest<AntAlgorithm, std::chrono::milliseconds, TsmResult>(AA, type, numOfCycles);
        if (printable) {
            std::cout << "-----------------------------------\n";
            std::cout << res;
        }
    } catch (const std::exception& e) {
        throw e;
    }
}

}  // namespace s21
