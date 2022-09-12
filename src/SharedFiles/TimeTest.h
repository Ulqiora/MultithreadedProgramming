#pragma once
#include <any>
#include <chrono>
#include "TypeOfRun.h"
namespace s21{

struct TimeTest{
    template<typename Algorithm,typename time,typename Result>
    static int startest(Algorithm& alg,TypeOfRun type, int cycleNumber){
        try {
            auto begin = std::chrono::steady_clock::now();
            for (int i = 0; i < cycleNumber; i++) {
                // std::cout<<i<<'\n';
                alg.start(type);
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