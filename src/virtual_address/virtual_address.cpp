/**
 * This file contains implementations for methods in the VirtualAddress class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "virtual_address/virtual_address.h"

using namespace std;


VirtualAddress VirtualAddress::from_string(int process_id, string address) {
  // DONE
	string pageStr = address.substr(0, PAGE_BITS);
	string offsetStr = address.substr(PAGE_BITS, OFFSET_BITS);

	size_t page = bitset<PAGE_BITS>(pageStr).to_ulong();
	size_t offset = bitset<OFFSET_BITS>(offsetStr).to_ulong();

	return VirtualAddress(process_id, page, offset);
}


string VirtualAddress::to_string() const {
  // DONE
	string pageStr = bitset<PAGE_BITS>(page).to_string();
	string offsetStr = bitset<OFFSET_BITS>(offset).to_string();

	return pageStr + offsetStr;
}


ostream& operator <<(ostream& out, const VirtualAddress& address) {
  // DONE
	out << "PID " << address.process_id << " @ " << address.to_string() << " [page: " << address.page << "; offset: " << address.offset << "]";
	return out;
}
