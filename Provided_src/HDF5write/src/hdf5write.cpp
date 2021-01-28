// standard C++ library headers
#include <chrono>
#include <iostream>
#include <thread>
#include <hdf5.h>
#include <vector>
#include <string>

// the implemented class
#include "hdf5write.hpp"

using std::cout;
using std::endl;
using std::flush;
using std::this_thread::sleep_for;
using std::chrono::milliseconds;
using std::vector;
using std::to_string;
using std::string;




void HDF5write::simulation_updated( const Distributed2DField& data )
{	
	// Getting Block height and width
	hsize_t block_height = data.noghost_view().extent(DY);
	hsize_t block_width = data.noghost_view().extent(DX);

	// Getting data to needed format
	vector<double> data_tmp(block_height*block_width);
	for ( int pyy = data.distribution().extent( DY )-1; pyy >=0 ; --pyy ) {
		for ( int yy = data.noghost_view().extent( DY )-1; yy >=0 ; --yy ) {
			for ( int pxx = 0; pxx < data.distribution().extent( DX ); ++pxx ) {
				for ( int xx = 0; xx < data.noghost_view().extent( DX ); ++xx ) {
                    data_tmp[yy*block_width+xx] = data.noghost_view(yy, xx);
				}
				MPI_Barrier(data.distribution().communicator());
			}
		}
	}

	// File name 
	string file_name = "./ResultHDF5/my_file_" + to_string(data.time()) + ".h5";

	// File create 
	hid_t h5file = H5Fcreate(file_name.c_str(), H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

	// Defining dimensions os dataspace
	hsize_t dims[2] = {block_height,block_width};

	// Creating the dataspace
	hid_t dataspace_id = H5Screate_simple(2, dims, NULL);

	// Create the dataset
	hid_t dataset_id = H5Dcreate(h5file, to_string(data.time()).c_str(), H5T_NATIVE_DOUBLE,
									dataspace_id, H5P_DEFAULT,
									H5P_DEFAULT, H5P_DEFAULT );
	// Writing data 
	H5Dwrite(dataset_id, H5T_NATIVE_DOUBLE, dataspace_id, H5S_ALL,
				H5S_ALL, (void*)&data_tmp[0]);

	// Closing opened dataset, dataspace and file
	H5Dclose(dataset_id);
	H5Sclose(dataspace_id);
	H5Fclose(h5file);	
}
