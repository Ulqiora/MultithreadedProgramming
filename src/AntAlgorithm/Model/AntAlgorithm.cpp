#include "AntAlgorithm.h"

namespace s21 {
// std::mutex mtx;
void AntAlgorithm::initPheromonesMap() {
    pheromoneMap.setSize(graph->size());
    for (int i = 0; i < pheromoneMap.size(); ++i) {
        for (int j = 0; j < pheromoneMap.size(); ++j) {
            if (i != j) pheromoneMap(i, j) = startPheromone;
        }
    }
}

void AntAlgorithm::updatePheromoneMap() {
    pheromoneMap *= (1 - evaporationCoef);
    for (auto& ant : ants) {
        ant.updatePheromones(&pheromoneMap);
    }
}

void AntAlgorithm::updateTsmResult(TsmResult* result, int& numOfIteration) {
    std::list<double> paths;
    for (auto& ant : ants) paths.push_back(ant.getPathLength());
    double minimumPath = *(std::min_element(paths.begin(), paths.end()));
    if (minimumPath < result->distance) {
        for (auto& ant : ants) {
            if (std::fabs(ant.getPathLength() - minimumPath) < std::numeric_limits<double>::epsilon()) {
                result->vertices = ant.getPath();
                result->distance = minimumPath;
                break;
            }
        }
    }
}

void AntAlgorithm::runAntOneThread() {
    for (int i = 0; i < graph->size(); ++i) ants[i].findPath(graph, pheromoneMap);
}
void AntAlgorithm::runAntMultiThreads() {
    for (int i = 0; i < graph->size(); ++i) {
        threads[i] =
            std::thread([&ant = (ants[i]), g = graph, &pM = pheromoneMap]() { ant.findPath(g, pM); });
    }
    for (auto& thread : threads) {
        thread.join();
    }
}

void AntAlgorithm::createAnts() {
    ants.clear();
    ants.resize(graph->size(), Ant());
    threads.resize(graph->size());
}

void AntAlgorithm::setGraph(Graph* other) { graph = other; }

TsmResult AntAlgorithm::start(TypeOfRun type) {
    if (type == TypeOfRun::MULTI_CONVEYOR)
        throw std::invalid_argument("This type is not applicable to this algorithm!");
    TsmResult result;
    if (!graph) throw std::invalid_argument("This graph is empty");
    initPheromonesMap();
    for (int numOfIteration = 0; numOfIteration != 100; numOfIteration++) {
        createAnts();
        if (type == TypeOfRun::ONE)
            runAntOneThread();
        else
            runAntMultiThreads();
        for (int i = 0; i < graph->size(); ++i) ants[i].findPath(graph, pheromoneMap);
        updatePheromoneMap();
        updateTsmResult(&result, numOfIteration);
    }
    for (auto& i : result.vertices) i++;
    return result;
}

}  // namespace s21