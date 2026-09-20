cmake_minimum_required(VERSION 4.3)
project(engine)

set(CMAKE_CXX_STANDARD 23)

find_package(pybind11 REQUIRED)
find_package(PkgConfig REQUIRED)

pkg_check_modules(PQXX REQUIRED IMPORTED_TARGET libpqxx)

pybind11_add_module(engine engine.cpp csv_parser.cpp db_connector.cpp)
target_link_libraries(engine PRIVATE PkgConfig::PQXX)