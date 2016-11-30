/**
 * This file contains the main() function that drives the simulation. You'll
 * need to add logic to this file to create a Simulation instance and invoke its
 * run() method.
 */

#include <cstdlib>
#include "flag_parser/flag_parser.h"
#include "process/process.h"
#include "simulation/simulation.h"
#include <iostream>

using namespace std;


/**
 * The main entry point to the simulation.
 */
int main(int argc, char** argv) {
  // DONE

	FlagOptions options;
	if (!parse_flags(argc, argv, options)) {
		cout << "Error parsing flags\n";
		print_usage();
		return EXIT_FAILURE;
	}

	Simulation simulation(options);
	simulation.run();
  return EXIT_SUCCESS;
}
