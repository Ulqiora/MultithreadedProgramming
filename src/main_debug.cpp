#include "AntAlgorithm/AntAlgorithm.h"
#include "SharedFiles/TimeTest.h"
#include "SharedFiles/TypeOfRun.h"
#include <iostream>
#include <thread>
#include <chrono>
int main(){

    std::cout<<std::thread::hardware_concurrency();
    s21::Graph g1;
    g1.loadGraphFromFile("../materials/matrices/11.txt");

    s21::AntAlgorithm ant;
    ant.setGraph(&g1);
    s21::TimeTest tt;
    std::cout<<tt.startest<s21::AntAlgorithm,std::chrono::milliseconds>(ant,s21::TypeOfRun::ONE,100)<<'\n';
    std::cout<<tt.startest<s21::AntAlgorithm,std::chrono::milliseconds>(ant,s21::TypeOfRun::MILTI_CLASSIC,100)<<'\n';
    return 0;
}