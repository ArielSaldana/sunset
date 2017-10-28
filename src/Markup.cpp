// Markup.cpp
// Copyright 1998-2017 Ariel Saldana. All Rights Reserved.

#include "Markup.hpp"

using mdm::Markup;

void mdm::to_json(json& j, const Markup& m) {
    j = json{
        {"start", m.start},
        {"end", m.end},
        {"type", m.type},
        {"anchorType", m.anchorType},
        {"rel", m.rel},
        {"href", m.href},
        {"title", m.title}
    };
}

void mdm::from_json(const json& j, Markup& m) {
    m.start = j.at("start").get<int>();
    m.end = j.at("end").get<int>();
    m.type = j.at("type").get<int>();
    m.anchorType = j.at("anchorType").get<int>();
    m.rel = j.at("rel").get<std::string>();
    m.href = j.at("href").get<std::string>();
    m.title = j.at("title").get<std::string>();
}