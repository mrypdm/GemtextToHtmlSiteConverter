// Copyright 2022 mrypdm

#ifndef INCLUDE_GEMTEXTTOHTMLSITECONVERTER_HPP
#define INCLUDE_GEMTEXTTOHTMLSITECONVERTER_HPP

#include <filesystem>

void ConvertSite(const std::filesystem::path& gemtextSitePath,
                 const std::filesystem::path& htmlSitePath);

#endif  // INCLUDE_GEMTEXTTOHTMLSITECONVERTER_HPP
