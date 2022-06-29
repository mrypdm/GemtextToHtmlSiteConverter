cmake_minimum_required(VERSION 3.18)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(GemtextToHtmlTranslatorTests)
string(APPEND CMAKE_CXX_FLAGS " -pedantic -Werror -Wall -Wextra")
string(APPEND CMAKE_CXX_FLAGS " -Wno-unused-command-line-argument")
string(APPEND CMAKE_CXX_FLAGS " -Wshadow -Wnon-virtual-dtor")

hunter_add_package(GTest)
find_package(GTest CONFIG REQUIRED)

add_executable(${PROJECT_NAME}
        string_utils_tests.cpp
        GemtextParser_tests.cpp
        HtmlComposer_tests.cpp
        HtmlDocumentWriter_tests.cpp
        GemtextDocumentReader_tests.cpp)

target_link_libraries(${PROJECT_NAME} GemtextToHtmlTranslator GTest::gtest_main)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

file(COPY misc DESTINATION ${CMAKE_CURRENT_BINARY_DIR})