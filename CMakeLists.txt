cmake_minimum_required(VERSION 3.5)

project(STACK)

# стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(stack_app src/main.cpp)

target_include_directories(stack_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)