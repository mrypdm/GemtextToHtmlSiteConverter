// Copyright 2022 mrypdm

#include <gtest/gtest.h>

#include <Composers/HtmlComposer/HtmlComposer.hpp>
#include <Documents/DocumentEntry.hpp>
#include <string>

//
// Tests for HtmlComposer
//

using EntryStringPair = std::pair<DocumentEntry, std::string>;

class HtmlComposerTests : public testing::TestWithParam<EntryStringPair> {};

std::vector<EntryStringPair> HtmlComposerParams{
    {DocumentEntry(DocumentEntryType::Text, "Text"), "Text"},
    {DocumentEntry(DocumentEntryType::Header, "Header"), "<h1>Header</h1>"},
    {DocumentEntry(DocumentEntryType::SubHeader, "Header2"),
     "<h2>Header2</h2>"},
    {DocumentEntry(DocumentEntryType::SubSubHeader, "Header3"),
     "<h3>Header3</h3>"},
    {DocumentEntry(DocumentEntryType::SubHeader, "#\t Header2"),
     "<h2>#\t Header2</h2>"},
    {DocumentEntry(DocumentEntryType::Quotes, "Citata"), "<q>Citata</q>"},
    {DocumentEntry(DocumentEntryType::ListElement, "list one"),
     "<li>list one</li>"},
    {DocumentEntry(DocumentEntryType::Link, "link header")
         .SetAttribute("href", "link.com"),
     "<a href=\"link.com\">link header</a>"},
    {DocumentEntry(DocumentEntryType::PreformattedTextOpen), "<pre>"},
    {DocumentEntry(DocumentEntryType::PreformattedTextClose), "</pre>"},
    {DocumentEntry(DocumentEntryType::ListOpen), "<ul>"},
    {DocumentEntry(DocumentEntryType::ListClose), "</ul>"},
};

INSTANTIATE_TEST_SUITE_P(HtmlComposerTests, HtmlComposerTests,
                         testing::ValuesIn(HtmlComposerParams));

TEST_P(HtmlComposerTests, HtmlComposerTests) {
  EntryStringPair pair = GetParam();
  HtmlComposer composer;

  auto res = composer(pair.first);

  ASSERT_EQ(res, pair.second);
}
