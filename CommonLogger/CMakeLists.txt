cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

project(CommonLogger)

add_executable(
        main
        main.cpp
        logger.hpp
        printer.hpp
        printer.cpp
        logger.cpp
)
