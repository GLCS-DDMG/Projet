#pragma once
// library headers
#include <string>

// local headers
#include "distributed2dfield.hpp"

using std::string;

class Configuration
{
public:
	/// The destructor
	virtual ~Configuration() = default;
	
	/** Access the number of iterations to execute
	 * @return 
	 */
	virtual int nb_iter() const = 0;
	
	/** Access the size of the global array
	 * @return the size of the global array
	 */
	virtual Coord2D global_shape() const = 0;
	
	/** Access the shape of the distribution to use
	 * @return the shape of the distribution to use
	 */
	virtual Coord2D dist_extents() const = 0;
	
	/** Access the step in time to use
	 * @return the step in time to use
	 */
	virtual double delta_t() const = 0;
	
	/** Access the step in space to use
	 * @return the step in space to use
	 */
	virtual std::array<double, 2> delta_space() const = 0;

	/** Access the step to write result file
	 * @return the step to write result file
	 */
	virtual int get_write_step() const = 0;
	
	/** Access the hdf5 file for fixed conditions
	 * @return the hdf5 file for fixed conditions
	 */
	virtual string get_fixed_condition_file() const = 0;

	/** Access the post processing state
	 * @return the post processing state
	 */
	virtual int get_post_processing_state() const = 0;	
};
