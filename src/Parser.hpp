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
#include <dirent.h>
#include "Paragraph.hpp"
#include "BodyModel.hpp"
#include "Content.hpp"
#include "Markup.hpp"
#include "Rule.hpp"
#include "yaml-cpp/yaml.h"

#define H1_REGEX "^#\\s.+"
#define H2_REGEX "^#{2}\\s.+"
#define H3_REGEX "^#{3}\\s.+"
#define H4_REGEX "^#{4}\\s.+"
#define H5_REGEX "^#{5}\\s.+"
#define H6_REGEX "^#{6}\\s.+"
#define UL_REGEX "^(\\*|-)\\s.+"
#define OL_REGEX "^\\d\\.\\s.+"
#define IMG_REGEX "^!\\[.*?\\]\\(.+\\)"
#define P_REGEX "[^\n]+"
#define CODEBLOCK_REGEX "`{3}.*"

namespace Sunset{
    class Parser {
    public:
        std::vector<Rule> rules;
        std::map<int, std::regex> regexMap;
        
        std::vector<Sunset::Content> content;
        enum StringValue { 
            title,
            description,
            link,
            img,
            category,
            layout
        };
        std::map<std::string, StringValue> values;
        
        Parser() : rules{
            {1, std::regex(H1_REGEX)},
            {2, std::regex(H2_REGEX)},
            {3, std::regex(H3_REGEX)},
            {4, std::regex(H4_REGEX)},
            {5, std::regex(H5_REGEX)},
            {7, std::regex(H6_REGEX)},
            {9, std::regex(UL_REGEX)},
            {10, std::regex(OL_REGEX)},
            {11, std::regex(IMG_REGEX)},
            {8, std::regex(CODEBLOCK_REGEX), true, true},
            {6, std::regex(P_REGEX), true},
            // {6, std::regex(".*"), true},
        }, values{
            {"title", title},
            {"description", description},
            {"link", link},
            {"img", img},
            {"category", category},
            {"layout", layout},
        } {}

        Sunset::Content loadFile(const std::string file);
        /**
         * @method  {getFileJson} Gets the Json value from a single or multiple files
         * @param   {std::string} file - vector to push any Markdown syntax onto for parsing.
         * @param   {bool} directory - vector to push any YAML syntax onto for parsing.
         * @return  {json} the json value
         */
        json getFileJson(const std::string file);
        json getFileJson(const std::string file, bool directory);

        /**
         * Proprocess the file. Checks if the file has YAML syntax to parse.
         * @param {std::ifstream&} myReadFile the address of the file being read
         * @param {std::vector<std::string>&} lines vector to push any Markdown syntax onto for parsing.
         * @param {std::vector<std::string>&} YAMLLines vector to push any YAML syntax onto for parsing.
         * @return {bool} hasYaml?
         */
        bool preprocessFile(std::ifstream& myReadFile, std::vector<std::string>& lines, std::vector<std::string>& YAMLLines);
        
        /**
         * @method {processYAML} processes YAML content.
         * @return {void}
         */
        void processYAML();

        /**
         * @method {processMarkdown} processes Markdown content.
         * @return {void}
         */
        void processMarkdown(Sunset::BodyModel& bodyModel, std::vector<std::string> const &lines, int index, int length, Sunset::Paragraph *p);
        
        /**
         * @method {processLine} processes markdown syntax further. Removing bold, italics, etc.
         * @return {void}
         */
        void processLine(Sunset::Paragraph &paragraph);
    };
}

#endif // parser_hpp