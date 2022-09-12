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
#include "../../SharedFiles/TypeOfRun.h"
namespace s21 {

class AntAlgorithm {
private:
    Graph* graph = nullptr;
    SquareMatrix pheromoneMap;
    std::vector<Ant> ants;
    std::vector<std::thread> threads;
    const int numOfIteration = 30;
    const int evaporationCoef = 0.5;
    const double startPheromone = 0.5;
    void initPheromonesMap();
    void runAntOneThread();
    void runAntMultiThreads();
    void updatePheromoneMap();
    void updateTsmResult(TsmResult* result,int& numOfIteration);
    void createAnts();
   public:
    AntAlgorithm() = default;
    void setGraph(Graph*);
    TsmResult start(TypeOfRun);
};

}  // namespace s21