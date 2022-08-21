// Copyright 2022 mrypdm

#ifndef INCLUDE_DOCUMENT_HPP
#define INCLUDE_DOCUMENT_HPP

#include <DocumentReaders/IDocumentReader.hpp>
#include <DocumentWriters/IDocumentWriter.hpp>
#include <Documents/DocumentEntry.hpp>
#include <list>

class Document {
  std::list<DocumentEntry> _data;

  Document();

 public:
  static Document CreateFrom(IDocumentReader& reader);

  void SaveTo(IDocumentWriter& writer);
};

#endif  // INCLUDE_DOCUMENT_HPP
