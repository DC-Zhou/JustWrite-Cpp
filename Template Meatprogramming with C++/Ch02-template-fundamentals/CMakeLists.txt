cmake_minimum_required(VERSION 3.24)
project(Ch01_template_fundamentals)

set(CMAKE_CXX_STANDARD 17)

add_executable(function-template function-template.cpp)
add_executable(class-template class-template.cpp)
add_executable(member-function-template member-function-template.cpp)
add_executable(non-type-template-parameters non-type-template-parameters.cpp)
add_executable(template-template-parameter template-template-parameter.cpp)
add_executable(template-specialization template-specialization.cpp)
add_executable(generic-lambdas generic-lambdas.cpp)