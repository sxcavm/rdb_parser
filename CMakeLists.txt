cmake_minimum_required(VERSION 3.29)
project(rdb_parser)

set(CMAKE_CXX_STANDARD 20)

add_executable(rdb_parser src/main.cpp
        src/rdb_parser.cpp
        include/rdb_parser.hpp)
