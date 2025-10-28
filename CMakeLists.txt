cmake_minimum_required(VERSION 3.15)
project (ls2)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


set(CMAKE_CXX_STANDARD 23) 
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)  

set(SOURCES
    src/LsCore.cpp
    src/Display.cpp
    src/Filehandler.cpp
    src/ArgumentParser.cpp
    src/UnixFileInfo.cpp
    src/main.cpp)

set(HEADERS
    include/LsCore.h
    include/Entry.h
    include/Display.h
    include/OsFileInfo.h
    include/StringFormater.h
    include/ArgumentParser.h
    include/UnixFileInfo.h
    include/Filehandler.h
    include/IFileHandler.h
)

find_package(GTest REQUIRED)
include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
target_link_libraries(${PROJECT_NAME} gtest::gtest)

enable_testing()

add_executable(
  unit_tests
  src/ArgumentParser.cpp
  src/UnixFileInfo.cpp
  src/Display.cpp
  tests/mocks/MockFileHandler.h
  tests/Filehandler.test.cpp
  tests/ArgumentParser.test.cpp
  tests/Display.test.cpp
)
target_link_libraries(
  unit_tests
  GTest::gtest_main
  GTest::gmock
)

include(GoogleTest)
gtest_discover_tests(unit_tests)
