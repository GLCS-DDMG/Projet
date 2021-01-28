cmake_minimum_required(VERSION 3.18)

add_library(PostProcessing
		src/postprocessing.cpp
)
target_include_directories(PostProcessing PUBLIC include/)
target_link_libraries(PostProcessing PUBLIC GLCS2020_project::baselib)
add_library(GLCS2020_project::PostProcessing ALIAS PostProcessing)
