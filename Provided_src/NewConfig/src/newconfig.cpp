// Local headers
#include "newconfig.hpp"

CommandLineConfig::CommandLineConfig( const int argc, const char* const argv[] )
{
	po::options_description options("Options");
  	options.add_options()
	("help, h", 							 "Describe arguments")
	("nb_iter", 	  			po::value<int>(), 	 "Number of iterations")
	("height", 					po::value<int>(), 	 "General height of domain")
	("width", 		    		po::value<int>(), 	 "General width  of domain")
	("process_height",  		po::value<int>(), 	 "Process height of domain")
	("process_width",   		po::value<int>(), 	 "Process width of domain")
	("delta_t", 	   			po::value<double>(), "Time step")
	("delta_y", 	   			po::value<int>(), 	 "Space step in y axe")
	("delta_x", 	   			po::value<int>(), 	 "Space step in x axe")
	("write_step", 	   			po::value<int>(), 	 "Step on which write result hdf5 file")
	("fixed_conditions_path",	po::value<string>(), "File path for fixed conditions");

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

	if (vm.count("write_step"))
	{
		m_write_step = vm["write_step"].as<int>();
		std::cout << "Write step : "<< m_write_step << "\n";
	}
	else{
		m_write_step = DEFAULT_WRITE_STEP;
		std::cout << "Write step : "<< m_write_step << "\n";
	}

	if (vm.count("fixed_conditions_path"))
	{
		m_fixed_conditions_path = vm["fixed_conditions_path"].as<string>();
		std::cout << "Fixed conditions file path : "<< m_fixed_conditions_path << "\n";
	}
	else{
		m_fixed_conditions_path = DEFAULT_FIXED_COND_PATH;
		std::cout << "Fixed conditions file path : "<< "NONE" << "\n";
	}

		


	std::cout << "Configuring...\n";

}
