cmake_minimum_required(VERSION 3.15)
project (ls2)

set(SOURCES
    src/filehandler.cpp
    src/main.cpp)

set(HEADERS
    src/filehandler.h)

find_package(ZLIB REQUIRED)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ZLIB::ZLIB)
