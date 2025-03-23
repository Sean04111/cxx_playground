cmake_minimum_required(VERSION 3.30)
project(sfinae)

set(CMAKE_CXX_STANDARD 26)

add_executable(
        sfinae
        main.cpp
        sfinae.hpp
        sfinae.cpp
)
