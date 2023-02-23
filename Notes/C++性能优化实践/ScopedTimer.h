//
// Created by Zhouzhou on 2023/2/22.
//

#ifndef COMPILE_TIME_OPTIMIZE_SCOPEDTIMER_H
#define COMPILE_TIME_OPTIMIZE_SCOPEDTIMER_H

#include <chrono>
#include <iostream>

class ScopedTimer{
public:
    ScopedTimer(const char* name)
            : m_name(name),
              m_beg(std::chrono::high_resolution_clock::now()) { }

    ~ScopedTimer(){
        auto end = std::chrono::high_resolution_clock::now();
        auto dur = std::chrono::duration_cast<std::chrono::nanoseconds>(end - m_beg);
        std::cout << m_name << ":" << dur.count() << "ns \n";

    }

private:
    const char* m_name;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_beg;
};


#endif //COMPILE_TIME_OPTIMIZE_SCOPEDTIMER_H
