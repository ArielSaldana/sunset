// Markup.cpp
// Copyright 1998-2017 Ariel Saldana. All Rights Reserved.

#include "Markup.hpp"

using Sunset::Markup;

void Sunset::to_json(json& j, const Markup& m) {
    j = json{
        {"start", m.start},
        {"end", m.end},
        {"type", m.type},
    };

    // If the markup type is a link
    if (m.type == LINK) {
        j.emplace("anchorType", m.anchorType);
        j.emplace("rel", m.rel);
        j.emplace("href", m.href);
        j.emplace("title", m.title);
    }

}

void Sunset::from_json(const json& j, Markup& m) {
    m.start = j.at("start").get<int>();
    m.end = j.at("end").get<int>();
    m.type = j.at("type").get<int>();

    if (m.type == LINK) {
        m.anchorType = j.at("anchorType").get<int>();
        m.rel = j.at("rel").get<std::string>();
        m.href = j.at("href").get<std::string>();
        m.title = j.at("title").get<std::string>();
    }
}