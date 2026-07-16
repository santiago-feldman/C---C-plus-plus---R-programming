cmake_minimum_required(VERSION 3.0)

project("DNA Tool")

set (CMAKE_CXX_STANDARD 11)

# From "Working with CMake" documentation:
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin" OR ${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    # AddressSanitizer (ASan)
    add_compile_options(-fsanitize=address)
    add_link_options(-fsanitize=address)
endif()
if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    # UndefinedBehaviorSanitizer (UBSan)
    add_compile_options(-fsanitize=undefined)
    add_link_options(-fsanitize=undefined)
endif()

add_executable(
  main 
  main.cpp
  Hirschberg.cpp
)

# Main test
enable_testing()
add_executable(
  main_test 
  main_test.cpp
  Hirschberg.cpp
)
add_test(NAME test1 COMMAND edabotcontroller_test)