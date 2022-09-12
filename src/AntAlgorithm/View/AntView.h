#pragma once

#include <functional>
#include <limits>
#include <exception>

#include "../Model/AntAlgorithm.h"
#include "../../SharedFiles/TimeTest.h"

namespace s21{
enum class TypeMatrix{Randomly,Manualy};
class AntView{
private:
    AntAlgorithm AA;
    TimeTest timer;
    const std::string errorMessage="Incorrect input! Repeat again.\n";
    const std::string errorCtrlD="Incorrect input! Re-start program.\n";
private:
    void printMainWindow();
    void printSelectAction();
    template<typename T>
    T readFromCin(std::function<bool(T)>& funcOfValid);
    template<typename T>
    T entryWithInvitation(std::string invate,std::function<bool(T)>& funcOfValid);
private:
    void setToAlgorithm(const std::string&);
    void startMeasuring(std::string paragraphName, int numOfCycles, TypeOfRun type);
public:
    void show();
};


template<typename T>
T AntView::entryWithInvitation(std::string invate,std::function<bool(T)>& funcOfValid)
{
    std::cout << invate;
    try {
        return readFromCin<T>(funcOfValid);
    } catch (const std::exception& e) {
        throw e;
    }
}


template<typename T>
T AntView::readFromCin(std::function<bool(T)>& func) {
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