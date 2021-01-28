// implemented class
#include "postprocessing.hpp"

using std::vector;


PostProcessing :: PostProcessing ( const Distributed2DField& data )
{   
	// Getting Block height and width
	size_t block_height = data.noghost_view().extent(DY);
	size_t block_width = data.noghost_view().extent(DX);

	// Getting data 
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
    
    // Computing average
    this->average = 0.;
    for (int i = 0; i < block_height*block_width; ++i)
    {
    	this->average += data_tmp[i];
    }
    this->average /= (block_height*block_width);

}
PostProcessing::~PostProcessing(){}
