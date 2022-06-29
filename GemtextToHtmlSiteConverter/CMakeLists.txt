cmake_minimum_required(VERSION 3.18)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(GemtextToHtmlSiteConverter)
string(APPEND CMAKE_CXX_FLAGS " -pedantic -Werror -Wall -Wextra")
string(APPEND CMAKE_CXX_FLAGS " -Wno-unused-command-line-argument")
string(APPEND CMAKE_CXX_FLAGS " -Wshadow -Wnon-virtual-dtor")

add_library(${PROJECT_NAME} SHARED
        GemtextToHtmlSiteConverter.hpp
        GemtextToHtmlSiteConverter.cpp)

target_link_libraries(${PROJECT_NAME} GemtextToHtmlTranslator)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
