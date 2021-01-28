cmake_minimum_required(VERSION 3.18)

add_library(postprocessing
        src/postprocessing.cpp
)

target_include_directories(postprocessing PUBLIC include/)
target_link_libraries(postprocessing PUBLIC GLCS2020_project::baselib)
add_library(GLCS2020_project::postprocessing ALIAS postprocessing)