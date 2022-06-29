// Copyright 2022 mrypdm

#ifndef INCLUDE_IDOCUMENTWRITER_HPP
#define INCLUDE_IDOCUMENTWRITER_HPP

#include <Documents/DocumentEntry.hpp>
#include <filesystem>
#include <list>

struct IDocumentWriter {
  virtual void Write(const std::list<DocumentEntry>& data) const = 0;
  virtual ~IDocumentWriter() = default;
};

#endif  // INCLUDE_IDOCUMENTWRITER_HPP
