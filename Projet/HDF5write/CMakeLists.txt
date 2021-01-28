cmake_minimum_required(VERSION 3.18)

set(HDF5_PREFER_PARALLEL TRUE)
find_package(HDF5 REQUIRED COMPONENTS C HL)
find_package(MPI REQUIRED COMPONENTS CXX)

add_library(HDF5write
		src/hdf5write.cpp
)

target_include_directories(HDF5write PUBLIC include/)
target_link_libraries(HDF5write PUBLIC  GLCS2020_project::baselib
										GLCS2020_project::PostProcessing 
										hdf5::hdf5 
										hdf5::hdf5_hl)

add_library(GLCS2020_project::HDF5write ALIAS HDF5write)