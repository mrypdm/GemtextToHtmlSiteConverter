cmake_minimum_required(VERSION 3.18)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_CPPLINT cpplint;
        --filter=-build/c++11,-runtime/references,-whitespace/braces,-whitespace/indent,-whitespace/comments,-build/include_order;
        --quiet)

include("cmake/HunterGate.cmake")

HunterGate(
        URL "https://github.com/cpp-pm/hunter/archive/v0.23.314.tar.gz"
        SHA1 "95c47c92f68edb091b5d6d18924baabe02a6962a"
)

add_subdirectory(GemtextToHtmlTranslator)
add_subdirectory(GemtextToHtmlSiteConverter)
add_subdirectory(exe)

project(GemtextToHtmlConverter)
string(APPEND CMAKE_CXX_FLAGS " -pedantic -Werror -Wall -Wextra")
string(APPEND CMAKE_CXX_FLAGS " -Wno-unused-command-line-argument")
string(APPEND CMAKE_CXX_FLAGS " -Wshadow -Wnon-virtual-dtor")

enable_testing()
add_subdirectory(tests)
