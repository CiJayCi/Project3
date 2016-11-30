/**
 * This file contains implementations for methods in the Process class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "process/process.h"
#include <iostream>

using namespace std;


Process* Process::read_from_input(std::istream& in) {
  // DONE
	size_t num_bytes = 0;
	vector<Page*> pages;

	Page* current = Page::read_from_input(in);
	while (current != nullptr) {
		num_bytes += current->size();
		pages.push_back(current);
		current = Page::read_from_input(in);
	}

	return new Process(num_bytes, pages);

}


size_t Process::size() const {
  // DONE
	return num_bytes;
}


bool Process::is_valid_page(size_t index) const {
  // DONE
	return (index < pages.size());
}


size_t Process::get_rss() const {
  // DONE
	return page_table.get_present_page_count();
}


double Process::get_fault_percent() const {
  // DONE
	if (memory_accesses == 0) {
		return 0.0;
	}
	else {
		return ((float)page_faults * 100.0 / (float)memory_accesses);
	}
}
}
