cmake_minimum_required(VERSION 3.5)

if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
   message(FATAL_ERROR "In-source builds are not allowed.")
endif("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)
add_subdirectory(src)
add_subdirectory(test)