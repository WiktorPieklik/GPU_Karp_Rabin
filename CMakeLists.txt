cmake_minimum_required(VERSION 3.18)
project(gpu_karp_rabin CUDA)
set(CMAKE_CUDA_STANDARD 17)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)

add_executable(main main.cu)

add_subdirectory(src)

target_link_libraries(main PRIVATE sources text hash utility)

set_target_properties(main
        PROPERTIES
        CUDA_STANDARD 17
        CUDA_STANDARD_REQUIRED ON)
