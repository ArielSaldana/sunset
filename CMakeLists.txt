cmake_minimum_required (VERSION 3.0)
project (MarkdownParser)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")

#include the subdirectory containing our libs
include_directories(src)
include_directories(yaml/include)


#add_subdirectory (yaml)
#include_directories(yaml/src)
#LINK_DIRECTORIES(yaml/src)
#target_link_libraries (yaml-cpp ${LIB_I_NEED})


#indicate the entry point for the executable

file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS src/*.hpp)
file(GLOB YAMLSOURCES yaml/src/*.cpp)
file(GLOB YAMLHEADERS yaml/src/*.h)

add_executable (sunset 
    src/json.h
    ${SOURCES}
    ${HEADERS}
    ${YAMLSOURCES}
    ${YAMLHEADERS}
)

#add_library(MyLib SHARED 
#    ${SOURCES}
#    ${HEADERS}
#    ${YAMLSOURCES}
#    ${YAMLHEADERS}
#)

add_library(MyLibStatic STATIC 
    ${SOURCES}
    ${YAMLSOURCES}
)

# Indicate which libraries to include during the link process.
#target_link_libraries (Hello)

install (TARGETS sunset DESTINATION bin)