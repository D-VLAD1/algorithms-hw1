cmake_minimum_required(VERSION 3.27)
project(algorithms_hw1 CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(algorithms_hw1
        src/main.cpp
        include/student.cpp
        include/student_list.cpp
)
