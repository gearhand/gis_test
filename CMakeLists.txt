cmake_minimum_required(VERSION 3.15)
project(gis_test)

set(CMAKE_CXX_STANDARD 17)

add_executable(gis_test main.cpp)
target_include_directories(gis_test PRIVATE third_party/tclap-1.2.2/include)
