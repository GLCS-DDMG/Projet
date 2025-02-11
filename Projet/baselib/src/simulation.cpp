// the implemented class (last)
#include "simulation.hpp"

Simulation::Simulation( MPI_Comm comm, const Configuration& config, const TimeStep& time_step, const InitialConditionner& init )
	: m_config( config )
	, m_time_step( time_step )
	, m_init( init)
	, m_comm( comm )
{
}

void Simulation::run() const
{
	// allocate data for the current iteration
	Distributed2DField current( m_comm, m_config.dist_extents(), m_config.global_shape(), m_time_step.required_ghosts(), m_config.delta_space() );

	// allocate data for the next iteration
	Distributed2DField next( m_comm, m_config.dist_extents(), m_config.global_shape(), m_time_step.required_ghosts(), m_config.delta_space() );

	// define iteration index for result file writing
	int iteration_index = 1; 

	// initialize data at t=0
	m_init.initial_condition( current );
	m_init.initial_condition( next );

	// Write file if good iteration or post processing
	if (m_config.get_post_processing_state())
	{
		for ( auto&& observer : m_observers ) {
		observer->simulation_updated_post_processing( current );
		}
	}
	else
	{
		if (m_config.get_write_step() == iteration_index)
		{
			iteration_index == 1;
			for ( auto&& observer : m_observers ) {
			observer->simulation_updated( current );
			}
		}
		else
			iteration_index++;
	}
	

	// the main (time) iteration
	for ( int ii = 0; ii < m_config.nb_iter(); ++ii ) {

		// compute the temperature at the next iteration
		m_time_step.iter( current, next );

		// Write file if good iteration or post processing
		if (m_config.get_post_processing_state())
		{
			for ( auto&& observer : m_observers ) {
			observer->simulation_updated_post_processing( current );
			}
		}
		else
		{
			if (m_config.get_write_step() == iteration_index)
			{
				iteration_index == 1;
				for ( auto&& observer : m_observers ) {
				observer->simulation_updated( current );
				}
			}
			else
				iteration_index++;
		}

		// swap the current and next buffers
		current.swap( next );
	}

}
