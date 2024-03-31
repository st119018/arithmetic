cmake_minimum_required(VERSION 3.2) # specifies the minimum version of CMake the project needs
									
project(reverseCode VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(reverseCode reverse.cpp) 


										