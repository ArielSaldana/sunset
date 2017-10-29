//
//  paragraph.cpp
//  MarkdownParser
//
//  Created by Ariel Saldana on 10/26/17.
//  Copyright © 2017 Ariel Saldana. All rights reserved.
//

#include "Paragraph.hpp"

using Sunset::Paragraph;

void Sunset::to_json(json& j, const Paragraph& p) {
    j = json{
        {"id", p.id}, 
        {"text", p.text}, 
        {"type", p.type},
        {"markups", p.markups}
    };
}

void Sunset::from_json(const json& j, Paragraph& p) {
    p.id = j.at("id").get<std::string>();
    p.text = j.at("text").get<std::string>();
    p.type = j.at("type").get<int>();
    p.markups = j.at("markups").get<std::vector<Sunset::Markup>>();
}

