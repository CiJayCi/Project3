/**
 * This file contains implementations for methods in the PhysicalAddress class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "physical_address/physical_address.h"

using namespace std;


string PhysicalAddress::to_string() const {
  // DONE
	string frameStr = bitset<FRAME_BITS>(frame).to_string();
	string offsetStr = bitset<OFFSET_BITS>(offset).to_string();

	return frameStr + offsetStr;
}


ostream& operator <<(ostream& out, const PhysicalAddress& address) {
  // DONE
	out << address.to_string() << " [frame: " << address.frame << "; offset: " << address.offset << "]";
	return out;
}
