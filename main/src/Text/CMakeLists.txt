add_library(text STATIC
        PlainTextReader.cpp
        TextFileReader.cpp
        TextReaderFactory.cpp)

target_include_directories(text PUBLIC ${PROJECT_SOURCE_DIR}/main/header/Text)

target_link_libraries(text PUBLIC stdc++fs)
