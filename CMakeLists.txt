cmake_minimum_required(VERSION 3.23)
project(DataTable LANGUAGES CXX)

if (MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

add_library(dataTable SHARED)
target_compile_features(dataTable PRIVATE cxx_std_20)
target_include_directories(dataTable PRIVATE "${PROJECT_SOURCE_DIR}")
add_subdirectory("src")

add_executable(example1)
target_sources(example1 PRIVATE "examples/dataTable.cpp")
target_link_libraries(example1 PRIVATE dataTable)
target_compile_features(example1 PRIVATE cxx_std_20)


add_executable(example2)
target_sources(example2 PRIVATE "examples/setPermutation.cpp")
target_link_libraries(example2 PRIVATE dataTable)
target_compile_features(example2 PRIVATE cxx_std_20)



