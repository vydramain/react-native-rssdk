#pragma once

#include "./json.h"

namespace Json {
    static bool parseFromStream(
        CharReader::Factory const& fact,
        char const* begin, size_t length,
        Value* root, std::string* errs)
    {
        char const* end = begin + length;
        std::unique_ptr<CharReader> const reader(fact.newCharReader());
        return reader->parse(begin, end, root, errs);
    }
}
