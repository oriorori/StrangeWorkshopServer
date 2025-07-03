cmake_minimum_required(VERSION 3.10)
project(
    BoostAsioServer
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(THREADS_PREFER_PTHREAD_FLAG ON)

add_subdirectory(core)

add_executable(server main.cpp)

target_link_libraries(server PRIVATE core)