#pragma once

#include <functional>
#include <limits>
#include <exception>

#include "../Model/WinogradAlgorithm.h"
#include "../../SharedFiles/TimeTest.h"

namespace s21{
enum class TypeMatrix{Randomly,Manualy};
class WinogradView{
private:
    WinogradAlgorithm WA;
    TimeTest timer;
    const std::string errorMessage="Incorrect input! Repeat again.\n";
    const std::string errorCtrlD="Incorrect input! Re-start program.\n";
    // bool isValid(std::function<bool(int)>);
    void printMainWindow();
    void printChooseTypeInitMatricesWindow();
    template<typename T>
    T readFromCin(std::function<bool(T)>& funcOfValid);
    template<typename T>
    T entryWithInvitation(std::string invate,std::function<bool(T)>& funcOfValid);
    void startMeasuring(std::string paragraphName,int numOfCycles,TypeOfRun,int numOfThreads=-1);
    void setToAlgorithm(const Matrix& M1,const Matrix& M2,int numOfCycles);
    Matrix readMatrixFromCin(int row,int col);
    void showSetMatricesSizeWindow(TypeMatrix typeMatrices);
    Matrix showSetMatricesValues(TypeMatrix currentChoose,int numberOfMatrix,int row,int col);
    Matrix setMatricesByTypeForInit(TypeMatrix type,int row,int col,int numberOfMatrix);
public:
    void show();
};


template<typename T>
T WinogradView::entryWithInvitation(std::string invate,std::function<bool(T)>& funcOfValid)
{
    std::cout << invate;
    try {
        return readFromCin<T>(funcOfValid);
    } catch (const std::exception& e) {
        throw e;
    }
}


template<typename T>
T WinogradView::readFromCin(std::function<bool(T)>& func) {
    T mode;
    try {
        while(std::cin>>mode){
            if(func(mode)) return mode;
            else std::cerr<<errorMessage;
        }
        throw std::domain_error("^D");
    } catch (const std::invalid_argument& e) {
        std::cerr<<errorMessage;
        return readFromCin<T>(func);
    } catch (const std::out_of_range& e){
        std::cerr<<errorMessage;
        return readFromCin<T>(func);
    } catch (const std::domain_error& e){
        throw e;
    }
}

}