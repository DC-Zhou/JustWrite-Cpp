//
// Created by a'a on 2023/2/28.
//
#include "wrapper.h"
#include <iostream>
template wrapper<int>;          //[2]

void f()
{
    ext::wrapper<int> a{42};
    std::cout << a.data << "\n";
}