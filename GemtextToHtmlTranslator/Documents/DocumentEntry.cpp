// Copyright 2022 mrypdm

#include <Documents/DocumentEntry.hpp>
#include <stdexcept>
#include <string>
#include <utility>

std::string DocumentEntry::GetAttribute(const std::string &key) const {
  return _attributes.at(key);
}

DocumentEntry &DocumentEntry::SetAttribute(const std::string &key,
                                           std::string value) {
  _attributes[key] = std::move(value);
  return *this;
}

std::string DocumentEntry::GetText() const { return _text; }

void DocumentEntry::SetText(std::string text) { _text = std::move(text); }

DocumentEntryType DocumentEntry::GetType() const { return _type; }

DocumentEntry::DocumentEntry(DocumentEntryType type, std::string text)
    : _type(type), _text(std::move(text)) {}
