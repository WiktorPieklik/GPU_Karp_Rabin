add_subdirectory(Hash)
add_subdirectory(Text)
add_subdirectory(Utility)
add_library(sources STATIC
        RabinKarpSearch.cpp)


target_include_directories(sources PUBLIC ${PROJECT_SOURCE_DIR}/header)

target_link_libraries(sources hash text utility)
