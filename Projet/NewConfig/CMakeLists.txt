cmake_minimum_required(VERSION 3.18)

add_library(NewConfig
		src/newconfig.cpp
)
target_include_directories(NewConfig PUBLIC include/)
target_link_libraries(NewConfig PUBLIC GLCS2020_project::baselib boost_program_options)
add_library(GLCS2020_project::NewConfig ALIAS NewConfig)
