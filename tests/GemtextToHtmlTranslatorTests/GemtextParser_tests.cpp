// Copyright 2022 mrypdm

#include <gtest/gtest.h>

#include <Documents/DocumentEntry.hpp>
#include <Parsers/GemtextParser/GemtextParser.hpp>
#include <vector>

//
// Tests for GemtextParser
//

struct GemtextParserParam {
  std::string BlockText;
  bool Formatted;
  DocumentEntry Result;
};

class GemtextParserTests : public testing::TestWithParam<GemtextParserParam> {};

std::vector<GemtextParserParam> GemtextParserParams{
    {"Text", true, DocumentEntry(DocumentEntryType::Text, "Text")},
    {"#\t Header", true, DocumentEntry(DocumentEntryType::Header, "Header")},
    {" \t##\t\t Header2", true,
     DocumentEntry(DocumentEntryType::SubHeader, "Header2")},
    {" \t###\t\t Header3", true,
     DocumentEntry(DocumentEntryType::SubSubHeader, "Header3")},
    {" \t##\t#\t Header2\t ", true,
     DocumentEntry(DocumentEntryType::SubHeader, "#\t Header2")},
    {">Citata", true, DocumentEntry(DocumentEntryType::Quotes, "Citata")},
    {"*list one", true,
     DocumentEntry(DocumentEntryType::ListElement, "list one")},
    {"=>link.com link header", true,
     DocumentEntry(DocumentEntryType::Link, "link header")
         .SetAttribute("href", "link.com")},
    {"```", true, DocumentEntry(DocumentEntryType::PreformattedTextOpen)},

    {"```", false, DocumentEntry(DocumentEntryType::PreformattedTextClose)},
    {"Text", false, DocumentEntry(DocumentEntryType::Text, "Text")},
    {"#\t Header", false, DocumentEntry(DocumentEntryType::Text, "#\t Header")},
    {" \t##\t\t Header2", false,
     DocumentEntry(DocumentEntryType::Text, " \t##\t\t Header2")},
    {">Citata", false, DocumentEntry(DocumentEntryType::Text, ">Citata")},
    {"*list one", false, DocumentEntry(DocumentEntryType::Text, "*list one")},
    {"=>link.com link header", false,
     DocumentEntry(DocumentEntryType::Text, "=>link.com link header")},
};

INSTANTIATE_TEST_SUITE_P(GemtextParserTests, GemtextParserTests,
                         testing::ValuesIn(GemtextParserParams));

TEST_P(GemtextParserTests, GemtextParserTests) {
  GemtextParserParam param = GetParam();
  GemtextParser parser;

  auto res = parser(param.BlockText, !param.Formatted);

  ASSERT_EQ(res.GetType(), param.Result.GetType());
  ASSERT_EQ(res.GetText(), param.Result.GetText());

  if (param.Result.GetType() == DocumentEntryType::Link) {
    ASSERT_EQ(res.GetAttribute("href"), param.Result.GetAttribute("href"));
  }
}
