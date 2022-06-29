// Copyright 2022 mrypdm

#ifndef INCLUDE_IDOCUMENTFACTORY_HPP
#define INCLUDE_IDOCUMENTFACTORY_HPP

#include <Documents/DocumentEntry.hpp>
#include <list>

struct IDocumentReader {
  virtual std::list<DocumentEntry> Read() = 0;
  virtual ~IDocumentReader() = default;
};

#endif  // INCLUDE_IDOCUMENTFACTORY_HPP
