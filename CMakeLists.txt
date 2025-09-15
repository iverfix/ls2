cmake_minimum_required(VERSION 3.15)
project (ls2)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


set(CMAKE_CXX_STANDARD 23) 
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)  

set(SOURCES
    src/stringFormater.cpp
    src/filehandler.cpp
    src/main.cpp)

set(HEADERS
    include/stringFormater.h
    include/filehandler.h
)

find_package(GTest REQUIRED)
include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
target_link_libraries(${PROJECT_NAME} gtest::gtest)

enable_testing()

add_executable(
  hello_test
  src/stringFormater.cpp
  tests/filehandler.test.cpp
  tests/stringFormater.test.cpp
)
target_link_libraries(
  hello_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(hello_test)
