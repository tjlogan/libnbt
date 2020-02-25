cmake_minimum_required(VERSION 3.5)

if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
   message(FATAL_ERROR "In-source builds are not allowed.")
endif("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")

target_sources(nbt
   PRIVATE
   ${CMAKE_CURRENT_LIST_DIR}/base_tag.cpp
   ${CMAKE_CURRENT_LIST_DIR}/byte_tag.cpp
   ${CMAKE_CURRENT_LIST_DIR}/int_tag.cpp
   ${CMAKE_CURRENT_LIST_DIR}/short_tag.cpp
   ${CMAKE_CURRENT_LIST_DIR}/compound_tag.cpp
   ${CMAKE_CURRENT_LIST_DIR}/string_tag.cpp
   ${CMAKE_CURRENT_LIST_DIR}/long_tag.cpp
   ${CMAKE_CURRENT_LIST_DIR}/list_tag.cpp
   ${CMAKE_CURRENT_LIST_DIR}/float_tag.cpp
)
