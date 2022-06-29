// Copyright 2022 mrypdm

#include <GemtextToHtmlSiteConverter.hpp>

int main(int argc, const char **argv) {
    if (argc < 3)
        return 1;

    ConvertSite(argv[1], argv[2]);
}
