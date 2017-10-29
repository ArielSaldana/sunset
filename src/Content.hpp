// Content.hpp
// Copyright 2017 Ariel Saldana. All Rights Reserved.

#ifndef content_hpp
#define content_hpp
#pragma once

#include <string>
#include <vector>
#include "BodyModel.hpp"
#include "json.h"
#include <unordered_map>

using nlohmann::json;

namespace Sunset {
    class Content {
    public:
        std::string title;
        std::string description;
        std::string link;
        std::string img;
        std::string layout;
        std::string category;
        std::vector<std::string> tags;
        Sunset::BodyModel bodyModel;
    };
    void to_json(json& j, const Content& c);
    void from_json(const json& j, Content& p);
}

#endif /* content_hpp */