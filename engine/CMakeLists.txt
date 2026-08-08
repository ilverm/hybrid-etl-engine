cmake_minimum_required(VERSION 4.3)
project(engine)

set(CMAKE_CXX_STANDARD 23)

find_package(pybind11 REQUIRED)

pybind11_add_module(engine engine.cpp)
