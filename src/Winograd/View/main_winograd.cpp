#include <iostream>
#include <thread>
#include <chrono>
#include "WinogradView.h"
int main(){
    std::cout<<static_cast<int>(s21::TypeOfRun::ONE);
    s21::WinogradView WV;
    WV.show();
    return 0;
}