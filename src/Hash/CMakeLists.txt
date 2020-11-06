add_library(hash STATIC
        StandardHash.cu
        Hash.cu)

target_include_directories(hash PUBLIC ${PROJECT_SOURCE_DIR}/header/Hash)
