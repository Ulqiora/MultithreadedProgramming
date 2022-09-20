#include "SLEResult.h"
namespace s21 {
std::ostream& operator<<(std::ostream& os, SLEResult res) {
    os << "Result = ";
    if (res.answer.size() > 0) {
        for (unsigned int i = 0; i < res.answer.size(); i++) {
            std::cout << res.answer[i] << ' ';
        }
        std::cout << std::endl;
    } else {
        throw std::out_of_range("There is no answer");
    }
    os << '\n';
    return os;
}
}  // namespace s21
