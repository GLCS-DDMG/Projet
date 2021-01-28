cmake_minimum_required(VERSION 3.18)

project(GLCS2020_project C CXX)

set(HDF5_PREFER_PARALLEL TRUE)
find_package(HDF5 REQUIRED COMPONENTS C HL)
find_package(MPI REQUIRED COMPONENTS CXX)

add_subdirectory("vendor/mdspan/" "mdspan" EXCLUDE_FROM_ALL)

add_subdirectory(baselib)
add_subdirectory(heatlib)
add_subdirectory(simpleui)
add_subdirectory(NewConfig)
add_subdirectory(HDF5write)
add_subdirectory(PostProcessing)

add_executable(simpleheat
		simpleheat.cpp
)
target_link_libraries(simpleheat PRIVATE
		GLCS2020_project::baselib
		GLCS2020_project::heatlib
		GLCS2020_project::simpleui
		GLCS2020_project::NewConfig
		GLCS2020_project::HDF5write
		GLCS2020_project::PostProcessing
		MPI::MPI_CXX
		hdf5::hdf5
		hdf5::hdf5_hl) 
