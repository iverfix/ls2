cmake_minimum_required(VERSION 3.15)
project (ls2)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


set(CMAKE_CXX_STANDARD 20) 
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)  

set(SOURCES
    src/stringFormater.cpp
    src/filehandler.cpp
    src/main.cpp)

set(HEADERS
    src/stringFormater.h
    src/filehandler.h
)

find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
target_link_libraries(${PROJECT_NAME} gtest::gtest)

enable_testing()

add_executable(
  hello_test
  src/stringFormater.cpp
  src/filehandler.test.cpp
  src/stringFormater.test.cpp
)
target_link_libraries(
  hello_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(hello_test)
