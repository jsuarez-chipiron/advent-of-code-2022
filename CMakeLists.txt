cmake_minimum_required(VERSION 3.1)

project(advent_of_code_2022)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

add_executable(day1_1 day1_1.cpp)
add_executable(day1_2 day1_2.cpp)

# target_link_libraries(day1_1 -ltimer)
# target_link_libraries(main /usr/local/lib/libtimer.a) 
