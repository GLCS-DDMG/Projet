#pragma once

//library headers
#include <simulationobserver.hpp>

class PostProcessing   
        :public SimulationObserver
{
public:
    // compute the avg of each data on each step
    double avg_data( const Distributed2DField& data );
};