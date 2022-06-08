//
// Created by mrypdm on 07.06.22.
//

#ifndef INCLUDE_IDOCUMENTWRITER_HPP
#define INCLUDE_IDOCUMENTWRITER_HPP

#include <filesystem>
#include <list>
#include <Documents/DocumentEntry.hpp>

struct IDocumentWriter {
    virtual void Write(const std::list<DocumentEntry>& data) const = 0;
    virtual ~IDocumentWriter() = default;
};

#endif // INCLUDE_IDOCUMENTWRITER_HPP
