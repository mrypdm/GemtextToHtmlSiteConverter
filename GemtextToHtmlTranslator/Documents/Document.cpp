// Copyright 2022 mrypdm

#include <Documents/Document.hpp>

Document Document::CreateFrom(IDocumentReader &reader) {
    Document doc;
    doc._data = reader.Read();
    return doc;
}

void Document::SaveTo(const IDocumentWriter &writer) {
    writer.Write(_data);
}

Document::Document() = default;
