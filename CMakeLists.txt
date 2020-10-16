cmake_minimum_required(VERSION 3.15)
project(gpu_karp_rabin VERSION 1.0)
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/src/**/*.cpp ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_executable(main main.cpp ${SRC_FILES})
target_include_directories(main PUBLIC ${PROJECT_SOURCE_DIR}/header)