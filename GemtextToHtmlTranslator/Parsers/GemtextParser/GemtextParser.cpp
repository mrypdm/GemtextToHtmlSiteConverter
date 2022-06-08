// Copyright 2022 mrypdm

#include <Parsers/GemtextParser/GemtextParser.hpp>
#include <string>
#include <utility>
#include <utils/string_utils.hpp>

std::vector<std::pair<std::string, DocumentEntryType>>
    GemtextParser::entityTypes{
        {"###", DocumentEntryType::SubSubHeader},
        {"##", DocumentEntryType::SubHeader},
        {"#", DocumentEntryType::Header},
        {"*", DocumentEntryType::ListElement},
        {"=>", DocumentEntryType::Link},
        {">", DocumentEntryType::Quotes},
        {"```", DocumentEntryType::PreformattedText},
    };

DocumentEntryType GemtextParser::GetTypeForBlock(const std::string &blockText,
                                                 std::string &innerText) {
  for (const auto &it : entityTypes) {
    // Если нашли в самом начале, а не где-то в центре
    if (blockText.find(it.first) == 0) {
      // Внутренний текст блока
      innerText = TrimString(blockText.substr(it.first.size()));
      return it.second;
    }
  }

  innerText = blockText;
  return DocumentEntryType::Text;
}

DocumentEntry GemtextParser::ParseUnformattedTextBlock(
    DocumentEntryType newEntryType, const std::string &blockText) {
  // Если ```,  то закрываем блок
  if (newEntryType == DocumentEntryType::PreformattedText) {
    return DocumentEntry(DocumentEntryType::PreformattedTextClose);
  }
  // Иначе значит, что еще не вышли из блока => просто текст
  DocumentEntry newEntry(DocumentEntryType::Text, blockText);
  return newEntry;
}

DocumentEntry GemtextParser::CreateLinkEntity(const std::string &innerText) {
  auto firstSpace = innerText.find_first_of(" \t");

  auto href = innerText.substr(0, firstSpace);

  DocumentEntry newLink(DocumentEntryType::Link);
  newLink.SetAttribute("href", href);

  // Если нет текста ссылки, то ставим адрес
  if (firstSpace != std::string::npos) {
    newLink.SetText(TrimString(innerText.substr(firstSpace)));
  } else {
    newLink.SetText(href);
  }

  return newLink;
}

DocumentEntry GemtextParser::ParseFormattedBlock(DocumentEntryType newEntryType,
                                                 const std::string &innerText) {
  if (newEntryType == DocumentEntryType::Link) {
    return CreateLinkEntity(innerText);
    // Общий случай неформатированного блока заменяем на частный
  } else if (newEntryType == DocumentEntryType::PreformattedText) {
    return DocumentEntry(DocumentEntryType::PreformattedTextOpen);
  }
  // Для всех остальных случаев ставим только текст
  DocumentEntry newEntry(newEntryType, innerText);
  return newEntry;
}

DocumentEntry GemtextParser::operator()(const std::string &blockText,
                                        bool unformatted) {
  std::string innerText;
  auto entryType = GetTypeForBlock(TrimString(blockText), innerText);

  if (unformatted) {
    return ParseUnformattedTextBlock(entryType, blockText);
  }

  return ParseFormattedBlock(entryType, innerText);
}
