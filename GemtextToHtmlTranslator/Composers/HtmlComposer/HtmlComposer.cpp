// Copyright 2022 mrypdm

#include <Composers/HtmlComposer/HtmlComposer.hpp>
#include <map>

std::map<DocumentEntryType, std::string> HtmlComposer::openTag = {
    {DocumentEntryType::Header, "<h1>"},
    {DocumentEntryType::SubHeader, "<h2>"},
    {DocumentEntryType::SubSubHeader, "<h3>"},
    {DocumentEntryType::ListOpen, "<ul>"},
    {DocumentEntryType::ListElement, "<li>"},
    {DocumentEntryType::PreformattedTextOpen, "<pre>"},
    {DocumentEntryType::Quotes, "<q>"}};

std::map<DocumentEntryType, std::string> HtmlComposer::closeTag = {
    {DocumentEntryType::Header, "</h1>"},
    {DocumentEntryType::SubHeader, "</h2>"},
    {DocumentEntryType::SubSubHeader, "</h3>"},
    {DocumentEntryType::Link, "</a>"},
    {DocumentEntryType::ListClose, "</ul>"},
    {DocumentEntryType::ListElement, "</li>"},
    {DocumentEntryType::PreformattedTextClose, "</pre>"},
    {DocumentEntryType::Quotes, "</q>"}};

std::string HtmlComposer::operator()(const DocumentEntry &entry) {
  return GetOpenTag(entry) + entry.GetText() + GetCloseTag(entry);
}

std::string HtmlComposer::GetOpenTag(const DocumentEntry &entry) {
  if (entry.GetType() == DocumentEntryType::Link) {
    return "<a href=\"" + entry.GetAttribute("href") + "\">";
  }
  return openTag.count(entry.GetType()) ? openTag.at(entry.GetType()) : "";
}

std::string HtmlComposer::GetCloseTag(const DocumentEntry &entry) {
  return closeTag.count(entry.GetType()) ? closeTag.at(entry.GetType()) : "";
}
