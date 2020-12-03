cmake_minimum_required(VERSION 3.15)
project(gis_test)

set(CMAKE_CXX_STANDARD 17)

add_executable(gis_test main.cpp checksum.h checksum.cpp words.cpp words.h arguments.cpp arguments.h)
target_include_directories(gis_test PRIVATE third_party/tclap-1.2.2/include)

add_subdirectory(third_party/googletest-release-1.10.0)
add_executable(tests test/tests.cpp words.cpp checksum.cpp)
target_link_libraries(tests gtest_main)
if (WIN32)
    target_link_libraries(gis_test ws2_32)
    target_link_libraries(tests ws2_32)
endif()
target_include_directories(tests PRIVATE third_party/googletest-release-1.10.0/googletest/include)
target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR} third_party/tclap-1.2.2/include)
add_test(NAME tests COMMAND tests)
