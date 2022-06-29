cmake_minimum_required(VERSION 3.18)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(GemtextToHtmlTranslator)
string(APPEND CMAKE_CXX_FLAGS " -pedantic -Werror -Wall -Wextra")
string(APPEND CMAKE_CXX_FLAGS " -Wno-unused-command-line-argument")
string(APPEND CMAKE_CXX_FLAGS " -Wshadow -Wnon-virtual-dtor")

add_library(${PROJECT_NAME} SHARED
        Documents/DocumentEntry.hpp
        Documents/DocumentEntry.cpp

        Documents/Document.hpp
        Documents/Document.cpp

        Composers/HtmlComposer/HtmlComposer.hpp
        Composers/HtmlComposer/HtmlComposer.cpp

        Parsers/GemtextParser/GemtextParser.hpp
        Parsers/GemtextParser/GemtextParser.cpp

        utils/string_utils.hpp
        utils/string_utils.cpp

        DocumentReaders/IDocumentReader.hpp
        DocumentWriters/IDocumentWriter.hpp

        DocumentReaders/GemtextDocumentReader/GemtextDocumentReader.hpp
        DocumentReaders/GemtextDocumentReader/GemtextDocumentReader.cpp

        DocumentWriters/HtmlDocumentWriter/HtmlDocumentWriter.hpp
        DocumentWriters/HtmlDocumentWriter/HtmlDocumentWriter.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
