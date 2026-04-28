cmake_minimum_required(VERSION 4.1)
project(tachy_mp3 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17 CACHE STRING "The C++ standard to use")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


add_executable(${PROJECT_NAME} app/tachy_mp3.cpp)
