cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

project(SimpleSharedPtr)


add_executable(
        main
        main.cxx
        SimpleSharedPtr.hxx
        SimpleSharedPtr.cxx
)
