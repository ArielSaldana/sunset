// Parser.hpp
// Copyright 1998-2017 Ariel Saldana. All Rights Reserved.

#include "Parser.hpp"
#include "GenerateId.hpp"

using namespace Sunset;

Sunset::Content Parser::loadFile(std::string file)
{
    Sunset::Content fileContent;
    Sunset::BodyModel bodyModel;
    
    std::vector<std::string> lines;
    std::vector<std::string> YAMLLines;

    //open stream to read file
    std::ifstream myReadFile;
    myReadFile.open(file);

    // preprocess file
    bool requiresYAMLProcessing = preprocessFile(myReadFile, lines, YAMLLines);

    // YAML processing
    if (requiresYAMLProcessing) {
        std::string yaml = "{";
        for (int i = 1; i < YAMLLines.size(); i++) {
            yaml += YAMLLines.at(i) + ", ";
        }
        yaml+= "}";
        YAML::Node lineup = YAML::Load(yaml);

        for(YAML::const_iterator it=lineup.begin();it!=lineup.end();++it) {
            switch(values[it->first.as<std::string>()])
            {
                case title:
                    fileContent.title = it->second.as<std::string>();
                    break;
                case description:
                    fileContent.description = it->second.as<std::string>();
                    break;
                case link:
                    fileContent.link = it->second.as<std::string>();
                    break;
                case img:
                    fileContent.img = it->second.as<std::string>();
                    break;
                case category:
                    fileContent.category = it->second.as<std::string>();
                    break;
                case layout:
                    fileContent.layout = it->second.as<std::string>();
                    break;
            }
        }
    }

    // Markdown processing
    processMarkdown(bodyModel, lines, 0, lines.size(), nullptr);
    
    fileContent.bodyModel = bodyModel;
    return fileContent;
}


json Parser::getFileJson(std::string file)
{
    json j = loadFile(file);
    return j;
}

json Parser::getFileJson(const std::string file, bool directory) {
    if (!directory)
        return getFileJson(file);

    std::vector<Sunset::Content> contents;
    json j;

    DIR *dpdf;
    struct dirent *epdf;

    dpdf = opendir(file.c_str());
    if (dpdf != NULL){
        while ((epdf = readdir(dpdf))) {
            if (std::regex_match(epdf->d_name, std::regex(".+\\.md$"))) {
                content.push_back(
                    loadFile(file + epdf->d_name)
                );
            }
        }
    }
    closedir(dpdf);

    j["payload"]["content"] = content;
    return j;
}

bool Parser::preprocessFile(std::ifstream& myReadFile, std::vector<std::string>& lines, std::vector<std::string>& YAMLLines)
{
    std::string line;
    bool ignoringYAML = false, hasYAML = false;
    int linecount = 1;

    while (std::getline(myReadFile, line))
    {
        // if yaml found
        if (linecount == 1 && std::regex_match(line, std::regex("^-{3}$"))) {
            ignoringYAML = true;
            hasYAML = true;
        }
        else if (std::regex_match(line, std::regex("^-{3}$"))) {
            ignoringYAML = false;
            line = "";
        }
        
        if (!ignoringYAML) {
            lines.push_back(line);
        } else {
            if (line.length() > 0)
            YAMLLines.push_back(line);
        }

        linecount++;
    }

    return hasYAML;
}

void Parser::processMarkdown(Sunset::BodyModel& bodyModel, std::vector<std::string> const &lines, int index, int length, Sunset::Paragraph *p)
{
    if (index != length)
    {
        std::string line = lines.at(index);
        Sunset::Paragraph par;
        int offset = 0;

        // iterate through rules until match is found.
        for (int i = 0; i < rules.size(); i++)
        {
            Rule rule = rules.at(i);
            if (std::regex_match(line, rule.reg))
            { // match

                par = { Sunset::random_string(4), line, rule.id, {} };

                if (rule.multiline && rule.fenced)
                {
                    int searchPointer = index + 1;
                    par.text = "";
                    while (searchPointer + offset < lines.size() &&
                           !(std::regex_match(lines.at(searchPointer + offset), rule.reg)))
                    {
                        par.text += lines.at(searchPointer + offset) + "\r\n";
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

                processLine(par);
                bodyModel.add(par);
                break;
            }
        }
        processMarkdown(bodyModel, lines, index + 1 + offset, length, &par);
    }
}

void Parser::processLine(Sunset::Paragraph &paragraph)
{
    int removeIndex = 0;
    std::stack<Sunset::Markup> stack;
    Sunset::Markup markup;
    
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
        char c;
        for (int i = 0; i < paragraph.text.length(); i++)
        {
            c = paragraph.text[i];

            if (c == '*' || c == '_' || c == '`') { 
                int count = 1;
                while (i + count < paragraph.text.length() && 
                    paragraph.text.at(count+i) == c) {
                        count++;
                }

                if (c == '`') {
                    std::string s = paragraph.text.substr(i, paragraph.text.length());
                    std::smatch match;
                    std::regex r = std::regex("(`{"+std::to_string(count)+"}\\s*(.*?)\\s*`{"+std::to_string(count)+"})");

                    if (std::regex_search(s, match, r)) {
                        unsigned int pos = s.find(match[0]);

                        if (pos == 0) {
                            paragraph.text.replace(i, match[0].length(), match[2]);
                            markup = {i, i + static_cast<int>(match[2].length()), 4};
                            paragraph.markups.push_back(markup);

                            int difference = match[2].length() - i;
                            i += difference-1;
                        }
                    }
                } else {
                    paragraph.text.erase(i, count);
                    
                    markup = {i, 0, count};
                    i--;
                    
                    // stack logic
                    if (!(stack.empty()) && (stack.top().type == markup.type)) {
                        markup = stack.top();
                        markup.end = i+1;
                        paragraph.markups.push_back(markup);
                        stack.pop();
                    } else {
                        stack.push(markup);
                    }
                }
            }  else if (c == '[') {
                std::string s = paragraph.text.substr(i, paragraph.text.length());
                std::smatch match;
                if (std::regex_search(s, match, std::regex("\\[(.+?)\\]\\((.+?)\\s?(\"(.+?)\")?\\)"))) {
                    unsigned int pos =  s.find(match[0]);

                    if (pos == 0) { // this bracket is a match to a link
                        paragraph.text.replace(i, match[0].length(), match[1]);
                        
                        markup = {i, static_cast<int>(i + match[1].length()), 3};
                        markup.href = match[2];
                        (match[4] == "") ? markup.title = match[1] : markup.title = match[4]; 
                        
                        paragraph.markups.push_back(markup);

                        int difference = match[2].length() - i;
                        i += difference-1;
                    }
                }
            }
        }
    }
}