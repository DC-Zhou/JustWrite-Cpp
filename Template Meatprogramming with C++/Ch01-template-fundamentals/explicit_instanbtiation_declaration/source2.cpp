//
// Created by a'a on 2023/2/28.
//
#include "wrapper.h"
#include <iostream>

void g()
{
    wrapper<int> a{100};
    std::cout << a.data << "\n";
}
