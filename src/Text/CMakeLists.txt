add_library(text STATIC
        PlainTextReader.cu
        TextFileReader.cu
        TextReaderFactory.cu)

target_include_directories(text PUBLIC ${PROJECT_SOURCE_DIR}/header/Text)

target_link_libraries(text PUBLIC stdc++fs)