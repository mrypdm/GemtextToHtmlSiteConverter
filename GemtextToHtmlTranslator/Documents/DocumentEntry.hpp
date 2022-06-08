//
// Created by mrypdm on 07.06.22.
//

#ifndef INCLUDE_DOCUMENTENTRY_HPP
#define INCLUDE_DOCUMENTENTRY_HPP

#include <map>

enum DocumentEntryType {
    Text,
    Header,
    SubHeader,
    SubSubHeader,
    Link,
    ListElement,
    Quotes,
    ListOpen,
    ListClose,
    PreformattedText,
    PreformattedTextOpen,
    PreformattedTextClose,
};

class DocumentEntry {
    DocumentEntryType _type;
    std::string _text;
    std::map<std::string, std::string> _attributes;

public:
    explicit DocumentEntry(DocumentEntryType type, std::string text = "");

    [[nodiscard]] std::string GetAttribute(const std::string &key) const;

    DocumentEntry &SetAttribute(const std::string &key, std::string value);

    [[nodiscard]] std::string GetText() const;

    void SetText(std::string text);

    [[nodiscard]] DocumentEntryType GetType() const;
};

#endif // INCLUDE_DOCUMENTENTRY_HPP
