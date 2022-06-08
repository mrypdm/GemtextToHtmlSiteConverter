//
// Created by mrypdm on 07.06.22.
//

#ifndef INCLUDE_HTMLPARSER_HPP
#define INCLUDE_HTMLPARSER_HPP

#include <string>
#include <Documents/DocumentEntry.hpp>

class HtmlComposer {
    // html теги открытия и закртыия
    static std::map<DocumentEntryType, std::string> openTag;
    static std::map<DocumentEntryType, std::string> closeTag;

    std::string GetOpenTag(const DocumentEntry& tagType);
    std::string GetCloseTag(const DocumentEntry& tagType);

public:
    // Перевод вхождения в html текст
    std::string operator()(const DocumentEntry& entry);
};

#endif // INCLUDE_HTMLPARSER_HPP
