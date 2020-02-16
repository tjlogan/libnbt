cmake_minimum_required(VERSION 3.5)

if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
   message(FATAL_ERROR "In-source builds are not allowed.")
endif("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")

target_sources(runTests 
   PRIVATE
   ${CMAKE_CURRENT_LIST_DIR}/parser.cpp
)

target_sources(reader 
   PRIVATE
   ${CMAKE_CURRENT_LIST_DIR}/parser.cpp
)