// Markup.hpp
// Copyright 1998-2017 Ariel Saldana. All Rights Reserved.

#ifndef markup_hpp
#define markup_hpp
#pragma once

#include <string>
#include "json.h"

using nlohmann::json;

namespace mdm {
    struct Markup {
        int start;
        int end;
        int type;
        int anchorType;
        std::string rel;
        std::string href;
        std::string title;
    };
    void to_json(json& j, const Markup& m);
    void from_json(const json& j, Markup& m);
}

#endif /* markup_hpp */