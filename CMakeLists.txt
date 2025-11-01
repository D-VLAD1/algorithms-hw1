cmake_minimum_required(VERSION 3.27)
project(algorithms_hw1 CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(algorithms_hw1
        src/main.cpp
        include/student/student.cpp
        include/implementation1/student_list.cpp
        include/implementation2/student_list2.cpp
        include/implementation2/student_list2.h
        include/implementation3/student_list3.cpp
        include/implementation3/student_list3.h
)
