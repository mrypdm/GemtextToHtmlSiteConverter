//
// Created by mrypdm on 07.06.22.
//

#ifndef INCLUDE_IDOCUMENTFACTORY_HPP
#define INCLUDE_IDOCUMENTFACTORY_HPP

#include <list>
#include <Documents/DocumentEntry.hpp>

struct IDocumentReader {
    virtual std::list<DocumentEntry> Read() = 0;
    virtual ~IDocumentReader() = default;
};

#endif // INCLUDE_IDOCUMENTFACTORY_HPP
