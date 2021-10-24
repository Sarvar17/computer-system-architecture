cmake_minimum_required(VERSION 3.10)
 
set(CMAKE_CXX_STANDARD 17) 
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(homework_2 VERSION 1.0)

add_executable(homework_2 main.cpp language.cpp procedure.cpp functional.cpp oop.cpp container.cpp)
