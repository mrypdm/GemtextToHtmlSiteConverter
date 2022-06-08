// Copyright 2022 mrypdm

#include <string>
#include <algorithm>
#include <DocumentReaders/GemtextDocumentReader/GemtextDocumentReader.hpp>
#include <DocumentWriters/HtmlDocumentWriter/HtmlDocumentWriter.hpp>
#include <Documents/Document.hpp>
#include <GemtextToHtmlSiteConverter.hpp>

using std::filesystem::directory_iterator;
using std::filesystem::exists;
using std::filesystem::is_directory;
using std::filesystem::is_regular_file;
using std::filesystem::path;

static void CopyFile(const path &fromFile, const path &toFile) {
  if (exists(toFile)) return;

  if (fromFile.extension() == ".gmi") {
    auto toFileLocal = toFile;
    GemtextDocumentReader reader(fromFile);
    HtmlDocumentWriter writer(toFileLocal.replace_extension(".html"));
    auto doc = Document::CreateFrom(reader);
    doc.SaveTo(writer);
  } else {
    std::filesystem::copy(fromFile, toFile);
  }
}

static void CopyDirectory(const path &fromDir, const path &toDir) {
  if (!exists(toDir)) {
    std::filesystem::create_directory(toDir);
  }

  for (const auto &entry : directory_iterator(fromDir)) {
    if (is_directory(entry)) {
      CopyDirectory(entry, toDir / entry.path().filename());
    } else if (is_regular_file(entry)) {
      CopyFile(entry, toDir / entry.path().filename());
    }
  }
}

void ConvertSite(const std::filesystem::path &gemtextSitePath,
                 const std::filesystem::path &htmlSitePath) {
  if (!exists(gemtextSitePath)) {
    throw std::invalid_argument("'" + gemtextSitePath.string() +
                                "' doesn't exists");
  }

  if (!is_directory(gemtextSitePath)) {
    throw std::invalid_argument("'" + gemtextSitePath.string() +
                                "' is not a directory");
  }

  if (exists(htmlSitePath) && !is_directory(htmlSitePath)) {
    throw std::invalid_argument("'" + htmlSitePath.string() +
                                "' exists but it is not a directory");
  }

  CopyDirectory(gemtextSitePath, htmlSitePath);
}
