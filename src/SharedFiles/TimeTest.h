#pragma once
#include <any>
#include <chrono>
#include "../AntAlgorithm/AntAlgorithm.h"

namespace s21{

struct TimeTest{
    template<typename Algorithm,typename time>
    static int startest(Algorithm& alg,TypeOfRun type, int cycleNumber){
        try {
            auto begin = std::chrono::steady_clock::now();
            for (int i = 0; i < cycleNumber; i++) {
                TsmResult res = alg.start(type);
                std::cout << i << ":  distance=" << res.distance << '\n';
            }
            auto end = std::chrono::steady_clock::now();
            int result = std::chrono::duration_cast<time>(end - begin).count();
            return result;
        } catch (const std::exception& e) {
            throw e;
        }
    }
};
}