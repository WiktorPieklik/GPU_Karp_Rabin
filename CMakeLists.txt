cmake_minimum_required(VERSION 3.14)
project(gpu_karp_rabin VERSION 1.0)
set(CMAKE_CXX_STANDARD 20)


add_executable(main main.cpp)

add_compile_options(-Wall -Wextra -Wpedantic)

add_subdirectory(src)

target_link_libraries(main PRIVATE sources text hash utility)
