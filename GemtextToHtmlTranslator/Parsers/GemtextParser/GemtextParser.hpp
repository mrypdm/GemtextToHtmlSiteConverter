//
// Created by mrypdm on 07.06.22.
//

#ifndef INCLUDE_GEMTEXTPARSER_HPP
#define INCLUDE_GEMTEXTPARSER_HPP

#include <Documents/DocumentEntry.hpp>
#include <vector>

class GemtextParser {
    static std::vector<std::pair<std::string, DocumentEntryType>> entityTypes;

    DocumentEntry CreateLinkEntity(const std::string& innerText);

    // Тип вхождения для данного блока
    DocumentEntryType GetTypeForBlock(const std::string& blockText, std::string& innerText);

    // Чтение неформатированного блока
    DocumentEntry ParseUnformattedTextBlock(DocumentEntryType newEntryType, const std::string &blockText);

    // Чтение форматированного блока
    DocumentEntry ParseFormattedBlock(DocumentEntryType newEntryType, const std::string &innerText);
public:

    DocumentEntry operator()(const std::string& blockText, bool unformatted);
};

#endif // INCLUDE_GEMTEXTPARSER_HPP
