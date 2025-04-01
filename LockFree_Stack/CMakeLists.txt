cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

project(LockFreeStack)


add_executable(
        main
        main.cpp
        lock_free_stack_with_delete_list.hpp
        lock_free_stack_with_hazard_pointer.hpp
        lock_free_stack_with_reference_counting.hpp
)
