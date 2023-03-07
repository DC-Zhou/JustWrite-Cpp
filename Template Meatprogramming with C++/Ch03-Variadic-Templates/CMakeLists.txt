cmake_minimum_required(VERSION 3.24)
project(Ch03_Variadic_Templates)

set(CMAKE_CXX_STANDARD 20)

add_executable(with-no-variadic-template the-need-of-variadic-template.cpp)
add_executable(variadic-template variadic-template.cpp)
add_executable(parameter-packs parameter-packs.cpp)
