cmake_minimum_required(VERSION 3.24)
project(NumToString)

set(CMAKE_CXX_STANDARD 17)

add_executable(NumToString num_to_string.cpp)
# add_executable(compile_time_string log_str.cpp)
add_executable(compile_in_constexpr compile_in_non_constexpr.cpp)
add_executable(pmr_string pmr_string.cpp)