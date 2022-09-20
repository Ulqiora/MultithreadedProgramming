#pragma once
#include <map>
#include <memory>
#include <random>
#include <vector>

#include "Graph/graph.h"
namespace s21 {

class Ant {
 private:
    std::vector<bool> passedCity;
    std::vector<int> path;
    double proximityRatio = 1.0;
    double alpha = 1.0;
    double beta = 1.0;
    double pathLength = 0;
    int getRamdomValue(int minimum, int maximum);

 private:
    void initToStart(int sizeOfGraph);
    std::map<int, double>* createDictionaryOfAvailablePaths(Graph* graph);
    double calculateNumerator(std::map<int, double>* dictionaryOfAvailablePaths,
                              const SquareMatrix& pheromonesMap, int currentIndex);
    double calcDenominator(std::map<int, double>* dictionaryOfAvailablePaths,
                           const SquareMatrix& pheromonesMap);
    std::map<int, double>* calcProbabilities(Graph* graph, const SquareMatrix& pheromonesMap);

    void chooseWay(Graph* graph, std::map<int, double>* probabilities);

 public:
    Ant() = default;
    void findPath(Graph* graph, const SquareMatrix& pheromonesMap);
    void updatePheromones(SquareMatrix* pheromonesMap);
    double getPathLength() { return pathLength; }
    std::vector<int> getPath() { return path; }
};
}  // namespace s21
