// Copyright 2022 mrypdm

#include <gtest/gtest.h>

#include <string>
#include <utils/string_utils.hpp>
#include <vector>

//
// Tests for TrimString
//

using StringPair = std::pair<std::string, std::string>;

class TrimStringTest : public testing::TestWithParam<StringPair> {};

std::vector<StringPair> TrimStringParams{
    {"\tSTRING\t", "STRING"},   {"\tSTRING\t\t", "STRING"},
    {"\tSTRING", "STRING"},     {"STRING\t", "STRING"},
    {" \t STRING ", "STRING"},  {"\tSTRING  \t", "STRING"},
    {"\t \t STRING", "STRING"}, {"STRING WITH SPACE", "STRING WITH SPACE"},
    {"STRING", "STRING"},
};

INSTANTIATE_TEST_SUITE_P(TrimStringTest, TrimStringTest,
                         testing::ValuesIn(TrimStringParams));

TEST_P(TrimStringTest, TrimStringTest) {
  StringPair pair = GetParam();

  auto res = TrimString(pair.first);

  ASSERT_EQ(res, pair.second);
}

//
// Tests for IsEmptyOrWhitespaces
//

using StringBoolPair = std::pair<std::string, bool>;

class IsEmptyOrWhitespacesTest : public testing::TestWithParam<StringBoolPair> {
};

std::vector<StringBoolPair> IsEmptyOrWhitespacesParams{
    {"", true},
    {" ", true},
    {"   ", true},
    {"\t", true},
    {"\t\t", true},
    {"\t ", true},
    {"\t  123\t ", false},
    {"\n", true},
    {"whitespace", false},
};

INSTANTIATE_TEST_SUITE_P(IsEmptyOrWhitespacesTest, IsEmptyOrWhitespacesTest,
                         testing::ValuesIn(IsEmptyOrWhitespacesParams));

TEST_P(IsEmptyOrWhitespacesTest, IsEmptyOrWhitespacesTest) {
  StringBoolPair pair = GetParam();

  auto res = IsEmptyOrWhitespaces(pair.first);

  ASSERT_EQ(res, pair.second);
}
