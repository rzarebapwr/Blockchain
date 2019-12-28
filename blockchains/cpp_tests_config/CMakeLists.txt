cmake_minimum_required(VERSION 3.14)
project(cpp_testy)

set(CMAKE_CXX_STANDARD 17)


set(SOURCE_FILES main.cpp)
add_executable(cpp_testy ${SOURCE_FILES})

include_directories(src)

add_subdirectory(src)
add_subdirectory(test)


target_link_libraries(cpp_testy src)