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
    // m1(0,0)=1, m1(0,1)=2;
    // m1(1,0)=3, m1(1,1)=4;
    // m2(0,0)=1, m2(0,1)=2;
    // m2(1,0)=3, m2(1,1)=4;
    m1.setRandom(1000,1000);
    m2.setRandom(1000,1000);
    s21::WinogradAlgorithm WA;
    WA.setMatrixFirst(m1);
    WA.setMatrixSecond(m2);
    WA.setNumOfThreads(16);
    s21::TimeTest tt;
    int time=tt.startest<s21::WinogradAlgorithm,std::chrono::milliseconds,s21::Matrix>(WA,s21::TypeOfRun::MULTI_CLASSIC_WITH_NUM,10);
    std::cout<<"Total Time:           "<<time;
    std::cout<<"\nAlgorithm finished\n";
    return 0;
}