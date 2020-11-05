cmake_minimum_required(VERSION 3.14)
project(gpu_karp_rabin VERSION 1.0)
set(CMAKE_CXX_STANDARD 20)
file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/benchmark/results)

add_compile_options(-Wall -Wextra -Wpedantic)

add_executable(main_target main.cpp)
add_subdirectory(main/src)
target_link_libraries(main_target PRIVATE sources text hash utility)

add_executable(benchmark_target benchmark/src/Benchmark.cpp)
add_subdirectory(benchmark/src)
target_link_libraries(benchmark_target PRIVATE benchmark_sources)
