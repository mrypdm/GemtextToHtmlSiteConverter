// Copyright 2022 mrypdm

#ifndef INCLUDE_GEMTEXTDOCUMENTFACTORY_HPP
#define INCLUDE_GEMTEXTDOCUMENTFACTORY_HPP

#include <DocumentReaders/IDocumentReader.hpp>
#include <filesystem>
#include <list>

class GemtextDocumentReader : public IDocumentReader {
  std::filesystem::path _file;

  // Проверка на вход/выход блока списка
  void CheckListBlock(const DocumentEntry& entry);

  // Проверка на вход/выход из блока неформат. текста
  void CheckPreformattedTextBlock(const DocumentEntry& entry);

  // Находимя ли в блоке неформатированного текста
  bool inPreformattedTextBlock = false;

  // Находимся ли в списке
  bool inListBlock = false;

  // Результат чтения
  std::list<DocumentEntry> _data;

 public:
  explicit GemtextDocumentReader(const std::filesystem::path& file);

  std::list<DocumentEntry> Read() override;
};

#endif  // INCLUDE_GEMTEXTDOCUMENTFACTORY_HPP
