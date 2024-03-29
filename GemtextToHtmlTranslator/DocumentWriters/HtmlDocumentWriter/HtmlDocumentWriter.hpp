// Copyright 2022 mrypdm

#ifndef INCLUDE_HTMLDOCUMENTWRITER_HPP
#define INCLUDE_HTMLDOCUMENTWRITER_HPP

#include <DocumentWriters/IDocumentWriter.hpp>
#include <list>

class HtmlDocumentWriter : public IDocumentWriter {
  std::filesystem::path _file;

 public:
  explicit HtmlDocumentWriter(const std::filesystem::path& file);

  void Write(const std::list<DocumentEntry>& data) const override;
};

#endif  // INCLUDE_HTMLDOCUMENTWRITER_HPP
