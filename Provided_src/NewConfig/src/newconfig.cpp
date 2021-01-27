#include <cstdlib>
#include <iostream>
#include <string>

#include "newconfig.hpp"

using std::cerr;
using std::endl;
using std::exit;
using std::stoi;
using std::stod;
namespace po = boost::program_options;

CommandLineConfig::CommandLineConfig( const int argc, const char* const argv[] )
{
	po::options_description options("Options");
  	options.add_options()
	("help, h", 							 "Describe arguments")
	("nb_iter", 	  	po::value<int>(), 	 "Number of iterations")
	("height", 			po::value<int>(), 	 "General height of domain")
	("width", 		    po::value<int>(), 	 "General width  of domain")
	("process_height",  po::value<int>(), 	 "Process height of domain")
	("process_width",   po::value<int>(), 	 "Process width of domain")
	("delta_t", 	   	po::value<double>(), "Time step")
	("delta_y", 	   	po::value<int>(), 	 "Space step in y axe")
	("delta_x", 	   	po::value<int>(), 	 "Space step in x axe");

	po::variables_map vm;
	po::store(po::command_line_parser(argc, argv)
	             .options(options)
	             .allow_unregistered()
	             .run(),
		         vm);
	po::notify(vm);

	// Check for command line parameters ----------------------
	
	if (vm.count("help") || vm.count("h"))
	{
		std::cout << options << "\n";
		exit(0);
	}

	// --------------------------------------------------------

	if (vm.count("nb_iter"))
	{
		m_nb_iter = vm["nb_iter"].as<int>();
		std::cout << "Nb iterations : "<< m_nb_iter << "\n";
	}
	else{
		m_nb_iter = DEFAULT_NB_ITER;
		std::cout << "Nb iterations : "<< m_nb_iter << "\n";
	}

	// --------------------------------------------------------

	if (vm.count("height"))
	{
		m_global_shape[DY] = vm["height"].as<int>();
		std::cout << "Height : "<< m_global_shape[DY] << "\n";
	}
	else{
		m_global_shape[DY] = DEFAULT_HEIGHT;
		std::cout << "Height : "<< m_global_shape[DY] << "\n";
	}

	// --------------------------------------------------------

	if (vm.count("width"))
	{
		m_global_shape[DX] = vm["width"].as<int>();
		std::cout << "Width : "<< m_global_shape[DX] << "\n";
	}
	else{
		m_global_shape[DX] = DEFAULT_WIDTH;
		std::cout << "Width : "<< m_global_shape[DX] << "\n";
	}

	// --------------------------------------------------------

	if (vm.count("process_height"))
	{
		m_dist_extents[DY] = vm["process_height"].as<int>();
		std::cout << "Process height : "<< m_dist_extents[DY] << "\n";
	}
	else{
		m_dist_extents[DY] = DEFAULT_PR_HEIGHT;
		std::cout << "Process height : "<< m_dist_extents[DY] << "\n";
	}
	
	// --------------------------------------------------------

	if (vm.count("process_width"))
	{
		m_dist_extents[DX] = vm["process_width"].as<int>();
		std::cout << "Process width : "<< m_dist_extents[DX] << "\n";
	}
	else{
		m_dist_extents[DX] = DEFAULT_PR_WIDTH;
		std::cout << "Process width : "<< m_dist_extents[DX] << "\n";
	}

	// --------------------------------------------------------

	if (vm.count("delta_t"))
	{
		m_delta_t = vm["delta_t"].as<double>();
		std::cout << "Delta t : "<< m_delta_t << "\n";
	}
	else{
		m_delta_t = DEFAULT_DLT_T;
		std::cout << "Delta t : "<< m_delta_t << "\n";
	}

	// --------------------------------------------------------

	if (vm.count("delta_y"))
	{
		m_delta_space[DY] = vm["delta_y"].as<int>();
		std::cout << "Delta t : "<< m_delta_space[DY] << "\n";
	}
	else{
		m_delta_space[DY] = DEFAULT_DLT_Y;
		std::cout << "Delta t : "<< m_delta_space[DY] << "\n";
	}

	// --------------------------------------------------------

	if (vm.count("delta_x"))
	{
		m_delta_space[DX] = vm["delta_x"].as<int>();
		std::cout << "Delta t : "<< m_delta_space[DX] << "\n";
	}
	else{
		m_delta_space[DX] = DEFAULT_DLT_X;
		std::cout << "Delta t : "<< m_delta_space[DX] << "\n";
	}

	// --------------------------------------------------------

	std::cout << "Configuring...\n";

}
