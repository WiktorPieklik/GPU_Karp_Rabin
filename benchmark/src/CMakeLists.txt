add_library(benchmark_sources STATIC
            BenchmarkCase.cpp
            Benchmark.cpp)

target_include_directories(benchmark_sources PUBLIC ${PROJECT_SOURCE_DIR}/benchmark/header)
target_link_libraries(benchmark_sources PUBLIC stdc++fs)
