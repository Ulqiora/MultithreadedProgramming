#include "AntAlgorithm/AntAlgorithm.h"
#include <chrono>
int main(){
    using namespace s21;
    Graph g1;
    g1.loadGraphFromFile("../materials/matrices/11.txt");
    auto begin = std::chrono::steady_clock::now();
    for (int i=0;i<100;i++) {
        AntAlgorithm aa;
        TsmResult res = aa.start(&g1);
        std::cout<<i<<":  distance="<<res.distance<<'\n';
    }
    auto end = std::chrono::steady_clock::now();
    int time=std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
    std::cout<<"Total time,ms:"<<time;
    return 0;
}