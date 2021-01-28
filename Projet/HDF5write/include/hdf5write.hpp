#pragma once
#include <simulationobserver.hpp>



class HDF5write
		: public SimulationObserver
{
public:
	// see overriden function
	void simulation_updated( const Distributed2DField& data ) override;

	// Call PostProcessing method to write only the average
	void simulation_updated_post_processing(const Distributed2DField& data);
	
};
