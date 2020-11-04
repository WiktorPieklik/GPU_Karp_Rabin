cmake_minimum_required(VERSION 3.14)
project(gpu_karp_rabin VERSION 1.0)
set(CMAKE_CXX_STANDARD 20)

add_compile_options(-Wall -Wextra -Wpedantic)

add_executable(main main.cpp)
add_subdirectory(src)
target_link_libraries(main PRIVATE sources text hash utility)

add_executable(benchmark_target benchmark/src/Benchmark.cpp)
add_subdirectory(benchmark/src)
target_link_libraries(benchmark_target PUBLIC benchmark_sources sources text hash utility)