// Copyright 2022 mrypdm

#include <DocumentReaders/GemtextDocumentReader/GemtextDocumentReader.hpp>
#include <Parsers/GemtextParser/GemtextParser.hpp>
#include <fstream>
#include <list>
#include <string>
#include <utility>
#include <utils/string_utils.hpp>

void GemtextDocumentReader::CheckListBlock(const DocumentEntry &entry) {
  // Если только вошли в список, то ставим вхождение открытия списка
  if (entry.GetType() == DocumentEntryType::ListElement) {
    auto prevEntryType = _data.back().GetType();
    if (prevEntryType != DocumentEntryType::ListOpen &&
        prevEntryType != DocumentEntryType::ListElement) {
      _data.emplace_back(DocumentEntryType::ListOpen);
      inListBlock = true;
    }
    // Если вхождение - не элемент списка, то закрываем список (т.к. Gemtext не
    // поддерживает вложенные списки)
  } else if (inListBlock) {
    inListBlock = false;
    _data.emplace_back(DocumentEntryType::ListClose);
  }
}

void GemtextDocumentReader::CheckPreformattedTextBlock(
    const DocumentEntry &entry) {
  if (entry.GetType() == DocumentEntryType::PreformattedTextOpen) {
    inPreformattedTextBlock = true;
  } else if (entry.GetType() == DocumentEntryType::PreformattedTextClose) {
    inPreformattedTextBlock = false;
  }
}

std::list<DocumentEntry> GemtextDocumentReader::Read() {
  _data.clear();

  std::ifstream input(_file);

  if (!input)
    throw std::ifstream::failure("Can not open file '" + _file.string() + "'");

  GemtextParser parser;

  std::string currentBlock;

  while (!input.eof()) {
    std::getline(input, currentBlock);

    if (IsEmptyOrWhitespaces(currentBlock)) continue;

    auto newEntry = parser(currentBlock, inPreformattedTextBlock);

    CheckPreformattedTextBlock(newEntry);

    CheckListBlock(newEntry);

    _data.push_back(std::move(newEntry));
  }

  // Если последний элемент был списком, то закрываем список
  // т.к. у ``` есть пара, то он точно будет закрыт, поэтому этот случай не
  // проверяем
  if (inListBlock) {
    inListBlock = false;
    _data.emplace_back(DocumentEntryType::ListClose);
  }

  return _data;
}

GemtextDocumentReader::GemtextDocumentReader(
    const std::filesystem::path &file) {
  if (!std::filesystem::exists(file)) {
    throw std::invalid_argument("Path '" + file.string() + "' doesn't exist");
  }

  if (!std::filesystem::is_regular_file(file)) {
    throw std::invalid_argument("Path '" + file.string() + "' is not a file");
  }

  _file = file;
}
