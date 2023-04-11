cmake_minimum_required(VERSION 3.24)
project(TP2)

set(CMAKE_CXX_STANDARD 17)

add_executable(TP2 rate-monotonic.cpp)
#add_executable(TP2 deadline-monotonic.cpp)
#add_executable(TP2 earliest-deadline-first.cpp main.cpp)
