#include <iostream>

#include "json.h"
#include "BodyModel.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include <map>
#include "Parser.hpp"
#include "Content.hpp"
#include "yaml-cpp/yaml.h"
#include <dirent.h>



int main() {

    // YAML::Node lineup = YAML::LoadFile("./assets/test2.md");
    // // YAML::Node lineup = YAML::Load("{1B: Prince Fielder, 2B: Rickie Weeks, LF: Ryan Braun}");
    // // YAML::Node lineup = YAML::Load("{1B: Prince Fielder, 2B: Rickie Weeks, LF: Ryan Braun, tags: [css]}");
    
    // for(YAML::const_iterator it=lineup.begin();it!=lineup.end();++it) {
    //     // if (it->first.Type() == YAML::NodeType::Sequence) {

    //     // } else 
    //     std::cout << it->first.as<std::string>() << std::endl;
    //     std::cout << it->second.Type() << std::endl;
    // //   std::cout << "Playing at " << it->first.as<std::string>() << " is " << it->second.as<std::string>() << "\n";
    // }
    
    // lineup["RF"] = "Corey Hart";
    // lineup["C"] = "Jonathan Lucroy";
    // assert(lineup.size() == 5);


    // DIR *dpdf;
    // struct dirent *epdf;

    // dpdf = opendir("./");
    // if (dpdf != NULL){
    //     while ((epdf = readdir(dpdf))) {
    //         printf("Filename: %s\n",epdf->d_name);
    //         // std::cout << epdf->d_name << std::endl;
    //     }
    // }
    // closedir(dpdf);


    auto parser = new Sunset::Parser();
    // auto bm = parser->getFileJson("./assets/test2.md"); 
    auto bm = parser->getFileJson("./assets/", true); 
    std::cout << bm << std::endl;
    // json j;
    // j["payload"]["content"] = bm;
    // json jp = bm;
    // std::cout << jp << std::endl;
    
    // std::vector<Sunset::Content> v = {
    //     {"Spider Man 3"},
    //     { "Dead Mans Curse" }
    // };
    // json j;
    // j["payload"]["content"] = v;
    // std::cout << j << std::endl;
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

//     auto bm = new Sunset::BodyModel();

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
//     // auto bm = new Sunset::BodyModel();
//     // Sunset::Paragraph par { "2c66", "Hello, World", 1};
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