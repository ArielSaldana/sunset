// Parser.hpp
// Copyright 1998-2017 Ariel Saldana. All Rights Reserved.

#ifndef parser_hpp
#define parser_hpp
#pragma once

#include <fstream>
#include <sstream>
#include <regex>
#include <string>
#include <vector>
#include <stack>
#include <deque>
#include "Paragraph.hpp"
#include "BodyModel.hpp"
#include "Markup.hpp"
#include "Rule.hpp"

#define H1_REGEX "^#\\s.+"
#define H2_REGEX "^#{2}\\s.+"
#define H3_REGEX "^#{3}\\s.+"
#define H4_REGEX "^#{4}\\s.+"
#define H5_REGEX "^#{5}\\s.+"
#define H6_REGEX "^#{6}\\s.+"
#define ULOL_REGEX "^(\\*|-)\\s.+"
//#define P_REGEX "^[^(\\-#*)].*"
#define P_REGEX "^(\\w+|\\*{1,2}).+"
#define CODEBLOCK_REGEX "`{3}.*"

class Parser {
public:
    std::vector<Rule> rules;
    mdbm::BodyModel bodyModel;
    std::map<int, std::regex> regexMap;
    std::ifstream myReadFile;
    std::vector<std::string> lines;

    Parser() : rules{
        {1, std::regex(H1_REGEX)},
        {2, std::regex(H2_REGEX)},
        {3, std::regex(H3_REGEX)},
        {4, std::regex(H4_REGEX)},
        {5, std::regex(H5_REGEX)},
        {7, std::regex(H6_REGEX)},
        {9, std::regex(ULOL_REGEX)},
        {8, std::regex(CODEBLOCK_REGEX), true, true},
        {6, std::regex(P_REGEX), true},
        // {6, std::regex(".*"), true},
    } {}

    void loadFile(const std::string file);
    void preprocessFile();
    void process(std::vector<std::string> const &lines, int index, int length, mdp::Paragraph *p);
    void processLine(mdp::Paragraph &paragraph);
};

#endif // parser_hpp