cmake_minimum_required (VERSION 3.0)
project (MarkdownParser)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#include the subdirectory containing our libs
#add_subdirectory (src)
include_directories(src)

#indicate the entry point for the executable
add_executable (sunset 
src/main.cpp
src/BodyModel.cpp
src/Paragraph.cpp
src/Parser.cpp
src/Markup.cpp
src/json.h
src/BodyModel.hpp
src/Paragraph.hpp
src/Parser.hpp
src/Markup.hpp
)

# Indicate which libraries to include during the link process.
#target_link_libraries (Hello)

install (TARGETS sunset DESTINATION bin)