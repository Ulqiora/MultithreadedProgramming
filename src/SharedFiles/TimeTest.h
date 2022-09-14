#pragma once
#include <any>
#include <chrono>
#include "TypeOfRun.h"
namespace s21{

struct TimeTest{
    template<typename Algorithm,typename time,typename Result>
    static Result startest(Algorithm& alg,TypeOfRun type, int cycleNumber){
        try {
            Result res;
            auto begin = std::chrono::steady_clock::now();
            for (int i = 0; i < cycleNumber; i++) {
                if (i == 0)
                    res= alg.start(type);
                else
                    alg.start(type);
            }
            auto end = std::chrono::steady_clock::now();
            std::cout << "Execution time: " << std::chrono::duration_cast<time>(end - begin).count() << '\n';
            return res;
        } catch (const std::exception& e) {
            throw e;
        }
    }
};
}