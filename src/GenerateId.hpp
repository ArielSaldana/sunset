#ifndef generate_id_hpp
#define generate_id_hpp
#pragma once

#include <string>

namespace Sunset {
    static std::string random_string( size_t length )
    {
        auto randchar = []() -> char
        {
            const char charset[] =
            "0123456789"
            "abcdefghijklmnopqrstuvwxyz";
            const size_t max_index = (sizeof(charset) - 1);
            return charset[ rand() % max_index ];
        };
        std::string str(length,0);
        std::generate_n( str.begin(), length, randchar );
        return str;
    }
}
#endif