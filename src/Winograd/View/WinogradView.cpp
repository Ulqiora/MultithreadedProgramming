#include "WinogradView.h"

namespace s21 {
void WinogradView::show() {
    int typeMatrices;
    std::function<bool(int)> validfunctions = ([](int a) { return a >= 0 && a <= 4; });
    std::function<bool(int)> validfunctions2 = ([](int a) { return a >= 0 && a <= 2; });
    printMainWindow();
    while (typeMatrices != 0) {
        try {
            printChooseTypeInitMatricesWindow();
            typeMatrices = readFromCin<int>(validfunctions2);
            if (!typeMatrices) continue;
            showSetMatricesSizeWindow(static_cast<TypeMatrix>(typeMatrices));
        } catch (const std::domain_error& e) {
            std::cout<<e.what()<<"."<<errorCtrlD;
            typeMatrices = 0;
        }
    }
}

void WinogradView::printMainWindow() {
    std::cout << "-----------------------------------\n";
    std::cout << "Main window for Winograd Algorithm!\n";
    std::cout << "-----------------------------------\n";
}

void WinogradView::printChooseTypeInitMatricesWindow() {
    std::cout << "-----------------------------------\n";
    std::cout << "Choose type of initialization matrices\n";
    std::cout << "-----------------------------------\n";
    std::cout << "Select one of the following items:\n";
    std::cout << "1 - Manually.\n";
    std::cout << "2 - Randomly.\n";
    std::cout << "0 - Exit.\n";
}

void WinogradView::showSetMatricesSizeWindow(TypeMatrix typeMatrices){
    int TypeOfMatrices,rowsFirst,colsFirst,rowsSecond,colsSecond,numOfCycles;
    std::function<bool(int)> validfunctions = ([](int a) { return a>0; });
    std::function<bool(int)> validfunctions2 = ([&colsFirst](int a) { return a==colsFirst; });
    Matrix first, second;
    while (true){
        try
        {
            rowsFirst=entryWithInvitation<int>("Введите число строк первой матрицы: ",validfunctions);
            colsFirst=entryWithInvitation<int>("Введите число столбцов первой матрицы: ",validfunctions);
            rowsSecond=entryWithInvitation<int>("Введите число строк второй матрицы: ",validfunctions2);
            colsSecond=entryWithInvitation<int>("Введите число столбцов второй матрицы: ",validfunctions);
            first = setMatricesByTypeForInit(typeMatrices,rowsFirst,colsFirst,1);
            second = setMatricesByTypeForInit(typeMatrices,rowsSecond,colsSecond,2);
            numOfCycles=entryWithInvitation<int>("Введите число циклов: ",validfunctions);
            setToAlgorithm(first, second, numOfCycles);
            break;
        } catch(const std::exception& e) {
            throw e;
        }
    }
}


Matrix WinogradView::setMatricesByTypeForInit(TypeMatrix type,int row,int col,int numberOfMatrix)
{
    if (type == TypeMatrix::Manualy) {
        return showSetMatricesValues(type, numberOfMatrix, row, col);
    } else {
        Matrix res;
        res.setRandom(row,col);
        return res;
    }
}


Matrix WinogradView::showSetMatricesValues(TypeMatrix currentChoose, int numberOfMatrix, int row, int col) {
    Matrix result;
    if (currentChoose == TypeMatrix::Randomly) {
        result.setRandom(row, col);
    } else {
        try {
            std::cout<<"Input "<<numberOfMatrix<<"matrix\n";
            result = readMatrixFromCin(row, col);
        } catch (const std::exception& e) {
            throw e;
        }
    }
    return result;
}

Matrix WinogradView::readMatrixFromCin(int row,int col){
    std::function<bool(double)> validFunction = [](double a) { return true; };
    Matrix result(row, col);
    try {
        for (int i = 0; i < result.getRows(); i++) {
            for (int j = 0; j < result.getCols(); j++) {
                result(i, j) = readFromCin<double>(validFunction);
            }
        }
    } catch (const std::exception& e) {
        throw e;
    }
    return result;
}

void WinogradView::setToAlgorithm(const Matrix& M1, const Matrix& M2, int numOfCycles) {
    WA.setMatrixFirst(M1);
    WA.setMatrixSecond(M2);
    try {

        startMeasuring("Однопоточный режим\n", numOfCycles, TypeOfRun::ONE);
        startMeasuring("Классический режим\n", numOfCycles, TypeOfRun::MULTI_CLASSIC);
        startMeasuring("Конвеерный режим режим\n", numOfCycles, TypeOfRun::MULTI_CONVEYOR);
        startMeasuring("Многопотчность с 2 потоками\n", numOfCycles, TypeOfRun::MULTI_CLASSIC_WITH_NUM, 2);
        for (int i = 4; i <= std::thread::hardware_concurrency(); i += 4) {
            startMeasuring("Многопотчность с " + std::to_string(i) + " потоками\n", numOfCycles,
                           TypeOfRun::MULTI_CLASSIC_WITH_NUM, i);
        }
        startMeasuring("Классический режим\n", 1, TypeOfRun::MULTI_CLASSIC, -1 ,true);
    } catch (const std::exception& e) {
        throw e;
    }
}

void WinogradView::startMeasuring(std::string paragraphName, int numOfCycles, TypeOfRun type,int numOfThreads,bool printable) {
    if(numOfThreads > 0) WA.setNumOfThreads(numOfThreads); 
    std::cout << paragraphName;
    try {
        Matrix res =
            timer.startest<WinogradAlgorithm, std::chrono::milliseconds, Matrix>(WA, type, numOfCycles);
        if(printable){
            std::cout << "-----------------------------------\n";
            std::cout<<res;
        }
    } catch (const std::exception& e) {
        throw e;
    }
}

}  // namespace s21