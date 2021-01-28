#pragma once
// standard C++ library headers
#include <iostream>

// local headers
#include "distributed2dfield.hpp"


class PostProcessing   
{	
public:
	double average = 0.;

    // compute the average of data
    PostProcessing ( const Distributed2DField& data );

    ~PostProcessing();
};