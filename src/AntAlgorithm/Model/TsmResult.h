#pragma once
#include <iostream>
#include <limits>
#include <vector>
namespace s21 {
struct TsmResult {
    std::vector<int> vertices;
    double distance = std::numeric_limits<double>::infinity();
    friend std::ostream& operator<<(std::ostream& os, TsmResult res);
};
std::ostream& operator<<(std::ostream& os, TsmResult res);
}  // namespace s21