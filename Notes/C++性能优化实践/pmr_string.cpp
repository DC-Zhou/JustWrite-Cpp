//
// Created by Zhouzhou on 2023/2/22.
//
#include "ScopedTimer.h"
// Apple Clang not support memory_resource
#include <memory_resource>

const int SIZE = 1000000;

void test_pmr_string(){
    ScopedTimer timer("pmr string");
    for(int i  = 0; i < SIZE; i++){
        char buffer[1024];
        std::pmr::montonic_buffer_resource resource{&buffer, 1024};
        std::pmr::string s{ &resource};

        s.append("it is a test");
        s.append("it is a long test; it is a long test; it is a long test; it is a long test;");
    }
}

void test_std_string(){
    ScopedTimer timer("std string");
    for(int i = 0; i < SIZE; i++){
        std::string s;
        s.reserve(1024);

        s.append("it is a test");
        s.append("it is a long test; it is a long test; it is a long test; it is a long test;");
    }
}


int main(){
    std::cout << "= small string testing \n";
    for(int i = 0; i < 20; ++i){
        test_pmr_string();
        test_std_string();
    }

    std::pmr
}