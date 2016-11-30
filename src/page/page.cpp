/**
 * This file contains implementations for methods in the Page class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "page/page.h"

using namespace std;


// Ensure PAGE_SIZE is initialized.
const size_t Page::PAGE_SIZE;


Page* Page::read_from_input(std::istream& in) {
  // DONE
	vector<char> bytes;
	char current = 0;
	while (bytes.size() < PAGE_SIZE) {
		if (!(in >> noskipws >> current)) {
			break;
		}
		else {
			bytes.push_back(current);
		}
	}

	if (bytes.size() == 0) {
		return nullptr;
	}
	else {
		return new Page(bytes);
	}
}


size_t Page::size() const {
  // DONE
	return bytes.size();
}


bool Page::is_valid_offset(size_t offset) const {
  // DONE
	return offset < size();
}


char Page::get_byte_at_offset(size_t offset) {
  // DONE
	return bytes[offset];
}
