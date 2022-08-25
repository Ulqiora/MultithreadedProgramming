#pragma once
#include <algorithm>
#include <list>
#include <vector>
#include <mutex>
#include <thread>
#include <functional>
#include <future>
#include "TsmResult.h"
#include "Ant.h"
namespace s21 {

class AntAlgorithm {
private:
    Graph* graph = nullptr;
    Matrix pheromoneMap;
    std::vector<Ant> ants;
    std::vector<std::thread> threads;
    const int numOfIteration = 30;
    const int evaporationCoef = 0.5;
    const double startPheromone = 0.5;
    void initPheromonesMap();

    void updatePheromoneMap();
    void updateTsmResult(TsmResult* result,int& numOfIteration);

    void createAnts();
    
   public:
    AntAlgorithm() = default;
    TsmResult start(Graph* graphTest);
};

}  // namespace s21