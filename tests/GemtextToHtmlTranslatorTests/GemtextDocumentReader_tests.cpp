// Copyright 2022 mrypdm

#include <gtest/gtest.h>

#include <DocumentReaders/GemtextDocumentReader/GemtextDocumentReader.hpp>
#include <Documents/DocumentEntry.hpp>
#include <list>

TEST(GemtextDocumentReaderTests, InvalidConstructorParams_ShouldThrow) {
  ASSERT_THROW(GemtextDocumentReader("./misc"), std::invalid_argument);
  ASSERT_THROW(GemtextDocumentReader("./misc/dont_exists.gmi"),
               std::invalid_argument);
}

TEST(GemtextDocumentReaderTests, ReadFile_Success) {
  GemtextDocumentReader reader("./misc/gemtext_etalon.gmi");
  std::list<DocumentEntry> ans{
      DocumentEntry(DocumentEntryType::Header, "Header"),
      DocumentEntry(DocumentEntryType::ListOpen),
      DocumentEntry(DocumentEntryType::ListElement, "one item"),
      DocumentEntry(DocumentEntryType::ListElement, "two item"),
      DocumentEntry(DocumentEntryType::ListClose),
      DocumentEntry(DocumentEntryType::PreformattedTextOpen),
      DocumentEntry(DocumentEntryType::Text, "=> list.com unformatted link"),
      DocumentEntry(DocumentEntryType::Text, "## unform subheader"),
      DocumentEntry(DocumentEntryType::PreformattedTextClose),
      DocumentEntry(DocumentEntryType::Link, "form link")
          .SetAttribute("href", "list.com"),
      DocumentEntry(DocumentEntryType::SubHeader, "form subheader"),
      DocumentEntry(DocumentEntryType::Quotes, "last quote"),
  };

  auto res = reader.Read();

  ASSERT_EQ(res.size(), ans.size());

  auto res_it = res.begin();
  auto ans_it = ans.begin();

  for (; res_it != res.end(); ++res_it, ++ans_it) {
    ASSERT_EQ(res_it->GetType(), ans_it->GetType());
    ASSERT_EQ(res_it->GetText(), ans_it->GetText());
    if (ans_it->GetType() == DocumentEntryType::Link) {
      ASSERT_EQ(res_it->GetAttribute("href"), ans_it->GetAttribute("href"));
    }
  }
}
