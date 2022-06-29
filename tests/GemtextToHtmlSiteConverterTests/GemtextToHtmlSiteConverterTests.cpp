// Copyright 2022 mrypdm

#include <gtest/gtest.h>

#include <GemtextToHtmlSiteConverter.hpp>

namespace fs = std::filesystem;

bool ComparePaths(const fs::path &gemtextDirFilePath,
                  const fs::path &htmlDirFilePath) {
  auto lhsLocal = gemtextDirFilePath;
  if (gemtextDirFilePath.extension() == ".gmi" &&
      htmlDirFilePath.extension() == ".html") {
    lhsLocal.replace_extension(".html");
  }
  return lhsLocal == htmlDirFilePath;
}

std::vector<std::string> GetAllEntries(const fs::path &dir) {
  std::vector<std::string> res;

  for (const auto &entry : fs::recursive_directory_iterator(dir)) {
    res.push_back(entry.path().string().substr(dir.string().size()));
  }

  std::sort(res.begin(), res.end());

  return res;
}

bool CompareDirectories(const fs::path &gemtextDirectory,
                        const fs::path &htmlDirectory) {
  auto gemtextDirEntities = GetAllEntries(gemtextDirectory);
  auto htmlDirEntities = GetAllEntries(htmlDirectory);

  if (gemtextDirEntities.size() != htmlDirEntities.size()) return false;

  auto gemtextEntitiesIterator = gemtextDirEntities.begin();
  auto htmlEntitiesIterator = htmlDirEntities.begin();

  for (; gemtextEntitiesIterator != gemtextDirEntities.end();
       ++gemtextEntitiesIterator, ++htmlEntitiesIterator) {
    if (!ComparePaths(*gemtextEntitiesIterator, *htmlEntitiesIterator)) {
      return false;
    }
  }

  return true;
}

TEST(GemtextToHtmlSiteConverterTests, ConvertSite_Success) {
  ConvertSite("./misc/InputDirectory", "./misc/OutputDirectory");
  ASSERT_TRUE(
      CompareDirectories("./misc/InputDirectory", "./misc/OutputDirectory"));
}
