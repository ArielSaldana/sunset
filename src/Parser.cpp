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

void Parser::processLine(mdp::Paragraph &paragraph)
{
    int removeIndex = 0;
    switch (paragraph.type)
    {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 7:
    case 9:
        if (paragraph.type == 7) {
            removeIndex = 6;
        } else if (paragraph.type == 9) {
            removeIndex = 1;
        } else {
            removeIndex = paragraph.type;
        }
        paragraph.text = paragraph.text.substr(removeIndex + 1, paragraph.text.length() - 1);
    case 6:
    case 10:
        //create a stack based algorithm for this, or regex, and keep track of start/ends
        std::stack<mdm::Markup> stack;
        char c;
        mdm::Markup markup;

        for (int i = 0; i < paragraph.text.length(); i++)
        {
            c = paragraph.text[i];

            if (c == '*' || c == '_') { 
                int count = 1;
                while (i + count < paragraph.text.length()) {
                    if (paragraph.text.at(i+count) == c) {
                        count++;
                    } else {
                        break;
                    }
                }

                paragraph.text.erase(i, count);
                markup = {i, 0, count};
                i--;
                
                // stack logic
                if (!(stack.empty()) && (stack.top().type == markup.type)) {
                    markup = stack.top();
                    markup.end = i;
                    paragraph.markups.push_back(markup);
                    stack.pop();
                } else {
                    stack.push(markup);
                }
            }
        }

        break;
    }
}