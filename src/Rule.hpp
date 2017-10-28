// Type.hpp
// Copyright 1998-2017 Ariel Saldana. All Rights Reserved.

#ifndef rule_hpp
#define rule_hpp
#pragma once

#include <regex>

struct Rule {
    //Rule(int id, std::regex r) : id(id), 
    int id;
    std::regex reg;
    bool multiline;
    bool fenced;
};

#endif