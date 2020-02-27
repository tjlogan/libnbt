cmake_minimum_required(VERSION 3.5)

if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
   message(FATAL_ERROR "In-source builds are not allowed.")
endif("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests tag_test.cpp parser_test.cpp)
target_link_libraries(runTests ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARY} pthread nbt)