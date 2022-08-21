// Copyright 2022 mrypdm

#include <gtest/gtest.h>

#include <DocumentWriters/HtmlDocumentWriter/HtmlDocumentWriter.hpp>
#include <Documents/DocumentEntry.hpp>
#include <fstream>
#include <list>

bool compare_files(const std::string& lhs, const std::string& rhs) {
  std::ifstream f1(lhs, std::ifstream::binary | std::ifstream::ate);
  std::ifstream f2(rhs, std::ifstream::binary | std::ifstream::ate);

  if (f1.fail() || f2.fail()) {
    return false;
  }

  if (f1.tellg() != f2.tellg()) {
    return false;
  }

  f1.seekg(0, std::ifstream::beg);
  f2.seekg(0, std::ifstream::beg);
  return std::equal(std::istreambuf_iterator<char>(f1.rdbuf()),
                    std::istreambuf_iterator<char>(),
                    std::istreambuf_iterator<char>(f2.rdbuf()));
}

TEST(HtmlDocumentWriterTests, WriteToDirectory_ShouldThrow) {
  ASSERT_THROW(HtmlDocumentWriter writer("./misc"), std::invalid_argument);
}

TEST(HtmlDocumentWriterTests, WriteFile_Success) {
  HtmlDocumentWriter writer("./misc/html_result.html");
  std::list<DocumentEntry> data{
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

  writer.Write(data);

  ASSERT_TRUE(
      compare_files("./misc/html_result.html", "./misc/html_etalon.html"));
}
