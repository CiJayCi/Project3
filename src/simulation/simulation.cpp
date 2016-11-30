/**
 * This file contains implementations for the methods defined in the Simulation
 * class.
 *
 * You'll probably spend a lot of your time here.
 */

#include "simulation/simulation.h"
#include "frame/frame.h"
#include "physical_address/physical_address.h"

#include <iostream>

using namespace std;


void Simulation::run() {
  // DONE
	currentTime = 0;
	nextFrame = 0;

	for (auto& virtualAddress : virtualAddresses) {
		performMemAccess(virtualAddress);
		currentTime++;
	}

	if (options.verbose) {
		cout << "DONE!" << endl;
		cout << endl;
	}

	size_t totalMemAccesses = 0;
	size_t totalPageFaults = 0;
	size_t framesRemaining = NUM_FRAMES - nextFrame;

	for (auto& processKeyVal : processMap) {
		int pid = processKeyVal.first;
		Process* process = processKeyVal.second;

		cout << "Process  " << pid << ":  ACCESSES: " << process->memoryAccesses << "  FAULTS: " << process->page_faults << "  FAULT RATE: " << process->get_fault_percent() << "  RSS: " << process->get_rss() << endl;

		totalMemAccesses += process->memory_accesses;
		totalPageFaults += process->page_faults;
	}

	cout << endl;
	cout << "Total memory accesses : " << totalMemAccesses << endl;
	cout << "Total page faults : " << totalPageFaults << endl;
	cout << "Free frames remaining : " << framesRemaining << endl;
}


char Simulation::perform_memory_access(const VirtualAddress& address) {
  // DONE
	Process* process = processMap[address.process_id];
	process->memory_accesses++;
	size_t page = address.page;
	string memAccessResult;

	if (!process->page_table.rows[page].present) {
		memAccessResult = "PAGE FAULT";
		handle_page_fault(process, page);
	}
	else {
		memAccessResult = "IN MEMORY";
		process->page_table.rows[page].last_accessed_at = current_time;
	}

	int frameNum = process->page_table.rows[page].frame;
	PhysicalAddress physAddress(frameNum, address.offset);
	Frame frame;
	frame.set_page(process, page);
	char frameData = frame.contents->get_byte_at_offset(physAddress.offset);

	if (flag_options.verbose) {
		string indentPrefix = "    -> ";
		cout << address << endl;
		cout << indentPrefix << memAccessResult << endl;
		cout << indentPrefix << physAddress << endl;
		cout << indentPrefix << "RSS: " << process->get_rss() << endl;
		cout << endl;
	}

	return frameData;
}


void Simulation::handle_page_fault(Process* process, size_t page) {
  // DONE
	process->page_faults++;

	process->page_table.rows[page].present = true;
	process->page_table.rows[page].loaded_at = current_time;
	process->page_table.rows[page].last_accessed_at = current_time;

	if (process->get_rss() > flag_options.max_frames) {
		size_t pageToReplace = 0;
		if (flag_options.strategy == ReplacementStrategy::FIFO) {
			pageToReplace = process->page_table.get_oldest_page();
		}
		else if (flag_options.strategy == ReplacementStrategy::LRU) {
			pageToReplace = process->page_table.get_least_recently_used_page();
		}

		process->page_table.rows[page_to_replace].present = false;
		process->page_table.rows[page].frame = process->page_table.rows[pageToReplace].frame;

	}
	else {
		process->page_table.rows[page].frame = nextFrame;
		nextFrame++;
	}
}

Simulation::Simulation(FlagOptions options) : options(options) {
	string fileName = options.filename;
	ifstream input(fileName);
	if (!input) {
		cout << "Error opening simulation file '" << fileName << endl;
	}
	int numProcesses = 0;
	input >> numProcesses;
	for (int i = 0; i < numProcesses; ++i) {
		int pid;
		string processFilename;
		input >> pid >> processFilename;
		ifstream processInput(processFilename);
		if (!processInput) {
			cout << "Error opening process file '" << processFilename << "'\n";
		}
		processMap[pid] = Process::read_from_input(processInput);
	}
	int pid;
	string address;
	while (input >> pid >> address) {
		virtualAddresses.push_back(VirtualAddress::from_string(pid, address));
	}
}
