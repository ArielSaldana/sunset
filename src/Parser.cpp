// Parser.hpp
// Copyright 1998-2017 Ariel Saldana. All Rights Reserved.

#include "Parser.hpp"

void Parser::loadFile(std::string file)
{
    myReadFile.open(file);
}

void Parser::preprocessFile()
{
    std::string line;

    while (std::getline(myReadFile, line))
    {
        lines.push_back(line);
    }
}

void Parser::process(std::vector<std::string> const &lines, int index, int length, mdp::Paragraph *p)
{
    if (index != length)
    {
        std::string line = lines.at(index);
        mdp::Paragraph par;
        int offset = 0;

        // iterate through rules until match is found.
        for (int i = 0; i < rules.size(); i++)
        {
            Rule rule = rules.at(i);
            if (std::regex_match(line, rule.reg))
            { // match

                par = {"2ecf", line, rule.id, {}};

                if (rule.multiline && rule.fenced)
                {
                    int searchPointer = index + 1;
                    while (searchPointer + offset < lines.size() &&
                           !(std::regex_match(lines.at(searchPointer + offset), rule.reg)))
                    {
                        par.text += "\r\n" + lines.at(searchPointer + offset);
                        offset++;
                    }
                    if (offset > 0)
                        offset++;
                }

                else if (rule.multiline)
                { // rule is multiline
                    int searchPointer = index + 1;
                    while (searchPointer + offset < lines.size() &&
                           std::regex_match(lines.at(searchPointer + offset), rule.reg))
                    {
                        par.text += " " + lines.at(searchPointer + offset);
                        offset++;
                    }
                }

                // par.text = processLine(par.text, par.type);
                processLine(par);
                bodyModel.add(par);
                break;
            }
        }
        process(lines, index + 1 + offset, length, &par);
    }


}

std::string Parser::processLine(mdp::Paragraph &paragraph) {
    switch(paragraph.type) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 7:
        paragraph.text = paragraph.text.substr(paragraph.type+1, paragraph.text.length()-1);

    }
    return "";
}