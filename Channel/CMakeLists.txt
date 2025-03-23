cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

project(Channel)

add_executable(
        main
        main.cpp
        channel.hpp
)