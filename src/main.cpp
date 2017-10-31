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
    auto parser = new Sunset::Parser();
    // auto bm = parser->getFileJson("./assets/test2.md"); 
    auto bm = parser->getFileJson("./assets/", true); 
    std::cout << bm.dump(4) << std::endl;
}
