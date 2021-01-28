#include <mpi.h>

#include "newconfig.hpp"
#include "hdf5write.hpp"
#include "finitediffheatsolver.hpp"
#include "fixedconditions.hpp"
#include "simulation.hpp"
//#include "screenprinter.hpp"

int main( int argc, char* argv[] )
{
	// initialize the MPI library
	MPI_Init( &argc, &argv );

	// Construct the command-line arguments parser
	CommandLineConfig config( argc, argv );
	// construct the heat equation solver
	FinitediffHeatSolver heat_solver( config );
	// construct the initial condition setter
	FixedConditions init;
	// construct the simulation runner
	Simulation simulation( MPI_COMM_WORLD, config, heat_solver, init );
	// Add a printer to screen to observe the simulation
	HDF5write writer;
	simulation.observe( writer );

	// run the simulation
	simulation.run();

	// finalize MPI
	MPI_Finalize();

	return 0;
}
