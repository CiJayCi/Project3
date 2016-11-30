/**
 * This file contains implementations for methods in the flag_parser.h file.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "flag_parser/flag_parser.h"
#include <getopt.h>
#include <iostream>

using namespace std;


void print_usage() {
  cout <<
      "Usage: mem-sim [options] filename\n"
      "\n"
      "Options:\n"
      "  -v, --verbose\n"
      "      Output information about every memory access.\n"
      "\n"
      "  -s, --strategy (FIFO | LRU)\n"
      "      The replacement strategy to use. One of FIFO or LRU.\n"
      "\n"
      "  -f, --max-frames <positive integer>\n"
      "      The maximum number of frames a process may be allocated.\n"
      "\n"
      "  -h --help\n"
      "      Display a help message about these flags and exit\n"
      "\n";
}


bool parse_flags(int argc, char** argv, FlagOptions& flags) {
  // DONE
	static struct option long_options[] = {
		{ "verbose", no_argument, 0, 'v' },
		{ "strategy", required_argument, 0, 's' },
		{ "max-frames", required_argument, 0, 'f' },
		{ "help", no_argument, 0, 'h' },
		{ 0, 0, 0, 0 }
	};

	int opt = 0;
	int long = 0;
	while ((opt = getopt_long(argc, argv, "vs:f:h", long_options, &long)) != -1) {
		if (opt == 'v') {
			flags.verbose = true;
		}
		else if (opt == 's') {
			string strategyName = optarg;
			if (strategyName == "FIFO") {
				flags.strategy = ReplacementStrategy::FIFO;
			}
			else if (strategyName == "LRU") {
				flags.strategy = ReplacementStrategy::LRU;
			}
			else {
				return false;
			}
		}
		else if (opt == 'f') {
			int numFrames = atoi(optarg);
			if (numFrames <= 0) {
				return false;
			}
			flags.max_frames = numFrames;
		}
		else if (opt == 'h') {
			print_usage();
		}
		else {
			return false;
		}
	}

	flags.filename = argv[argc - 1];
	if (argc == 1) {
		return false;
	}
	return true;
}
