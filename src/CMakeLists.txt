cmake_minimum_required(VERSION 3.5)

if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
   message(FATAL_ERROR "In-source builds are not allowed.")
endif("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")

add_executable(reader main.cpp)

add_library(nbt STATIC parser.cpp)

target_link_libraries(reader nbt)

add_subdirectory(tag)
