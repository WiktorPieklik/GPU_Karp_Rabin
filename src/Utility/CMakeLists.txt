add_library(utility STATIC
        TextSplitter.cu)

target_include_directories(utility PUBLIC ${PROJECT_SOURCE_DIR}/header/Utility)
