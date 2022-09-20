#include "TsmResult.h"
namespace s21 {
std::ostream& operator<<(std::ostream& os, TsmResult res) {
    os << "Distance =  " << res.distance << '\n';
    os << "Path = ";
    for (auto& vertex : res.vertices) {
        std::cout << vertex << ' ';
    }
    os << '\n';
    return os;
}
}  // namespace s21
