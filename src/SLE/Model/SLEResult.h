#pragma once
#include <iostream>
#include <vector>

namespace s21 {
struct SLEResult {
    std::vector<double> answer;
};
std::ostream& operator<<(std::ostream& os, SLEResult res);
}  // namespace s21
