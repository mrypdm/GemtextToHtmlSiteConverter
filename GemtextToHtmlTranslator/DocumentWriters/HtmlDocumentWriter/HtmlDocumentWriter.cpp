// Copyright 2022 mrypdm

#include <Composers/HtmlComposer/HtmlComposer.hpp>
#include <DocumentWriters/HtmlDocumentWriter/HtmlDocumentWriter.hpp>
#include <fstream>
#include <list>
#include <string>

void HtmlDocumentWriter::Write(const std::list<DocumentEntry>& data) const {
  std::ofstream output(_file);

  HtmlComposer composer;

  output << "<html>" << std::endl
         << "<head></head>" << std::endl
         << "<body>" << std::endl;
  for (const auto& entry : data) {
    output << composer(entry) << std::endl;
  }
  output << "</body>" << std::endl << "</html>" << std::endl;
}

HtmlDocumentWriter::HtmlDocumentWriter(const std::filesystem::path& file) {
  if (std::filesystem::exists(file) &&
      !std::filesystem::is_regular_file(file)) {
    throw std::invalid_argument("Path '" + file.string() +
                                "' exists and it is not a file");
  }

  _file = file;
}
