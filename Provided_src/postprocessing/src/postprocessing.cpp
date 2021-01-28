// std lib headers
#include <chrono>
#include <iostream>
#include <thread>

// implemented class
#include "postprocessing.hpp"

double PostProcessing::avg_data( const Distributed2DField& data ) 
{   
    std::vector<double> tmp;
    
    for ( int pyy = data.distribution().extent( DY )-1; pyy >=0 ; --pyy ) {
		for ( int yy = data.noghost_view().extent( DY )-1; yy >=0 ; --yy ) {
			for ( int pxx = 0; pxx < data.distribution().extent( DX ); ++pxx ) {
				for ( int xx = 0; xx < data.noghost_view().extent( DX ); ++xx ) {
                    tmp.push_back( data.noghost_view(yy, xx) );
				}
				MPI_Barrier(data.distribution().communicator());
			}
		}
	}
    
    double avg;
    for (int i=0; i<tmp.size(); i++)
        avg += tmp[i];

    avg /= tmp.size();
    std::cout<<avg<<std::flush;
    return avg;

}