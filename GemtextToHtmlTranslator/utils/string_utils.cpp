// Copyright 2022 mrypdm

#include <regex>
#include <utils/string_utils.hpp>

bool IsEmptyOrWhitespaces(const std::string &str) {
  auto empty = str.empty();
  auto whitespaces = str.find_first_not_of(" \t\r\n") == std::string::npos;

  return empty || whitespaces;
}

std::string TrimString(const std::string &str) {
  static std::regex regular("^\\s*(.*?)\\s*$");
  std::smatch result;

  std::regex_match(str, result, regular);
  return result[1];
}
