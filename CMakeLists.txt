cmake_minimum_required(VERSION 3.14)
project(STACK LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ==========================================
# 1. GOOGLE TEST
# ==========================================
include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# ==========================================
# 2. ОСНОВНАЯ ПРОГРАММА
# ==========================================
file(GLOB APP_SOURCES "src/*.cpp")

if(APP_SOURCES)
    add_executable(my_app ${APP_SOURCES})
    target_include_directories(my_app PRIVATE include src)
endif()

# ==========================================
# 3. ТЕСТЫ
# ==========================================
enable_testing()

file(GLOB TEST_SOURCES "test/*.cpp")

if(TEST_SOURCES)
    add_executable(my_tests ${TEST_SOURCES})

    target_include_directories(my_tests PRIVATE include src)
    target_link_libraries(my_tests PRIVATE GTest::gtest_main)   # ← важно: gtest_main

    include(GoogleTest)
    add_test(NAME my_tests COMMAND my_tests)
endif()