#pragma once

// library headers
#include <iostream>
#include <boost/program_options.hpp>
#include <configuration.hpp>
#include <string>
#include <cstdlib>

using std::string;
using std::cerr;
using std::endl;
using std::exit;
using std::stoi;
using std::stod;
namespace po = boost::program_options;


#ifndef DEFAULT_VALUES
#define DEFAULT_NB_ITER 10
#define DEFAULT_HEIGHT  4
#define DEFAULT_WIDTH   8 
#define DEFAULT_PR_HEIGHT 1
#define DEFAULT_PR_WIDTH 1
#define DEFAULT_DLT_T 0.125
#define DEFAULT_DLT_Y 1
#define DEFAULT_DLT_X 1
#define DEFAULT_WRITE_STEP 1
#define DEFAULT_FIXED_COND_PATH " "
#endif

class CommandLineConfig:
		public Configuration
{
	/// number of iterations to execute
	int m_nb_iter;
	
	/// shape of the global data field
	Coord2D m_global_shape;
	
	/// shape of the data distribution
	Coord2D m_dist_extents;
	
	/// time difference between two consecutive points
	double m_delta_t;
	
	/// space difference between two consecutive points
	std::array<double, 2> m_delta_space;

	/// step on which write hdf5 result file
	int m_write_step;

	string m_fixed_conditions_path;
	
public:
	/** Construct a new CommandLineConfig
	 * @param argc the number of command-line arguments
	 * @param argv the values of command-line arguments
	 */
	CommandLineConfig(const int argc, const char* const argv[]);
	
	// see overridden function
	int nb_iter() const override { return m_nb_iter; }
	
	// see overridden function
	Coord2D global_shape() const override { return m_global_shape; }
	
	// see overridden function
	Coord2D dist_extents() const override { return m_dist_extents; }
	
	// see overridden function
	double delta_t() const override { return m_delta_t; }
	
	// see overridden function
	std::array<double, 2> delta_space() const override { return m_delta_space; }

	// see overridden function
	int get_write_step() const override { return m_write_step; }

	// see overridden function
	string get_fixed_condition_file() const override { return m_fixed_conditions_path; }
	
};
