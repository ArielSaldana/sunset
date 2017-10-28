#include <iostream>

#include "json.h"
#include "BodyModel.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include <map>
#include "Parser.hpp"

int main() {
    auto parser = new Parser();
    parser->loadFile("./assets/test.md");
    
    parser->preprocessFile();
    parser->process(
        parser->lines,
        0,
        parser->lines.size(), 
        nullptr
    );

    json jp = parser->bodyModel;
    std::cout << jp << std::endl;
}

// int main()
// {
//     // CREATE A MAP
//     std::map<int, std::regex> regexMap;
//     regexMap.insert({1, std::regex(H1_REGEX)});
//     regexMap.insert({2, std::regex(H2_REGEX)});
//     regexMap.insert({3, std::regex(H3_REGEX)});
//     regexMap.insert({4, std::regex(H4_REGEX)});
//     regexMap.insert({5, std::regex(H5_REGEX)});
//     regexMap.insert({9, std::regex(ULOL_REGEX)});
//     regexMap.insert({6, std::regex(P_REGEX)});

//     auto bm = new mdbm::BodyModel();

//     std::ifstream myReadFile;
//     myReadFile.open("/Users/ariel/Desktop/test-cmake/assets/test.md");

//     std::string line;
//     std::string strBuf = "";
//     bool bufHasData = false;
//     int buftype = 0;

//     while (std::getline(myReadFile, line))
//     {

//         for (std::pair<int, std::regex> element : regexMap)
//         {
//             if (std::regex_match(line, element.second)) {
//                 if (element.first == 6) { // paragraph
//                     strBuf += line + " ";
//                     bufHasData = true;
//                     break;
//                 } else {
//                     if (bufHasData) {
//                         bm->add({"2c", strBuf, 6});
//                         strBuf = "";
//                         bufHasData = false;
//                     }
//                     bm->add({ "2c", line, element.first});
//                     break;
//                 }
//             } 
//         }
//     }



//     myReadFile.close();
//     // auto bm = new mdbm::BodyModel();
//     // mdp::Paragraph par { "2c66", "Hello, World", 1};
//     // bm->add(par);
//     json jp = *bm;
//     std::cout << jp << std::endl;
// }

// cases are
 /*

multiline start, middle, end


6 -> multiline
6 -> multiline
6 -> multiline
3 -> multiline


 */