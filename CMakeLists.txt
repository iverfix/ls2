cmake_minimum_required(VERSION 3.15)
project (ls2)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


set(CMAKE_CXX_STANDARD 23) 
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)  

set(SOURCES
    src/lsCore.cpp
    src/display.cpp
    src/filehandler.cpp
    src/argumentParser.cpp
    src/UnixFileInfo.cpp
    src/main.cpp)

set(HEADERS
    include/lsCore.h
    include/entry.h
    include/display.h
    include/OsFileInfo.h
    include/stringFormater.h
    include/argumentParser.h
    include/UnixFileInfo.h
    include/filehandler.h
    include/IFileHandler.h
)

find_package(GTest REQUIRED)
include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
target_link_libraries(${PROJECT_NAME} gtest::gtest)

enable_testing()

add_executable(
  unit_tests
  src/argumentParser.cpp
  src/UnixFileInfo.cpp
  src/display.cpp
  tests/mocks/MockFileHandler.h
  tests/filehandler.test.cpp
  tests/argumentParser.test.cpp
  tests/display.test.cpp
)
target_link_libraries(
  unit_tests
  GTest::gtest_main
  GTest::gmock
)

include(GoogleTest)
gtest_discover_tests(unit_tests)
