//
// Created by mrypdm on 07.06.22.
//

#ifndef INCLUDE_DOCUMENT_HPP
#define INCLUDE_DOCUMENT_HPP

#include <list>
#include <Documents/DocumentEntry.hpp>
#include <DocumentReaders/IDocumentReader.hpp>
#include <DocumentWriters/IDocumentWriter.hpp>

class Document {
    std::list<DocumentEntry> _data;

    Document();
public:
    static Document CreateFrom(IDocumentReader& reader);

    void SaveTo(const IDocumentWriter& writer);
};

#endif // INCLUDE_DOCUMENT_HPP
