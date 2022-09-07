#include "AntAlgorithm/AntAlgorithm.h"
#include "SharedFiles/TimeTest.h"
#include "SharedFiles/TypeOfRun.h"
#include "Winograd/WinogradAlgorithm.h"
#include <iostream>
#include <thread>
#include <chrono>

void foo(){
    std::cout<<"KU";
}
int main(){
    s21::Matrix m1(2,2),m2(2,2);
    m1.setRandom(600,500);
    m2.setRandom(500,600);
    s21::WinogradAlgorithm WA;
    WA.setMatrixFirst(m1);
    WA.setMatrixSecond(m2);
    WA.setNumOfThreads(12);
    s21::TimeTest tt;
    int time=tt.startest<s21::WinogradAlgorithm,std::chrono::milliseconds,s21::Matrix>(WA,s21::TypeOfRun::ONE,1);
    std::cout<<"Total Time:           "<<time;
    std::cout<<"\nAlgorithm finished\n";
    return 0;
}