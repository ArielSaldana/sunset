// Content.cpp
// Copyright 2017 Ariel Saldana. All Rights Reserved.

#include "Content.hpp"

using Sunset::Content;

void Sunset::to_json(json &j, const Content& c) {
    j = json{
        {"title", c.title},
        {"description", c.description},
        {"link", c.link},
        {"img", c.img},
        {"layout", c.layout},
        {"tags", c.tags},
        {"bodyModel", c.bodyModel}
    };
}