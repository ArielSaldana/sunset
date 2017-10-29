//
//  paragraph.hpp
//  MarkdownParser
//
//  Created by Ariel Saldana on 10/26/17.
//  Copyright © 2017 Ariel Saldana. All rights reserved.
//

#ifndef paragraph_hpp
#define paragraph_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include "json.h"
#include "Markup.hpp"

using nlohmann::json;

namespace Sunset {
    struct Paragraph {
        std::string id;
        std::string text;
        int type;
        std::vector<Sunset::Markup> markups;
    };
    void to_json(json& j, const Paragraph& p);
    void from_json(const json& j, Paragraph& p);
}
#endif /* paragraph_hpp */
