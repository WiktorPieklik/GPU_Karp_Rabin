add_library(hash STATIC
        StandardHash.cpp
        Hash.cpp)

target_include_directories(hash PUBLIC ${PROJECT_SOURCE_DIR}/main/header/Hash)
