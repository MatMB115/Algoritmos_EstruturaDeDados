cmake_minimum_required(VERSION 3.22)
project(Select_Insert C)

set(CMAKE_C_STANDARD 99)

add_executable(Select_Insert main.c cmake-build-debug/selecaoInsercao.c cmake-build-debug/selecaoInsercao.h cmake-build-debug/selecaoInsercao.c cmake-build-debug/selecaoInsercao.h)
